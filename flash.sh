#!/bin/bash

cd build
teensy_loader_cli --mcu=TEENSY41 -w $1.hex