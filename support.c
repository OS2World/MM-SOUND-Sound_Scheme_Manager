#define INCL_MCIOS2
#define INCL_MACHDR
#define INCL_WIN
#define INCL_PM
#include <os2.h>
#include <os2me.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssm.h"
#include "support.h"
#include "main.h"
#include "menu.h"
#include "question.h"
#include "find.h"
#include "icon.h"
#include "acceltable.h"
#include "stringtable.h"
#include "test.h"
#include "prodinfo.h"
#include "settings.h"
#include "pmtools.h"


// Geef het geheugen van de tabel met Naam, Key en Index van de gebeurtenissen recursief vrij
void WisNaamTabel(PTABEL pTabel)
{
// Is dit de laatste record?
if (pTabel->Volgende!=NULL)
   {
   // Nee, laat hem eerst het geheugen van de volgende record vrijgeven
   WisNaamTabel(pTabel->Volgende);
   }
// Het geheugen van eventuele volgende records is al vrijgegeven, geef nu het geheugen van deze record vrij
// Geef eerst het geheugen van de leden vrij
DosFreeMem(pTabel->Naam);
DosFreeMem(pTabel->Key);
// Geef nu het geheugen voor deze record vrij (en dus ook meteen dat waarnaar de pointer Volgende uit de
// eventuele vorige aanroep naar wees)
DosFreeMem(pTabel);
}

int LeesNaam(PTABEL Tabel, HINI PrfMMPM)
{
char *buffer, *Temp, *Naam, *namestr, *deel1, *deel2, *deel3;
int Index;
unsigned long ulSize;
PTABEL pTabel;
// Vraag de grootte op
PrfQueryProfileSize(PrfMMPM, MMPM_SOUNDS, NULL, &ulSize);
// En reserveer het geheugen
DosAllocMem((void **)&buffer, ulSize, PAG_COMMIT | PAG_READ | PAG_WRITE);
if (buffer==NULL)
   {
   WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, "Couldn't allocate memory", "Debug!", 0, MB_OK | MB_ERROR);
   return 0;
   }
// Vraag alle keys op
PrfQueryProfileString(PrfMMPM, MMPM_SOUNDS, NULL, NULL, (void *)buffer, ulSize+1);
// Ontrafel de keys
namestr=buffer;
pTabel=Tabel;
Index=0;
while (*namestr!=0)
   {
   // Zet de index in de record
   pTabel->Index=Index;
   // en verhoog de index met 1
   Index++;
   // Vraag de grootte op
   PrfQueryProfileSize(PrfMMPM, MMPM_SOUNDS, namestr, &ulSize);
   Temp=NULL;
   // Reserveer tijdelijk geheugen
   DosAllocMem((void **)&Temp, ulSize, PAG_COMMIT | PAG_READ | PAG_WRITE);
   PrfQueryProfileString(PrfMMPM, MMPM_SOUNDS, namestr, NULL, (void *)Temp, ulSize);
   // Vind het naam-gedeelte van de string
   deel2=strchr(Temp, '#');
   if (deel2!=NULL)
      {
      deel2++;
      deel3=strchr(deel2, '#');
      if (deel3!=NULL)
         {
         *deel3=0;
         }
      // Reserveer het geheugen (wordt vrijgegeven in WisNaamTabel())
      DosAllocMem((void **)&Naam, strlen(deel2)+1, PAG_COMMIT | PAG_READ | PAG_WRITE);
      strcpy(Naam, deel2);
      }
   else
      {
      DosAllocMem((void **)&Naam, strlen(NO_DESCRIPTION_AVAILABLE)+1, PAG_COMMIT | PAG_READ | PAG_WRITE);
      strcpy(Naam, NO_DESCRIPTION_AVAILABLE);
      }
   DosFreeMem(Temp);
   // Zet de pointer in de record
   pTabel->Naam=Naam;
   Temp=NULL;
   // Reserveer het geheugen voor de key-naam (wordt vrijgegeven in WisNaamTabel())
   DosAllocMem((void **)&Temp, strlen(namestr)+1, PAG_COMMIT | PAG_READ | PAG_WRITE);
   // Zet de pointer in de record
   pTabel->Key=Temp;
   // kopieer de key-naam naar de record
   strcpy(pTabel->Key, namestr);
   // vind de volgende key-naam
   namestr+=strlen(namestr)+1;
   // Is er nog een record nodig?
   if (namestr[0]!=0)
      {
      // Ja, reserveer het benodigde geheugen (wordt vrijgegeven in WisNaamTabel())
      DosAllocMem((void**)&(pTabel->Volgende), sizeof(TABEL), PAG_COMMIT | PAG_READ | PAG_WRITE);
      // en laat pTabel naar de volgende record wijzen
      pTabel=pTabel->Volgende;
      }
   else
      {
      // Nee,  zet de NULL pointer in pTabel->Volgende
      pTabel->Volgende=NULL;
      }
   }
// Ruim een beetje op
DosFreeMem(buffer);
namestr=NULL;
return Index; // Index geeft het aantal records
}

void WisSchema(char *Naam, PINFO pInfo, PTABEL Tabel)
{
PrfWriteProfileString(pInfo->PrfScheme, Naam, NULL, NULL);
// Herstel het schema <current>
if (strcmp(Naam, SCHEMA_HUIDIG)==0)
  LeesHuidigSchema(Tabel, pInfo);
}

void KopieerSchema(char *Origineel, char *Kopie, PINFO pInfo, PTABEL Tabel)
{
char Data[CCHMAXPATH];
PTABEL pTabel;
ULONG ulGrootte;

pTabel=Tabel;
// Vind de juiste record in de tabel
do
   {
   Data[0]=0;
   // Voor het geval het veld leeg is de naam en het standaard volume in data
   // zetten, zodat dat weggeschreven wordt
   sprintf(Data, "#%s#%i", pTabel->Naam, pInfo->DefaultVolume);
   // Lees veld in
   PrfQueryProfileString(pInfo->PrfScheme, Origineel, pTabel->Key, Data, Data, CCHMAXPATH);
   // schrijf veld
   PrfWriteProfileString(pInfo->PrfScheme, Kopie, pTabel->Key, Data);
   // Volgende record
   pTabel=pTabel->Volgende;
   }
while (pTabel!=NULL);
}

void HernoemSchema(char *Oud, char *Nieuw, PINFO pInfo, PTABEL Tabel)
{
PTABEL pTabel;
ULONG ulGrootte;
// Hernoemen is kopi‰ren en daarna wissen
KopieerSchema(Oud, Nieuw, pInfo, Tabel);
WisSchema(Oud, pInfo, Tabel);
// Zorg dat er weer een '<current>' schema is
if (strcmp(Oud, SCHEMA_HUIDIG)==0)
  LeesHuidigSchema(Tabel, pInfo);
}


void NieuwSchema(char *Naam, PINFO pInfo, PTABEL Tabel)
{
char Data[CCHMAXPATH];
PTABEL pTabel;
ULONG ulGrootte;

pTabel=Tabel;
// Vind de juiste record in de tabel
do
   {
   Data[0]=0;
   // Zet de naam en het standaard volume in het veld
   sprintf(Data, "#%s#%i", pTabel->Naam, pInfo->DefaultVolume);
   // schrijf het veld
   PrfWriteProfileString(pInfo->PrfScheme, Naam, pTabel->Key, Data);
   pTabel=pTabel->Volgende;
   }
while (pTabel!=NULL);
}

// Wordt aangeroepen als men op "Apply" drukt, en maakt het schema het actieve schema
void MaakSchemaActief(char *Naam, PTABEL Tabel, PINFO pInfo)
{
PTABEL pTabel;
ULONG Size;
char *Data;

pTabel=Tabel;
while (pTabel!=NULL)
   {
   // Vraag de grootte van de key op
   PrfQueryProfileSize(pInfo->PrfScheme, Naam, pTabel->Key, &Size);
   // Reserveer het geheugen
   DosAllocMem((void**)&Data, Size, PAG_COMMIT | PAG_READ | PAG_WRITE);
   // Lees de key in
   PrfQueryProfileString(pInfo->PrfScheme, Naam, pTabel->Key, NULL, Data, Size);
   // Schrijf de key
   PrfWriteProfileString(pInfo->PrfMMPM, MMPM_SOUNDS, pTabel->Key, Data);
   // Geef het geheugen vrij
   DosFreeMem(Data);
   // Laat pTabel->Key naar de volgende key wijzen
   pTabel=pTabel->Volgende;
   }
// Ververs het schema '<current>'
LeesHuidigSchema(Tabel, pInfo);
}

// Lees het huidige schema in en zet het in de eigen profile
void LeesHuidigSchema(PTABEL Tabel, PINFO pInfo)
{
PTABEL pTabel;
ULONG Size;
char *Data;

pTabel=Tabel;
while (pTabel!=NULL)
   {
   // Vraag de grootte van de key op
   PrfQueryProfileSize(pInfo->PrfMMPM, MMPM_SOUNDS, pTabel->Key, &Size);
   // Reserveer het geheugen
   DosAllocMem((void**)&Data, Size, PAG_COMMIT | PAG_READ | PAG_WRITE);
   // Lees de key in
   PrfQueryProfileString(pInfo->PrfMMPM, MMPM_SOUNDS, pTabel->Key, NULL, Data, Size);
   // Schrijf de key
   PrfWriteProfileString(pInfo->PrfScheme, SCHEMA_HUIDIG, pTabel->Key, Data);
   // Geef het geheugen vrij
   DosFreeMem(Data);
   // Laat pTabel->Key naar de volgende key wijzen
   pTabel=pTabel->Volgende;
   }
}


int OpenMMPMProfile(PINFO pInfo, char *Pad)
{
char pcTitle[CCHMAXPATH], pcMessage[CCHMAXPATH];
pInfo->PrfMMPM = PrfOpenProfile(pInfo->hab, Pad);
if (pInfo->PrfMMPM==NULLHANDLE)
   {
   WinLoadString(pInfo->hab, NULLHANDLE, NOMMPMINI_MESSAGE, CCHMAXPATH, pcMessage);
   WinLoadString(pInfo->hab, NULLHANDLE, ERROR_TITLE, CCHMAXPATH, pcTitle);
   WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, pcMessage, pcTitle, 0, MB_ERROR | MB_OK);
   return RC_ERROR;
   }
return RC_OK;
}

// Ok
// Leest het bestand SSM.INI in
int OpenSSMProfile(PINFO pInfo, char *Pad, char *SSMPad)
{
char pcTitle[CCHMAXPATH],
     pcMessage[CCHMAXPATH],
     pcTemp[6],
     VolledigeNaam[CCHMAXPATH];

strcpy(VolledigeNaam, SSMPad);
strcat(VolledigeNaam, SSMPROFILE);
pInfo->PrfSSM=PrfOpenProfile(pInfo->hab, VolledigeNaam);
if (pInfo->PrfSSM==NULLHANDLE) // Als het bestand niet geopend kan worden keer dan terug
   return RC_ERROR;
// Lees de standaard directory in
PrfQueryProfileString(pInfo->PrfSSM, SSM_SETTINGS, SSM_DEFAULT_SOUND_DIR, Pad, pInfo->DefaultSoundDir, CCHMAXPATH);
// Lees het standaard volume in, als dat niet bestaat dan 100%
pInfo->DefaultVolume=PrfQueryProfileInt(pInfo->PrfSSM, SSM_SETTINGS, SSM_DEFAULT_VOLUME, 100L);
// Moeten geluidsbestanden van ge‹mporteerde schema's in subdir opgeslagen worden?
PrfQueryProfileString(pInfo->PrfSSM, SSM_SETTINGS, SSM_SCHEMES_IN_SUBDIR, STR_TRUE, pcTemp, 6);
if (strcmp(pcTemp, STR_TRUE))
   pInfo->SchemesInSubDir=TRUE; // Ja
else
   pInfo->SchemesInSubDir=FALSE; // Nee
// Zijn de geluiden geactiveerd?
PrfQueryProfileString(pInfo->PrfMMPM, MMPM_SOUND_SETTINGS, MMPM_ENABLE_SOUNDS, STR_TRUE, pcTemp, 6);
if (strcmp(pcTemp, STR_TRUE))
   pInfo->EnableSounds=TRUE; // Ja
else
   pInfo->EnableSounds=FALSE; // Nee
// Standaard volume voor alles?
PrfQueryProfileString(pInfo->PrfMMPM, MMPM_SOUND_SETTINGS, MMPM_APPLY_VOLUME_TO_ALL, STR_FALSE, pcTemp, 6);
if (strcmp(pcTemp, STR_TRUE))
   pInfo->ApplyVolumeToAll=TRUE; // Ja
else
   pInfo->ApplyVolumeToAll=FALSE; // Nee

return RC_OK;
}

// Ok
// Vraagt het pad op naar MMOS/2 aan de hand van de omgevingsvariabele MMBASE
int VraagPadOp(PINFO pInfo, char *MMOS2Pad, char *GeluidenPad)
{
char pcTitle[CCHMAXPATH], pcMessage[CCHMAXPATH];
char *EnvVar;
// Lees de variabele MMBASE in om de MMOS2 directory te wten, zodat mmpm.ini ingelezen kan worden
EnvVar=getenv(MMBASE);
// Kopieer EnvVar naar een tijdelijke variabele
strcpy(MMOS2Pad, EnvVar);
// Controleer of MMBASE in het juiste formaat is, zoniet pas het dan aan
// Controleer of MMBASE niet leeg is. Zo wel be‰indig het programma
if (strlen(MMOS2Pad)==0)
   {
   WinLoadString(pInfo->hab, NULLHANDLE, NOMMPMINI_MESSAGE, CCHMAXPATH, pcMessage);
   WinLoadString(pInfo->hab, NULLHANDLE, ERROR_TITLE, CCHMAXPATH, pcTitle);
   WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, pcMessage, pcTitle, 0, MB_ERROR | MB_OK);
   return RC_ERROR;
   }
// Controleer of MMBASE niet met een ; eindigt.
if (MMOS2Pad[strlen(MMOS2Pad)-1]==';')
   MMOS2Pad[strlen(MMOS2Pad)-1]=0; // Verwijder de ;
// Controleer of MMBASE niet leeg is. Zo wel be‰indig het programma
if (strlen(MMOS2Pad)==0)
   {
   WinLoadString(pInfo->hab, NULLHANDLE, NOMMPMINI_MESSAGE, CCHMAXPATH, pcMessage);
   WinLoadString(pInfo->hab, NULLHANDLE, ERROR_TITLE, CCHMAXPATH, pcTitle);
   WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, pcMessage, pcTitle, 0, MB_ERROR | MB_OK);
   return RC_ERROR;
   }
// Controleer of MMBASE met een \ eindigt.
if (MMOS2Pad[strlen(MMOS2Pad)-1]!='\\')
   strcat(MMOS2Pad, "\\"); // Voeg een \ toe
// Maak een tijdelijke verwijzing naar de directory Sounds in de MMOS/2 directory
strcpy(GeluidenPad, MMOS2Pad);
strcat(GeluidenPad, SOUNDDIR);
// Construeer het volledige pad + naam voor MMPM.INI
strcat(MMOS2Pad, MMOS2PROFILE);
return RC_OK;
}

// Slaat een gebeurtenis op in INI bestand
void BewaarGebeurtenis(PINFO pInfo, PTABEL Tabel, PACTIE Actie)
{
PTABEL pTabel;
char Data[CCHMAXPATH];
ULONG ulGrootte;

pTabel=Tabel;
// Vind de juiste record in de tabel
do
   {
   if (pTabel->Index==Actie->Index)
      {
      sprintf(Data, "%s#%s#%i", Actie->Bestand, pTabel->Naam, Actie->Volume);
      PrfWriteProfileString(pInfo->PrfScheme, Actie->Schema, pTabel->Key, Data);
      break;
      }
   pTabel=pTabel->Volgende;
   }
while (pTabel!=NULL);
}

// Leest een gebeurtenis vanuit INI bestand
void LeesGebeurtenis(PINFO pInfo, PTABEL Tabel, PACTIE Actie)
{
PTABEL pTabel;
ULONG ulGrootte;
char Data[CCHMAXPATH], *deel2, *deel3;

pTabel=Tabel;
Data[0]=0;
// Vind de juiste record in de tabel
do
   {
   if (pTabel->Index==Actie->Index)
      {
      PrfQueryProfileString(pInfo->PrfScheme, Actie->Schema, pTabel->Key, "", Data, CCHMAXPATH);
      break;
      }
   pTabel=pTabel->Volgende;
   }
while (pTabel!=NULL);
// Vind het naam-gedeelte van de string
deel2=strchr(Data, '#');
if (deel2!=NULL)
   {
   deel2[0]=0;
   strcpy(Actie->Bestand, Data);
   deel2++;
   deel3=strchr(deel2, '#');
   if (deel3!=NULL)
      {
      sscanf(deel3, "#%i", &Actie->Volume);
      }
   else
      {
      Actie->Volume=pInfo->DefaultVolume;
      }
   }
else
   {
   strcpy(Actie->Bestand, Data);
   Actie->Volume=pInfo->DefaultVolume;
   }
}

// Ok
// Maakt controls niet actief
void DisableItems(HAB hab, HWND hwnd, int Which)
{
HWND menu;
menu=WinWindowFromID(hwnd, FID_MENU); // Vraag de handle naar het menu op
if (Which & DI_SCHEME) // Er is geen schema geselecteerd, deactiveer alles wat met schemas te maken heeft
   {
   WinEnableWindow(WinWindowFromID(hwnd, LB_ACTIONS), FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_COPY), FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_DELETE), FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_RENAME), FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_TEST), FALSE);
   WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(MI_EXPORT, TRUE), MPFROM2SHORT(MIA_DISABLED, MIA_DISABLED));
   }
if (Which & DI_ACTION) // Er is geen event geselecteerd, deactiveer alles wat met events te maken heeft
   {
   WinEnableWindow(WinWindowFromID(hwnd, EF_SOUND), FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_PLAY), FALSE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_LOCATE), FALSE);
   WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(MI_COPY, TRUE), MPFROM2SHORT(MIA_DISABLED, MIA_DISABLED));
   WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(MI_CUT, TRUE), MPFROM2SHORT(MIA_DISABLED, MIA_DISABLED));
   WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(MI_PASTE, TRUE), MPFROM2SHORT(MIA_DISABLED, MIA_DISABLED));
   }
if (Which & DI_CHANGE) // Er is geen wijziging die ongedaan gemaakt kan worden, deactiveer de 'Undo' knoppen
   {
   WinEnableWindow(WinWindowFromID(hwnd, PB_UNDO), FALSE);
//   WinEnableWindow(WinWindowFromID(hwnd, PB_UNDOALL), FALSE);
   WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(MI_UNDO, TRUE), MPFROM2SHORT(MIA_DISABLED, MIA_DISABLED));
   }
}

// Ok
// Maakt controls actief
void EnableItems(HAB hab, HWND hwnd, int Which)
{
HWND menu;
menu=WinWindowFromID(hwnd, FID_MENU);
if (Which & DI_SCHEME)
   {
   WinEnableWindow(WinWindowFromID(hwnd, LB_ACTIONS), TRUE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_COPY), TRUE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_DELETE), TRUE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_RENAME), TRUE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_TEST), TRUE);
   WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(MI_EXPORT, TRUE), MPFROM2SHORT(MIA_DISABLED, ~MIA_DISABLED));
   }
if (Which & DI_ACTION)
   {
   WinEnableWindow(WinWindowFromID(hwnd, EF_SOUND), TRUE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_PLAY), TRUE);
   WinEnableWindow(WinWindowFromID(hwnd, PB_LOCATE), TRUE);
   WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(MI_COPY, TRUE), MPFROM2SHORT(MIA_DISABLED, ~MIA_DISABLED));
   WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(MI_CUT, TRUE), MPFROM2SHORT(MIA_DISABLED, ~MIA_DISABLED));
   WinOpenClipbrd(hab);
   if (WinQueryClipbrdData(hab,CF_TEXT))
      {
      WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(MI_PASTE, TRUE), MPFROM2SHORT(MIA_DISABLED, ~MIA_DISABLED));
      }
   WinCloseClipbrd(hab);
   }
if (Which & DI_CHANGE)
   {
   WinEnableWindow(WinWindowFromID(hwnd, PB_UNDO), TRUE);
//   WinEnableWindow(WinWindowFromID(hwnd, PB_UNDOALL), TRUE);
   WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(MI_UNDO, TRUE), MPFROM2SHORT(MIA_DISABLED, ~MIA_DISABLED));
   }
}


void ImportSysSchemes(PTABEL Tabel, PINFO pInfo)
{
/* Inlezen lijst met Schema's vervolgens per schema een tabel bouwen en deze opslaan in eigen INI bestand */
PTABEL pTabel;
ULONG Size;
char *Data, ssmData[CCHMAXPATH], *Schema, *KeyNaam, *Schemas;

PrfQueryProfileSize(HINI_SYSTEMPROFILE, "PM_SOUND_SCHEMES_LIST", NULL, &Size);
DosAllocMem((void**)&Schemas, Size, PAG_COMMIT |PAG_READ | PAG_WRITE);
PrfQueryProfileString(HINI_SYSTEMPROFILE, "PM_SOUND_SCHEMES_LIST", NULL, NULL, Schemas, Size);
Schema=Schemas;
while (Schema[0]!=0)
   {
   PrfQueryProfileSize(HINI_SYSTEMPROFILE, "PM_SOUND_SCHEMES_LIST", Schema, &Size);
   DosAllocMem((void**)&KeyNaam, Size, PAG_COMMIT |PAG_READ | PAG_WRITE);
   PrfQueryProfileString(HINI_SYSTEMPROFILE, "PM_SOUND_SCHEMES_LIST", Schema, NULL, KeyNaam, Size);
   pTabel=Tabel;
   while (pTabel!=NULL)
      {
      // Vraag de grootte van de key op
      if (PrfQueryProfileSize(HINI_SYSTEMPROFILE, KeyNaam, pTabel->Key, &Size))
         {
         // Reserveer het geheugen
         DosAllocMem((void**)&Data, Size, PAG_COMMIT | PAG_READ | PAG_WRITE);
         // Lees de key in
         PrfQueryProfileString(HINI_SYSTEMPROFILE, KeyNaam, pTabel->Key, NULL, Data, Size);
         // Schrijf de key
         sprintf(ssmData, "%s#%s#%i", Data, pTabel->Naam, pInfo->DefaultVolume);
         PrfWriteProfileString(pInfo->PrfScheme, Schema, pTabel->Key, ssmData);
         // Geef het geheugen vrij
         DosFreeMem(Data);
         }
      // Laat pTabel->Key naar de volgende key wijzen
      pTabel=pTabel->Volgende;
      }
   DosFreeMem(KeyNaam);
   Schema+=strlen(Schema)+1;
   }
DosFreeMem(Schemas);
}
