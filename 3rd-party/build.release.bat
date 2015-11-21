@echo off

set MSBUILD_PATH="C:\Program Files (x86)\MSBuild\12.0\Bin\"

if exist %MSBUILD_PATH% goto build

@echo Not able to find MSBuild executable. Please check your Microsoft Build Tool installation.
goto end

:build
cd %MSBUILD_PATH%

set PROJECT_PATH=%~dp0
msbuild.exe %PROJECT_PATH%3rd-party.sln /t:Rebuild /p:configuration=release

:end
pause