#!/bin/bash

stty -F /dev/ttyACM0 raw 115200
cat /dev/ttyACM0

stty -F /dev/ttyACM1 raw 115200
cat /dev/ttyACM1
