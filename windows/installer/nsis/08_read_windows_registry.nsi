# name the installer
OutFile "installer.exe"
 
#default section start
Section
 
    # read the value from the registry into the $0 register
    ReadRegStr $0 HKLM "SOFTWARE\Microsoft\Windows NT\CurrentVersion" "CurrentVersion"
 
    # print the results in a popup message box
    MessageBox MB_OK "version: $0"
 
# default section end
SectionEnd