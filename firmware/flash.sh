#!/bin/bash
# Flashing script
set -x
ARDUINO_CLI=$HOME/bin/arduino-cli
BOARD_REGEX='[[:alnum:]]\+:[[:alnum:]]\+:[-_[:alnum:]]\+'
BOARD=$($ARDUINO_CLI board list | grep -o  $BOARD_REGEX) 

#ESP32 board not detected automatically So we give manual board name for esp32
if [ "$BOARD" = "" ]; then
	BOARD=esp32:esp32:esp32
fi
PORT="/dev/ttyUSB0"

#Install Dependent libraries
$ARDUINO_CLI lib install pubsubclient &&

# Compile the sketch
$ARDUINO_CLI compile  --export-binaries -b $BOARD . &&

# Upload the compiled sketch to the board
$ARDUINO_CLI upload -p $PORT --fqbn $BOARD . &&
 
echo "Arduino flashed successfully!" 
