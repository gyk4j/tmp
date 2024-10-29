@echo off

SETLOCAL

:include
SET PATH=%PATH%;C:\mingw32\mingw32\bin
SET CGO_ENABLED=1
SET GOOS=windows
SET GOARCH=386
SET PATH=%CD%\bin;%PATH%

if not "%1" == "" goto %1 

:all
CALL :goexiftool
CALL :go7z
CALL :mediainfo
goto end

:goexiftool
go build -o bin\goexiftool.exe .\cmd\goexiftool
bin\goexiftool test\Chrysanthemum.jpg
goto end

:go7z
go build -o bin\go7z.exe .\cmd\go7z
bin\go7z.exe test\Core-15.0.iso
goto end

:mediainfo
go build -o bin\mediainfo.exe .\cmd\mediainfo
bin\mediainfo test\Wildlife.wmv
goto end

:clean
rd /s /q out
del bin\goexiftool.exe
del bin\go7z.exe
del bin\mediainfo.exe
go mod tidy
goto end

:end

ENDLOCAL
