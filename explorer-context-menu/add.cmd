reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_create /ve /t REG_SZ /d "Create Skull" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_create /v Icon /t REG_SZ /d "C:\m\mushroom.ico" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_create /v HasLUAShield /t REG_SZ /d "" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_create\command /ve /t REG_SZ /d "\"C:\m\skull.cmd\" /c \"%%1\"" /f

reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_retrieve /ve /t REG_SZ /d "Retrieve Skull" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_retrieve /v Icon /t REG_SZ /d "C:\m\diamond.ico" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_retrieve /v HasLUAShield /t REG_SZ /d "" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_retrieve\command /ve /t REG_SZ /d "\"C:\m\skull.cmd\" /r \"%%1\"" /f

reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_update /ve /t REG_SZ /d "Update Skull" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_update /v Icon /t REG_SZ /d "C:\m\money.ico" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_update /v HasLUAShield /t REG_SZ /d "" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_update\command /ve /t REG_SZ /d "\"C:\m\skull.cmd\" /u \"%%1\"" /f

reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_delete /ve /t REG_SZ /d "Delete Skull" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_delete /v Icon /t REG_SZ /d "C:\m\gold.ico" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_delete /v HasLUAShield /t REG_SZ /d "" /f
reg add HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\CommandStore\shell\skull_delete\command /ve /t REG_SZ /d "\"C:\m\skull.cmd\" /d \"%%1\"" /f

reg add HKLM\SOFTWARE\Classes\*\shell\skull /v MUIVerb /t REG_SZ /d "Skull File"
reg add HKLM\SOFTWARE\Classes\*\shell\skull /v Icon /t REG_SZ /d "C:\m\skull.ico"
reg add HKLM\SOFTWARE\Classes\*\shell\skull /v SubCommands /t REG_SZ /d "skull_create; skull_retrieve; skull_update; skull_delete"

reg add HKLM\SOFTWARE\Classes\Directory\shell\skull /v MUIVerb /t REG_SZ /d "Skull Directory"
reg add HKLM\SOFTWARE\Classes\Directory\shell\skull /v Icon /t REG_SZ /d "C:\m\skull.ico"
reg add HKLM\SOFTWARE\Classes\Directory\shell\skull /v SubCommands /t REG_SZ /d "skull_create; skull_retrieve; skull_update; skull_delete"

reg add HKLM\SOFTWARE\Classes\Directory\Background\shell\skull /v MUIVerb /t REG_SZ /d "Skull Tools"
reg add HKLM\SOFTWARE\Classes\Directory\Background\shell\skull /v Icon /t REG_SZ /d "C:\m\skull.ico"
reg add HKLM\SOFTWARE\Classes\Directory\Background\shell\skull\command /ve /t REG_SZ /d "\"C:\m\skull.cmd\" /b \"%V\""

reg add HKLM\SOFTWARE\Classes\Drive\shell\skull /v MUIVerb /t REG_SZ /d "Skull Drive"
reg add HKLM\SOFTWARE\Classes\Drive\shell\skull /v Icon /t REG_SZ /d "C:\m\skull.ico"
reg add HKLM\SOFTWARE\Classes\Drive\shell\skull /v SubCommands /t REG_SZ /d "skull_create; skull_retrieve; skull_update; skull_delete"

reg add HKLM\SOFTWARE\Classes\LibraryFolder\shell\skull /v MUIVerb /t REG_SZ /d "Skull LibraryFolder"
reg add HKLM\SOFTWARE\Classes\LibraryFolder\shell\skull /v Icon /t REG_SZ /d "C:\m\skull.ico"
reg add HKLM\SOFTWARE\Classes\LibraryFolder\shell\skull /v SubCommands /t REG_SZ /d "skull_create; skull_retrieve; skull_update; skull_delete"

reg add HKLM\SOFTWARE\Classes\LibraryFolder\background\shell\skull /v MUIVerb /t REG_SZ /d "Skull LibraryFolder Background"
reg add HKLM\SOFTWARE\Classes\LibraryFolder\background\shell\skull /v Icon /t REG_SZ /d "C:\m\skull.ico"
reg add HKLM\SOFTWARE\Classes\LibraryFolder\background\shell\skull\command /ve /t REG_SZ /d "\"C:\m\skull.cmd\" /b \"%V\""
