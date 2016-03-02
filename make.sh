#!/bin/bash

./initialize.sh

cd ./core
make

cd ../client
make

cd ../server
make

cd ..