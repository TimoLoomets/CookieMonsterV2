#!/bin/bash

mkdir -p build
cd build

cmake .. -DMCU=IMXRT1062_T41
make $1_hex

