*************************************************************

Installing the LinuxCNC Ethercat HAL driver

Written By: Sean Froome

*************************************************************

This guide assumes you already have Ethercat installed. If you do not,
install it as it is a prerequisite to the linuxCNC-ethercat HAL drivers.

This guide was based on a google docs tutorial found here:
https://docs.google.com/document/d/1GiB065ZIAaoMHPtVfTg9JV1Kn-19xGQl2X9DM9-THNM/edit#

***************************************************
Installing Linux-CNC
***************************************************

Install the LinuxCNC debs from the RMD gitlab repo.

https://192.168.1.104/rmd/rmdcnc/linuxcnc-debs  
`sudo apt install ./linuxcnc-uspace_...`  
`sudo apt install ./linuxcnc-uspace-dev_...`  
`sudo apt isntall ./linuxcnc-doc-en_...`  
Follow the steps on the wiki page to install python-PyQT5  
https//192.168.1.104/rmd/rmdcnc/rmdcnc-core/-/wikis/Ubuntu%2018.04%20Computer%20Setup

************************************************
Install linuxcnc-ethercat
************************************************

0. It's recommended to use the  LinuxCNC-ethercat repo on the RMDCNC gitlab, as
it has all the necessary with the necessary modifications already done.
Most of the instructions below are if you are installing LinuxCNC-ethercat from
scratch using the public github repo.  
If you are reading this, you have probably already cloned the repo, but if not,
here's the link to the RMD repo.  
https://rmd-dev.rmdeng.local/rmd/rmdcnc/ethercat-master  
There is a separate readme for installing the ethercat-master package.  
If you are using the RMD repo, you can skip ahead to
step 4.   
If you are using the installscript, run the script and skip to step 5.  
You will likely need to install this package before installing the linuxcnc-ethercat files.  
`sudo apt install libexpat1-dev`

1. Clone the "official" linuxCNC-ethercat repo with git  
`git clone https://github.com/sittner/linuxcnc-ethercat.git`

2. You'll need a copy of realtime.mk from version 0.9.1 . You can download a zip or tar of
v0.9.1 from here:
https://github.com/sittner/linuxcnc-ethercat/releases/tag/v0.9.1
download the zip, extract it,
and copy the realtime.mk file to the linuxcnc-ethercat/src directory.

3. You'll also need to add this line to the top of lcec_main.c: '#include "rtapi_mutex.h"'

4. Once these changes are made, run the Makefile in the top level folder in the
linuxCNC-ethercat directory by running the following commands.  
`sudo make`  
`sudo make install`  

5. Copy the lcec_conf file to the linuxcnc config folder of your choice inside
the RMDCNC repo (in my case, I have it placed in the sim-rmd-rtr config folder).
Also copy the ethercat-conf.xml file to the sim-rmd-rtr folder. You will need
to modify the xml file based on what ethercat devices you have connected to the computer.
You will also need to make modifications to the sim-rmd-rtr.hal file to connect the
ethercat devices to LinuxCNC.
