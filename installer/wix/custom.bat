@echo off

cls

setlocal

set WIX_PRODUCT=custom

if not exist "build\." mkdir build

REM del /q build\*.msi
REM del /q build\*.wixobj
REM del /q build\*.wixpdb

candle -nologo -out build\cuidlga.wixobj cuidlga.wxs
candle -nologo -out build\cuidlgb.wixobj cuidlgb.wxs

candle ^
  -nologo ^
  -out .\build\%WIX_PRODUCT%.wixobj ^
  %WIX_PRODUCT%.wxs 
  
if errorlevel 1 goto end
  
light ^
  -nologo ^
  -ext WixUIExtension ^
  -out .\build\%WIX_PRODUCT%.msi ^
  .\build\%WIX_PRODUCT%.wixobj .\build\cuidlga.wixobj .\build\cuidlgb.wixobj
  
if errorlevel 1 goto end
  
:end
if errorlevel 1 (
  echo.
  echo ERROR: An error occurred.
  echo.
)

endlocal