1. open https://www.microchip.com/ and create accaunt.

2. open https://www.microchipdirect.com/fpga-software-products and request License files
You must to set your MAC address.
Linux (CentOS): command for show MAC address:

```
    ip a
```

    * "Libero Silver 1Yr Floating License for Windows/Linux Server" (LIB-SLV-F-1YR)
    * "SmartHLS 1 Year Floating License for Windows or Linux Server" (SmartHLS-F-1YR)
    * wait until License file Дождаться пока на почту придет файл лицензий. Он должен появиться и на странице, где мы ее заказывали.
    * copy License file (LIB-SLV-F-1YR) to ~/Downloads of CentOS. Rename License file -> LIB-SLV-F-1YR.dat
    * copy License file (SmartHLS-F-1YR) to ~/Downloads of CentOS. Rename License file -> SmartHLS-F-1YR.dat

3. open https://www.microchip.com/en-us/products/fpgas-and-plds/fpga-and-soc-design-tools/fpga/libero-software-later-versions
    *  download https://ww1.microchip.com/downloads/secure/aemdocuments/documents/fpga/media-content/fpga/v2023-1/libero_soc_v2023.1_web_lin.zip to ~/Downloads

4. unzip.

``` sh
  unzip ~/Downloads/libero_soc_v2023.1_web_lin.zip -d ~/Downloads
```

5. Create directory.

```sh
sudo mkdir /home/program
sudo chmod 777 /home/program
```

6. run launch_installer.sh

```sh
./launch_installer.sh
```

7. Set paths:
  * path to Libero_Soc `/home/program/microchip/Libero_SoC_v2023.1`
  * path to common files `/home/program/microchip/common`

8. wait end up installation and run

```sh
sudo /home/program/microchip/Libero_SoC_v2023.1/Logs/req_to_install.sh
```

8. create libero_patch.sh

```sh
touch ~/Downloads/libero_patch.sh
sudo chmod +x ~/Downloads/libero_patch.sh
```

9. copy to libero_patch.sh


```
#!/bin/bash

LIB_SLV_F_1YR=./LIB-SLV-F-1YR.dat
SmartHLS_F_1YR=./SmartHLS-F-1YR.dat

LIBERO_PATH=/home/program/microchip/Libero_SoC_v2023.1 #./program/microchip/Libero_SoC_v2023.1 #
LIBERO_COMMON_PATH=/home/program/microchip/common


if [[ ! -d $LIBERO_COMMON_PATH/demons ]]; then
    mkdir -p $LIBERO_COMMON_PATH/demons || exit 1
fi

if [[ -f $LIBERO_PATH/Libero/bin64/actlmgrd ]]; then
    if [[ ! -f  $LIBERO_COMMON_PATH/demons/actlmgrd ]]; then
        cp -v $LIBERO_PATH/Libero/bin64/actlmgrd $LIBERO_COMMON_PATH/demons
        cp -v $LIBERO_PATH/Libero/bin64/lmgrd $LIBERO_COMMON_PATH/demons
        cp -v $LIBERO_PATH/Libero/bin64/lmutil $LIBERO_COMMON_PATH/demons
        cp -v $LIBERO_PATH/Libero/bin64/mgcld $LIBERO_COMMON_PATH/demons
        cp -v $LIBERO_PATH/Libero/bin64/snpslmd $LIBERO_COMMON_PATH/demons
    fi
else
    echo "can't find $LIBERO_PATH/Libero/bin64/actlmgrd"
    exit 1
fi

if [[ -f $LIB_SLV_F_1YR ]]; then
    if [[ ! -d $LIBERO_COMMON_PATH/lics ]]; then
        mkdir -p $LIBERO_COMMON_PATH/lics || exit 1
        cp -v $LIB_SLV_F_1YR $LIBERO_COMMON_PATH/lics/License.dat || exit 1

        HOST_ID=$(hostname) || exit 1

        sed -i "s/<put.hostname.here>/$HOST_ID/g" $LIBERO_COMMON_PATH/lics/License.dat || exit 1
        STRING_EDITED="$LIBERO_COMMON_PATH/demons/actlmgrd port=1702"
        STRING_EDITED_SED=$(echo $STRING_EDITED | sed 's#/#\\/#g') #get absolute path and replace / to \/
        sed -i "s/PATH\/actlmgrd/$STRING_EDITED_SED/g" $LIBERO_COMMON_PATH/lics/License.dat || exit 1

        #remove first the first occurrence in a file
        sed -i '0,/1702/s/1702//' $LIBERO_COMMON_PATH/lics/License.dat || exit 1

        STRING_EDITED="$LIBERO_COMMON_PATH/demons/mgcld port=1703"
        STRING_EDITED_SED=$(echo $STRING_EDITED | sed 's#/#\\/#g') #get absolute path and replace / to \/
        sed -i "s/PATH\/mgcld/$STRING_EDITED_SED/g" $LIBERO_COMMON_PATH/lics/License.dat || exit 1

        STRING_EDITED="$LIBERO_COMMON_PATH/demons/snpslmd port=1704"
        STRING_EDITED_SED=$(echo $STRING_EDITED | sed 's#/#\\/#g') #get absolute path and replace / to \/
        sed -i "s/PATH\/snpslmd/$STRING_EDITED_SED/g" $LIBERO_COMMON_PATH/lics/License.dat || exit 1

        STRING_EDITED=$(find $SmartHLS_F_1YR -type f -print | xargs grep "INCREMENT SmartHLS actlmgrd")
        echo "$STRING_EDITED" >> $LIBERO_COMMON_PATH/lics/License.dat

        STRING_EDITED=$(find $SmartHLS_F_1YR -type f -print | xargs grep "INCREMENT SmartHLS_SOC actlmgrd")
        echo "$STRING_EDITED" >> $LIBERO_COMMON_PATH/lics/License.dat
    fi
else
    echo "can't find $LIB_SLV_F_1YR"
    exit 1
fi

if [[ ! -f $LIBERO_PATH/settings64.sh ]]; then
    touch $LIBERO_PATH/settings64.sh
    echo "# For Floating License from a License Servers" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LIBERO=$LIBERO_PATH" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LIBERO_ROOTDIR=\$LIBERO/Libero/bin" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LIBERO_LIBDIR=\$LIBERO/Libero/lib64" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LIBERO_SHLS=\$LIBERO/SmartHLS-2023.1/SmartHLS/bin/" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LIBERO_MODELSIM=\$LIBERO/ModelSimPro/modeltech/bin/" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export PATH=\$LIBERO_MODELSIM:\$LIBERO_SHLS:\$LIBERO_ROOTDIR:\$PATH" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LD_LIBRARY_PATH=\$LIBERO_LIBDIR:\$LD_LIBRARY_PATH" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "# For real display 0 for remote display 1" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export DISPLAY=:1" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "# <1702> is the port number of libero" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "# <1703> is the port number of modelsim" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "# <1704> is the port number of synopsys" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "# localhost is server address" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LM_LICENSE_FILE=1702@localhost:\$LM_LICENSE_FILE" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LM_LICENSE_FILE=1703@localhost:\$LM_LICENSE_FILE" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export SNPSLMD_LICENSE_FILE=1704@localhost:\$SNPSLMD_LICENSE_FILE" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export MTI_VCO_MODE=32" >> $LIBERO_PATH/settings64.sh || exit 1
fi

$LIBERO_COMMON_PATH/demons/lmgrd -c $LIBERO_COMMON_PATH/lics/License.dat -l $LIBERO_COMMON_PATH/logs/lic_log.txt  || exit 1

$LIBERO_COMMON_PATH/demons/lmutil lmstat -c $LIBERO_COMMON_PATH/lics/License.dat || exit 1
```

9. run libero_patch.sh

```sh
cd ~/Downloads
./libero_patch.sh
```

10. Убедиться, что демоны поднялись и лицензии активны. Вывод предыдущей команды должен содержать:
```
lmutil - Copyright (c) 1989-2018 Flexera. All Rights Reserved.
Flexible License Manager status on Mon 7/17/2023 05:11

License server status: 27000@CentOS3
License file(s) on CentOS3: /home/program/microchip/common/lics/License.dat:

CentOS3: license server UP (MASTER) v11.16.1

Vendor daemon status (on CentOS3):

actlmgrd: UP v11.16.1
mgcld: UP v11.16.4
snpslmd: UP v11.16.4
```

11. Open terminal and apply enviroment ot current session

```sh
source /home/program/microchip/Libero_SoC_v2023.1/settings64.sh
```

12. Run Libero in the same terminal.
```sh
libero &
```

13. Actions into Libero_SoC IDE
  * Help>Select Default License.
  * Select License and press button `Set Default License`.
  * Close window

14. Actions into Libero_SoC IDE
  * View>Windows>Catalog
  * Press button `Download them now!`.
  * Wait end up load

15. Run SmartHLS in the same terminal:
```sh
shls_ide &
```

16. Open SmartHLS and `SmartHLS->Tool Path Settings`:
  * `/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/bin/shls`
  * `/home/program/microchip/Libero_SoC_v2023.1/ModelSimPro/modeltech/linuxacoem/vsim`
  * `/home/program/microchip/Libero_SoC_v2023.1/Libero/bin/libero`