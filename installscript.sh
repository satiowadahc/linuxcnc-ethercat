#!/bin/bash
# LinuxCNC-Ethercat install script
# Written by: Sean Froome

# Please check the install documentation before running this script!


if [ "$1" = "" ]; then
echo "No path to RMDCNC folder given"
else
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
LCNC_ETHERCAT_DIR=$PWD
echo "your current working directory is: $LCNC_ETHERCAT_DIR"

# Make sure you point to the correct config in RMDCNC-Core\linuxcnc\configs.
# Must be passed in as an argument when script is run.
# example: ./installscript.sh "~/RMDCNC-Core\linuxcnc\configs\sim-rmd-rtr"
sudo cp $LCNC_ETHERCAT_DIR/src/lcec_conf "$1"
echo "Install script complete."
fi
