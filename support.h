#ifndef SUPPORT_H // Test om dubbele declaraties te voorkomen

#define SUPPORT_H // Definieer SUPPORT_H om hierop te kunnen testen

// Window messages
#define UM_UPDATE WM_USER+1

// Vlaggen voor activeren / deactiveren knoppen en menus
#define DI_SCHEME 1
#define DI_ACTION 2
#define DI_CHANGE 4
#define DI_FIND   8

// Returncodes
#define RC_OK 0
#define RC_ERROR -1

// Teksten
#define STR_TRUE "TRUE"
#define STR_FALSE "FALSE"
#define MMBASE "MMBASE"


// Namen van directories
#define SOUNDDIR "Sounds\\"

// Extensies
#define WAVEFILES "*.WAV"

// Namen van semaforen
#define SEMAFOOR "\\SEM32\\SSM"

// Namen van Profiles
#define MMOS2PROFILE "mmpm.ini"
#define SSMPROFILE   "ssm.ini"
#define SCHEMEPROFILE "scheme.ini"

// Naam van executable
#define SSM_EXECUTABLE "ssm.exe"

// Namen van Applications en Keys in Profiles
#define SSM_SETTINGS "Settings"
#define SSM_DEFAULT_SOUND_DIR "DefaultSoundDir"
#define SSM_DEFAULT_VOLUME "DefaultVolume"
#define SSM_SCHEMES_IN_INI "SchemesInINI"
#define SSM_SCHEMES_IN_SUBDIR "SchemesInSubDir"
#define MMPM_SOUNDS "MMPM2_AlarmSounds"
#define MMPM_SOUND_SETTINGS "MMPM2_AlarmSoundsData"
#define MMPM_APPLY_VOLUME_TO_ALL "ApplyVolumeToAll"
#define MMPM_ENABLE_SOUNDS "EnableSounds"
#define MMPM_VOLUME "Volume"
#define OS2SYS_SCHEME_LIST "PM_SOUND_SCHEMES_LIST"
#define NO_DESCRIPTION_AVAILABLE "No description available"
#define SCHEMA_HUIDIG "<current>"

// Structuur voor het doorgeven van initialisatie informatie
typedef struct _INFO
{
  char DefaultSoundDir[CCHMAXPATH];
  BOOL SchemesInINI,
       SchemesInSubDir,
       EnableSounds,
       ApplyVolumeToAll;
  char DefaultVolume;
  HINI PrfSSM, PrfMMPM, PrfScheme;
  HAB hab;
} INFO, *PINFO;


// parameters die doorgegeven moeten worden om het juiste vraagdialoog te tonen
typedef struct _CREATEPARAMS
{
char Title[81], StaticText[81], SchemeName[201];
BOOL ok;
} CREATEPARAMS;

typedef struct _TABEL
{
char *Naam, *Key;
int Index;
_TABEL *Volgende;
} TABEL, *PTABEL;

typedef struct _ACTIE
{
char Bestand[CCHMAXPATH], Schema[201];
int Index, Volume;
} ACTIE, *PACTIE;

typedef struct _TESTPARAMS
{
char Schema[201];
PINFO Info;
} TESTPARAMS, *PTESTPARAMS;

// Procedures
void EnableItems(HAB hab, HWND hwnd, int Which); // Activeer bepaalde knoppen
void DisableItems(HAB hab, HWND hwnd, int Which); // Deactiveer bepaalde knoppen
int LeesNaam(PTABEL Tabel, HINI PrfMMPM); // Lees de namen van de gebeurtenissen in geef het aantal terug
void WisNaamTabel(PTABEL pTabel); // Geef het gereserveerde geheugen vrij
void WisSchema(char *Naam, PINFO pInfo, PTABEL Tabel);
void KopieerSchema(char *Origineel, char *Kopie, PINFO pInfo, PTABEL Tabel);
void HernoemSchema(char *Oud, char *Nieuw, PINFO pInfo, PTABEL Tabel);
void NieuwSchema(char *Naam, PINFO pInfo, PTABEL Tabel);
void MaakSchemaActief(char *Naam, PTABEL pTabel, PINFO pInfo);
void LeesHuidigSchema(PTABEL Tabel, PINFO pInfo); // Lees het huidige schema in en zet het in de eigen profile
int OpenMMPMProfile(PINFO pInit, char *Pad);
int OpenSSMProfile(PINFO pInit, char *Pad, char *SSMPad);
int VraagPadOp(PINFO pInfo, char *MMOS2Pad, char *GeluidenPad);
void BewaarGebeurtenis(PINFO pInfo, PTABEL Tabel, PACTIE Actie);
void LeesGebeurtenis(PINFO pInfo, PTABEL Tabel, PACTIE Actie);
void ImportSysSchemes(PTABEL Tabel, PINFO pInfo);

#endif
