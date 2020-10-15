*************************************************************

# Installing the LinuxCNC Ethercat HAL driver

##### Written By: Sean Froome

*************************************************************

This guide assumes you already have Ethercat installed. If you do not,
install it as it is a prerequisite to the linuxCNC-ethercat HAL drivers. 
You can download the packge off the RMD git repo:
[RMD Ethercat-Master Repo](https://rmd-dev.rmdeng.local/rmd/rmdcnc/ethercat-master)  

This guide was based on a google docs tutorial found here:
[LinuxCNC Bosch Tutorial](https://docs.google.com/document/d/1GiB065ZIAaoMHPtVfTg9JV1Kn-19xGQl2X9DM9-THNM/edit#)

***************************************************
## Installing Linux-CNC
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
## Installing linuxcnc-ethercat
************************************************

It's recommended to use the  LinuxCNC-ethercat repo on the RMDCNC gitlab, as it has all the necessary modifications already done. 
Most of the instructions below are if you are installing LinuxCNC-ethercat from scratch using the public github repo. 
If you are reading this, you have probably already cloned the repo, but if not, here's the link to the RMD repo:   
[RMD Ethercat-Master Repo](https://rmd-dev.rmdeng.local/rmd/rmdcnc/ethercat-master/)  
Follow the readme in the ethercat-master repo to install the ethercat-master package.  


1. You will likely need to install this package before installing the linuxcnc-ethercat files.  
`sudo apt install libexpat1-dev`

************************************************
### Installing linuxcnc-ethercat with bash script
************************************************
To run the bash script you need to decide which config of RMDCNC you wish to use ethercat with. You will need to pass
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
Google Docs tutorial linked above.
************************************************
### Installing linuxcnc-ethercat from github sources
************************************************

1. Clone the "official" linuxCNC-ethercat repo with git  
`git clone https://github.com/sittner/linuxcnc-ethercat.git`

2. Download a copy of linuxcnc-ethercat v0.9.1 (previous version).  
[LinuxCNC EtherCAT v0.9.1 release](https://github.com/sittner/linuxcnc-ethercat/releases/tag/v0.9.1)  
Extract the zip, and copy  `realtime.mk` to the linuxcnc-ethercat/src directory.

3. Add this line to the top of lcec_main.c:  
```#include "rtapi_mutex.h"```

4. Once these changes are made, run the Makefile in the top level folder of the
linuxCNC-ethercat directory by running the following commands:  
    ```
    sudo make
    sudo make install
    ``` 
5. Copy files and modify the target LinuxCNC configuration folder:
   1. Copy `lcec_conf`to your target linuxcnc config folder of your choice.
   2. Copy the ethercat-conf.xml file (found in the examples folder) to the linuxcnc folder of your choice. 
   3. Modify the xml file based on the EtherCAT devices you wish to use.
   4. Modify the HAL file(s) to connect EtherCAT devices to LinuxCNC. 