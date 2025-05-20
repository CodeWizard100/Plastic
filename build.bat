@echo off
setlocal

echo Generating Visual Studio solution...

:: Path to portable CMake
set "CMAKE_EXE=tools\windows\cmake\bin\cmake.exe"

if not exist "%CMAKE_EXE%" (
    echo ERROR: Portable CMake not found at "%CMAKE_EXE%"
    exit /b 1
)

:: Default MSBuild search locations
set "MSBUILD_PATH="
set "MSBUILD_DEFAULT=C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe"
set "MSBUILD_FALLBACK=D:\VisualStudio\MSBuild\Current\Bin\MSBuild.exe"

:: Try default MSBuild path
if exist "%MSBUILD_DEFAULT%" (
    set "MSBUILD_PATH=%MSBUILD_DEFAULT%"
) else (
    :: Try fallback MSBuild path
    if exist "%MSBUILD_FALLBACK%" (
        set "MSBUILD_PATH=%MSBUILD_FALLBACK%"
    )
)

:: If MSBuild not found in either location, ask user
if not defined MSBUILD_PATH (
    set /p "MSBUILD_PATH=MSBuild.exe not found in default locations. Please enter full path to MSBuild.exe: "
    if not exist "%MSBUILD_PATH%" (
        echo ERROR: MSBuild.exe not found at "%MSBUILD_PATH%"
        exit /b 1
    )
)

:: Run CMake to generate solution
"%CMAKE_EXE%" -B build -G "Visual Studio 17 2022" -A x64
if errorlevel 1 (
    echo CMake generation failed.
    exit /b 1
)

echo Building all targets...
"%MSBUILD_PATH%" build\Plastic.sln /p:Configuration=Release /m /p:Platform=x64
if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Build succeeded.
exit /b 0
endlocal