#!/bin/bash

rm -rf ./build/*
./build.sh $1
./flash.sh $1