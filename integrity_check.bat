@echo off
REM Compiling the C program
gcc main.c -o main.exe

REM Check if the compilation succeeded
if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b %errorlevel%
)

REM Running the program
main.exe

pause
