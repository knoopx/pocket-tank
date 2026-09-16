#!/bin/bash
# flash.sh - the only way to flash the tank. Builds and flashes the app;
# `--model` also writes the model partition. Back up the save area first
# (esptool read_flash 0x9000 0x6000 -> ~/Documents): a reflash wipes the
# live tank, so keep the snapshot as the record of what was on it.
#
#   tools/flash.sh              # build, flash app
#   tools/flash.sh --model      # ... and model/out/model_q4.bin at 0x410000
#   tools/flash.sh --no-build   # flash the existing build
set -u
cd "$(dirname "$0")/.."
BUILD=~/.cache/pocket-tank/fw-build
PORT=$(ls /dev/ttyACM* 2>/dev/null | head -1)
[ -n "$PORT" ] || { echo "flash: no /dev/ttyACM* - wake the tank (BOOT) first"; exit 1; }
. ~/esp/esp-idf/export.sh > /dev/null 2>&1 || { echo "flash: ESP-IDF export failed"; exit 1; }
cd firmware
if [[ " $* " != *" --no-build "* ]]; then
  idf.py -B "$BUILD" build 2>&1 | grep -E "error|binary size|build complete"
  [ "${PIPESTATUS[0]}" -eq 0 ] || { echo "flash: BUILD FAILED - nothing flashed"; exit 1; }
fi
if [[ " $* " == *" --model "* ]]; then
  python -m esptool --chip esp32p4 -p "$PORT" -b 460800 write_flash 0x410000 ../model/out/model_q4.bin 2>&1 | grep -E "Wrote|verified|rror"
  sleep 3
fi
idf.py -B "$BUILD" -p "$PORT" flash 2>&1 | grep -E "verified|Hard resetting|rror" | tail -2
echo "flash: done - the tank boots now"
