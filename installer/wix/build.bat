@echo off

cls

setlocal

set WIX_PRODUCT=product

if not exist "build\." mkdir build

REM del /q build\*.msi
REM del /q build\*.wixobj
REM del /q build\*.wixpdb

candle ^
  -out .\build\%WIX_PRODUCT%.wixobj ^
  %WIX_PRODUCT%.wxs
  
if errorlevel 1 goto end
  
light ^
  -cc .\build ^
  -reusecab ^
  -ext WixUIExtension ^
  -ext WixUtilExtension ^
  -out .\build\%WIX_PRODUCT%.msi ^
  .\build\%WIX_PRODUCT%.wixobj
  
if errorlevel 1 goto end
  
:end
if errorlevel 1 (
  echo.
  echo ERROR: An error occurred.
  echo.
)

endlocal