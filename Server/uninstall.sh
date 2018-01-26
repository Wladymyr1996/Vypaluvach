#!/bin/bash

if [ `id -u` -ne 0 ]
then
	echo "[ERROR] - this script can run only root user"
	exit
fi

rm /usr/bin/OPiVypaluvach
