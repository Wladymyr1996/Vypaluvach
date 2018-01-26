#!/bin/bash

if [ `id -u` -ne 0 ]
then
	echo "[ERROR] - this script can run only root user"
	exit
fi

qmake
if [ $? != 0 ]
then
	echo "[ERROR] - qmake error."
	exit
fi

make 
if [ $? != 0 ]
	echo "[ERROR] - make error."
	make clear
	exit
fi
make clean

cp OPiVypaluvach /usr/bin/OPiVypaluvach
