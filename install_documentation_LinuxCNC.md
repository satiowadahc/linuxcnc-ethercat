*************************************************************

#Installing the LinuxCNC Ethercat HAL driver

#####Written By: Sean Froome

*************************************************************

This guide assumes you already have Ethercat installed. If you do not,
install it as it is a prerequisite to the linuxCNC-ethercat HAL drivers. 
You can download the packge off the RMD git repo:
[RMD Ethercat-Master Repo](https://rmd-dev.rmdeng.local/rmd/rmdcnc/ethercat-master)  

This guide was based on a google docs tutorial found here:
[LinuxCNC Bosch Tutorial](https://docs.google.com/document/d/1GiB065ZIAaoMHPtVfTg9JV1Kn-19xGQl2X9DM9-THNM/edit#)

***************************************************
##Installing Linux-CNC
***************************************************

Install the LinuxCNC debs from the RMD gitlab repo.

[RMDCNC LinuxCNC deb packages](https://rmd-dev.rmdeng.local/rmd/rmdcnc/linuxcnc-debs)  
```bash
sudo apt install ./linuxcnc-uspace_...   
sudo apt install ./linuxcnc-uspace-dev_...  
sudo apt install ./linuxcnc-doc-en_...
```  
Follow the steps on the wiki page to install python-PyQT5  
[RMDCNC-Wiki](https://rmd-dev.rmdeng.local/rmd/rmdcnc/rmdcnc-core/-/wikis/Ubuntu%2018.04%20Computer%20Setup)

************************************************
##Installing linuxcnc-ethercat
************************************************

It's recommended to use the  LinuxCNC-ethercat repo on the RMDCNC gitlab, as it has all the necessary modifications already done. 
Most of the instructions below are if you are installing LinuxCNC-ethercat from scratch using the public github repo. 
If you are reading this, you have probably already cloned the repo, but if not, here's the link to the RMD repo:   
[RMD Ethercat-Master Repo](https://rmd-dev.rmdeng.local/rmd/rmdcnc/ethercat-master/)  
Follow the readme in the ethercat-master repo to install the ethercat-master package.  


1. You will likely need to install this package before installing the linuxcnc-ethercat files.  
`sudo apt install libexpat1-dev`

************************************************
###Installing linuxcnc-ethercat with bash script
************************************************
To run the bash script you need to decide which config of RMDCNC you wish to use ethercat with. The You will need to pass
that folder location as an argument when you run the script.  
`~/RMDCNC-Core/linuxcnc/configs/sim-rmd-rtr` is an example path. 

If you're using the above path, then you run the shell script, it should look like the following:  
`./installscript.sh "~/RMDCNC-Core/linuxcnc/configs/sim-rmd-rtr"` 
There are two files you will need to modify
1. the ethercat-conf.xml file
2. your hal file 
    
Inside your chosen config folder should now be the ethercat-conf xml file, and an lcec_conf binary file. 
Your xml file will vary depending on what ethercat devices you wish to connect to linuxcnc, and what 
slave address they have. The examples listed in the examples folder are a good place to start, as is the 
google docs tutorial linked above.
************************************************
###Installing linuxcnc-ethercat from github sources
************************************************

1. Clone the "official" linuxCNC-ethercat repo with git  
`git clone https://github.com/sittner/linuxcnc-ethercat.git`

2. You'll need a copy of realtime.mk from version 0.9.1 . You can download a zip or tar of
v0.9.1 from here:
["Official" LinuxCNC EtherCAT repo](https://github.com/sittner/linuxcnc-ethercat/releases/tag/v0.9.1)  
download the zip, extract it, and copy the realtime.mk file to the linuxcnc-ethercat/src directory.

3. You'll also need to add this line to the top of lcec_main.c: '#include "rtapi_mutex.h"'

4. Once these changes are made, run the Makefile in the top level folder in the
linuxCNC-ethercat directory by running the following commands:  
    ```
    sudo make
    sudo make install
    ``` 
2. Copy and modify files: 
   1. Copy the lcec_conf file to the linuxcnc config folder of your choice inside
     the RMDCNC repo (in my case, I have it placed in the sim-rmd-rtr config folder). 
   2. Also copy the ethercat-conf.xml file (a copy can be found in the examples folder) to the sim-rmd-rtr folder. 
   3.  You will need to modify the xml file based on what ethercat devices you have connected to the computer.
   4. You will also need to make modifications to the sim-rmd-rtr.hal file to connect the
ethercat devices to LinuxCNC.