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
  
light ^
  -cc .\build ^
  -reusecab ^
  -ext WixUIExtension ^
  -out .\build\%WIX_PRODUCT%.msi ^
  .\build\%WIX_PRODUCT%.wixobj
  
endlocal