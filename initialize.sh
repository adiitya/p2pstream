#!/bin/bash

mkdir p2pstream

cd p2pstream

mkdir client
mkdir server

mkdir client/include
mkdir client/source

mkdir server/include
mkdir server/source

mkdir experiment

touch Makefile
touch .gitignore

echo "/experiment/" > .gitignore

git init

cd ..