1. open https://www.microchip.com/ and create accaunt.

1. open https://www.microchipdirect.com/fpga-software-products
1. request License files. (You must to set your MAC address.)
    * "Libero Silver 1Yr Floating License for Windows/Linux Server" (LIB-SLV-F-1YR)
    * "SmartHLS 1 Year Floating License for Windows or Linux Server" (SmartHLS-F-1YR)
    * Linux (CentOS): command for show MAC address:

    ``` sh
    ip a
    ```

1. wait until License files get to email.
1. copy License files to ~/Downloads of CentOS
    * copy License file (LIB-SLV-F-1YR) to ~/Downloads of CentOS. Rename License file -> LIB-SLV-F-1YR.dat
    * copy License file (SmartHLS-F-1YR) to ~/Downloads of CentOS. Rename License file -> SmartHLS-F-1YR.dat

1. open https://www.microchip.com/en-us/products/fpgas-and-plds/fpga-and-soc-design-tools/fpga/libero-software-later-versions

1. download [libero_soc_v2023.1_web_lin.zip](https://ww1.microchip.com/downloads/secure/aemdocuments/documents/fpga/media-content/fpga/v2023-1/libero_soc_v2023.1_web_lin.zip) to ~/Downloads of CentOS

1. unzip.

    ``` sh
    unzip ~/Downloads/libero_soc_v2023.1_web_lin.zip -d ~/Downloads
    ```

1. Create directory.

    ```sh
    sudo mkdir /home/program
    sudo chmod 777 /home/program
    ```

1. run launch_installer.sh

    ```sh
    ./launch_installer.sh
    ```

1. set paths
    * path to Libero_Soc `/home/program/microchip/Libero_SoC_v2023.1`
    * path to common files `/home/program/microchip/common`

1. wait end up installation and run

    ```sh
    sudo /home/program/microchip/Libero_SoC_v2023.1/Logs/req_to_install.sh
    ```

1. download https://github.com/vicg42/microchip-fpga/tree/main/libero_patch.sh to ~/Downloads of CentOS

1. run libero_patch.sh

    ```sh
    cd ~/Downloads
    ./libero_patch.sh
    ```

1. output of running script libero_patch.sh must be like that

    ``` txt
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

1. Open terminal and apply enviroment ot current session

    ```sh
    source /home/program/microchip/Libero_SoC_v2023.1/settings64.sh
    ```

1. Run Libero in the same terminal.

    ```sh
    libero &
    ```

1. Actions into Libero_SoC IDE
    * Help>Select Default License.
    * Select License and press button `Set Default License`.
    * Close window

1. Actions into Libero_SoC IDE
    * View>Windows>Catalog
    * Press button `Download them now!`.
    * Wait end up load

1. Run SmartHLS in the same terminal:

    ```sh
    shls_ide &
    ```

1. Open SmartHLS and `SmartHLS->Tool Path Settings`:
    * `/home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/bin/shls`
    * `/home/program/microchip/Libero_SoC_v2023.1/ModelSimPro/modeltech/linuxacoem/vsim`
    * `/home/program/microchip/Libero_SoC_v2023.1/Libero/bin/libero`