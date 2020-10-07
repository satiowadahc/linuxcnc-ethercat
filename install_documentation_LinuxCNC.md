/*************************************************************
Installing the LinuxCNC Ethercat HAL driver

Written By: Sean Froome
Last Modified: September 3, 2020
*************************************************************/

This guide assumes you already have Ethercat installed. If you do not,
install it as it is a prerequisite to the linuxCNC-ethercat HAL drivers.

This guide was based on this google docs tutorial found here:
https://docs.google.com/document/d/1GiB065ZIAaoMHPtVfTg9JV1Kn-19xGQl2X9DM9-THNM/edit#

/****************************************************
INSTALLING LINUXCNC
***************************************************/

Install the LinuxCNC debs from the RMD gitlab repo.

http://192.168.1.104/gitlab/rmd/rmdcnc/linuxcnc-debs

sudo apt install ./linuxcnc-uspace_...
sudo apt install ./linuxcnc-uspace-dev_...
sudo apt isntall ./linuxcnc-doc-en_...

Follow the steps on the wiki page to install python-PyQT5
http://192.168.1.104/gitlab/rmd/rmdcnc/rmdcnc-core/-/wikis/Ubuntu%2018.04%20Computer%20Setup

/*************************************************
INSTALL linuxcnc-ethercat
************************************************/

0)
It's recommended to use the  LinuxCNC-ethercat repo on the RMDCNC gitlab, as
it has all the necessary with the necessary modifications already done.
Most of the instructions below are if you are installing LinuxCNC-ethercat from
scratch using the public github repo.

If you are reading this, you have probably already cloned the repo, but if not,
here's the link to the RMD repo.
http://rmd-dev/gitlab/rmd/rmdcnc/ethercat-master

If you are using the RMD repo, you can skip ahead to
step 4. If you are using the installscript, you can skip to step 5.

You will likely need this package before installing the linuxcnc-ethercat files.
sudo apt install libexpat1-dev (the script installs this package automatically)

1) Clone the "official" linuxCNC-ethercat repo by

git clone https://github.com/sittner/linuxcnc-ethercat.git

2)
You'll need the copy of realtime.mk from version 0.9.1 . You can download a zip or tar of
v0.9.1 from here:
https://github.com/sittner/linuxcnc-ethercat/releases/tag/v0.9.1
download the zip, extract it,
and copy the realtime.mk file to the linuxcnc-ethercat/src directory.

3)
You'll also need to add this line to the top of lcec_main.c:
#include "rtapi_mutex.h"

4)
Once these changes are made, run the Makefile in the top level folder in the
linuxCNC-ethercat directory by running

If you're installing it from my repo, make sure to checkout the sf-master branch
first, as that is the branch with my fixes in it.
sudo make
sudo make install

5)
copy the file lcec_conf into your main linuxcnc-dev/bin folder. This step may or
may not actually make much of a difference, as of course if you installed the
debs, this folder won't exist.

Also copy the lcec_conf file to the linuxcnc config folder of your choice inside
the RMDCNC repo (in my case, I have it placed in the sim-rmd-rtr config).

Also copy the ethercat-conf.xml file to the sim-rmd-rtr folder as well. You will need
to modify the xml file based on what ethercat devices you have connected to the computer.

You will also need to make modifications to the sim-rmd-rtr.hal file to connect the
ethercat devices to LinuxCNC.
