/* Import Schemes from the OS/2 System INI file */
/* Copyright 1999 by D.J. van Enckevort */
/* Last edited 12-7-1999 */
/* Corrected MMPM variable  and renamed file */
call RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
call SysLoadFuncs

/* read the descriptions from the MMPM INI file */

dummy=value('MMBASE',,'OS2ENVIRONMENT')
parse var dummy MMPM';'
MMPM=MMPM'\MMPM.INI'

Say "Reading names"
do key=0 to 12
  sound=SysINI(MMPM, 'MMPM2_AlarmSounds', key)
  parse var sound file'#'name'#'volume
  names.key=name
  volumes.key=volume
  Say key names.key
end

/* read the Schemes from System INI */

Say "Reading Schemes"
rc=SysINI('SYSTEM', 'PM_SOUND_SCHEMES_LIST', 'ALL:', Schemes.);
if rc\='ERROR:' then
do
  do i=1 to Schemes.0
      Say Schemes.i
      Scheme=SysINI('SYSTEM', 'PM_SOUND_SCHEMES_LIST', Schemes.i)
      do key=0 to 12
        file=SysINI('SYSTEM', Scheme, key)
        sound=file'#'names.key'#'volumes.key
        say key sound
        rc=SysINI('SCHEME.INI', Schemes.i, key, sound)
      end
  end
end
