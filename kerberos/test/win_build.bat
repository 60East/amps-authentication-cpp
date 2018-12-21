setlocal
  
set TARGET=%1
if not defined TARGET (
  set TARGET=x64
) 
  
IF DEFINED VCINSTALLDIR (
  pushd "%VCINSTALLDIR%"
  IF EXIST "vcvarsall.bat" (
    call vcvarsall.bat %TARGET%
  ) ELSE (
    call Auxiliary\Build\vcvarsall.bat %TARGET%
  )
  popd
) 

IF EXIST "%WindowsSDKDIR%\bin\setenv.cmd" (
  call setenv %TARGET%
)

nmake clean
nmake

