#!/bin/bash
# LinuxCNC-Ethercat install script
# Written by: Sean Froome
echo "**********************************************"
echo " "
echo "Removing old build files"
echo " "
echo "**********************************************"
sudo make clean

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
echo "**********************************************"
make all modules
sudo make
sudo make install

echo "**********************************************"
echo " "
echo "Copying Config Files"
echo " "
echo "**********************************************"
#TODO make this more robust.
sudo cp src/lcec_conf ~/RMDCNC-Core/linuxcnc/configs/sim-rmd-rtr


echo "Install script complete."
