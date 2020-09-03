#!/bin/bash
# LinuxCNC-Ethercat install script
# Written by: Sean Froome
# Last Updated September 3, 2020

echo "**********************************************"
echo " "
echo "Installing necessary packages"
echo " "
echo "**********************************************"
sudo apt update
sudo apt upgrade
sudo apt install libexpat1-dev

echo "**********************************************"
echo " "
echo "Installing linuxcnc-ethercat files"
echo " "
echo "***************************************"
make all modules
sudo make
sudo make install

echo "Install script complete."
