@echo off
rem This script compiles main.c and integrity_check_db.c into an executable

rem Compile the program
gcc -o integrity_checker main.c integrity_check_db.c

rem Check if compilation succeeded
if %errorlevel% neq 0 (
    echo Compilation failed. Make sure gcc is installed and added to the PATH.
    pause
    exit /b
)

echo Compilation successful! The executable integrity_checker.exe has been created.
pause

