@echo off

:: assumes `pio` binary is present & in path

:: config
set PI_USER=jokil
set PI_HOST=joshberrypi.joshualung.com
set REMOTE_DIR=~/tools/esp-flashing-env/pio/firmware-files

echo "Building, Uploading & Flashing Project"
C:\Users\jo_ki\.platformio\penv\Scripts\platformio.exe run

if %errorlevel% neq 0 (
    echo error building
    exit /b %errorlevel% 
)


echo "Transferring binaries to %PI_USER%@%PI_HOST%:%REMOTE_DIR%"
scp "C:\Users\jo_ki\.platformio\packages\framework-arduinoespressif32\tools\partitions\boot_app0.bin" .pio\build\default\bootloader.bin .pio\build\default\firmware.bin .pio\build\default\partitions.bin %PI_USER%@%PI_HOST%:%REMOTE_DIR%

ssh %PI_USER%@%PI_HOST% "cd ~/tools/esp-flashing-env/pio && ./flash.sh"

echo "Done"