Option Explicit

Dim aWhiteList(2)
aWhiteList(1) = "SSID1"
aWhiteList(2) = "SSID2"
' Append more if needed. Adjust the size on line 3.

Function InWhiteList(a, v)
    Dim i
    
    InWhiteList = False
    For i = 1 To UBound(a)
        'WScript.Echo "[InWhiteList] " & a(i) & " =?= " & v
        
        If a(i) = v Then
            InWhiteList = True
            Exit Function
        End If
    Next
End Function

Function DeleteProfile(name)
    On Error Resume Next
    Dim objShell
    objShell = CreateObject("WScript.Shell")
    
    WScript.Echo "Deleting " & name
    objShell.RegDelete(name)
        
    If Err.Number <> 0 Then
        WScript.Echo "Error #" & Err.Number & ": " & Err.Description
        DeleteProfile = Err.Number
        Err.Clear
    Else
        DeleteProfile = 0
    End If
End Function

Const HKEY_LOCAL_MACHINE = &H80000002
Dim oReg : Set oReg = GetObject("winmgmts:{impersonationLevel=impersonate}!\\.\root\default:StdRegProv")
Dim oShell : Set oShell = CreateObject("WScript.Shell")
Dim sProfiles, aProfiles, sProfileGuid, sProfileName, bAction

' Get all keys within sPath
sProfiles = "SOFTWARE\Microsoft\Windows NT\CurrentVersion\NetworkList\Profiles"
oReg.EnumKey HKEY_LOCAL_MACHINE, sProfiles, aProfiles

' Loop through each key
For Each sProfileGuid In aProfiles
    oReg.GetStringValue HKEY_LOCAL_MACHINE, sProfiles & "\" & sProfileGuid, "ProfileName", sProfileName
    bAction = InWhiteList(aWhiteList, sProfileName)
    Wscript.Echo sProfileGuid & " = " & sProfileName & " - " & bAction
    
    If Not bAction Then
        DeleteProfile("HKLM\" & sProfiles & "\" & sProfileGuid & "\")
    End If
Next