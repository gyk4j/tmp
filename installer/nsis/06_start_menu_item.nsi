# Name the installer
OutFile "installer.exe"
 
# default section
Section
 
    # create a shortcut named "new shortcut" in the start menu programs directory
    # presently, the new shortcut doesn't call anything (the second field is blank)
    CreateShortcut "$SMPROGRAMS\new shortcut.lnk" ""
 
    # to delete shortcut, go to start menu directory and manually delete it
 
# default sec end
SectionEnd