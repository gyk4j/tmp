@echo off

SETLOCAL

SET PATH=%PATH%;C:\mingw32\mingw32\bin
SET CGO_ENABLED=1
SET GOOS=windows
SET GOARCH=386

del wreck.exe
go build

ENDLOCAL
