; VersionInfo.nsi
;
; This script shows you how to add version information to an installer.
; Windows shows this information on the Version tab of the File properties.

;--------------------------------

Name "Version Info"

OutFile "VersionInfo.exe"

LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"
;--------------------------------
;Version Information

VIProductVersion "7.8.9.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "{FileDescription}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "5.6.7"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "{ProductName}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductVersion" "1.2.3.4"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "A test comment"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "{CompanyName}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "{LegalTrademarks}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "{LegalCopyright}"
  
;--------------------------------

Section ""

SectionEnd
