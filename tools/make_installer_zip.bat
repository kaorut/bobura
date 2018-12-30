@echo off
rem Makes an installer zip file.
rem Copyright (C) 2007-2019 kaoru
rem $Id$

if not exist bin\installer.Release exit /b 1
pushd bin\installer.Release

powershell Compress-Archive -Path setup.exe, bobura.Win32.msi, bobura.x64.msi -DestinationPath ..\bobura.zip -CompressionLevel Optimal -Force

popd
