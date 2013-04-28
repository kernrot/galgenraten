@echo off
setlocal enabledelayedexpansion

echo ===================================================
echo  Galgenraten - Build mit Cygwin C++ Compiler (g++)
echo ===================================================

:: Cygwin Pfad prufen
set "CYGWIN_BIN=C:\cygwin64\bin"
if exist "%CYGWIN_BIN%" (
    set "PATH=%CYGWIN_BIN%;%PATH%"
)

:: Bevorzuge MinGW Toolchain in Cygwin fur native Windows-Konsole/conio
set "CXX="
if exist "%CYGWIN_BIN%\x86_64-w64-mingw32-g++.exe" (
    set "CXX=%CYGWIN_BIN%\x86_64-w64-mingw32-g++.exe"
) else if exist "%CYGWIN_BIN%\g++.exe" (
    set "CXX=%CYGWIN_BIN%\g++.exe"
) else (
    where g++.exe >nul 2>nul
    if !errorlevel! equ 0 (
        set "CXX=g++.exe"
    )
)

if "%CXX%"=="" (
    echo [FEHLER] C++ Compiler wurde nicht gefunden!
    echo Bitte stellen Sie sicher, dass Cygwin unter C:\cygwin64 installiert ist oder g++ im PATH liegt.
    pause
    exit /b 1
)

:: Zielordner Release erstellen
if not exist "Release" (
    mkdir "Release"
)

echo.
echo Kompiliere Quelldateien aus "Galgenraten" mit %CXX%...
"%CXX%" -O3 -fpermissive -finput-charset=windows-1252 -I"Galgenraten" ^
    Galgenraten\FktDisp.cpp ^
    Galgenraten\FktGR.cpp ^
    Galgenraten\FktK.cpp ^
    Galgenraten\FktProtokoll.cpp ^
    Galgenraten\FktWoerterbuch.cpp ^
    Galgenraten\MainGR.cpp ^
    -o "Release\Galgenraten.exe"

if %errorlevel% neq 0 (
    echo.
    echo [FEHLER] Die Kompilierung ist fehlgeschlagen!
    pause
    exit /b %errorlevel%
)

:: Standard-Worterbuch nach Release kopieren
copy /Y "ratewoerter.txt" "Release\ratewoerter.txt" >nul

echo.
echo [ERFOLG] Erstellung abgeschlossen!
echo Ausgabedatei: Release\Galgenraten.exe
echo ===================================================
endlocal
