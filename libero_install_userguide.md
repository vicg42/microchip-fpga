1. open https://www.microchip.com/ and create accaunt.

1. open https://www.microchipdirect.com/fpga-software-products
1. Get MAC address of your HOST:
    * CentOS:

        ``` sh
        ip a
        ```

    * Ubuntu:
        * `sudo apt install net-tools`

        ``` sh
        ifconfig -a | grep ether
        ```

1. request License files. (You must to set your MAC address.)
    * "Libero Silver 1Yr Floating License for Windows/Linux Server" (LIB-SLV-F-1YR)
    * "SmartHLS 1 Year Floating License for Windows or Linux Server" (SmartHLS-F-1YR)

1. wait until License files get to email.
1. copy License files to ~/Downloads

    ```sh
    cp <License file (LIB-SLV-F-1YR)> ~/Downloads && mv ~/Downloads/License.dat ~/Downloads/LIB-SLV-F-1YR.dat
    cp <License file (SmartHLS-F-1YR)> ~/Downloads && mv ~/Downloads/License.dat ~/Downloads/SmartHLS-F-1YR.dat
    ```

1. [download later version of Libero](https://www.microchip.com/en-us/products/fpgas-and-plds/fpga-and-soc-design-tools/fpga/libero-software-later-versions) to ~/Downloads

1. Create directory.

    ```sh
    sudo mkdir /home/program
    sudo chmod 777 /home/program
    ```

1. unzip.

    ``` sh
    unzip <path to Libero_SoC_v2023.2_lin.zip> -d ~/Downloads
    ```

1. run install

    ```sh
    ~/Downloads/Libero_SoC_v2023.2_lin/launch_installer.sh
    ```

    set paths in install GUI
    * path to Libero_Soc `/home/program/microchip/Libero_SoC_v2023.2`
    * path to common files `/home/program/microchip/common`

1. wait end up installation and run

    ```sh
    sudo /home/program/microchip/Libero_SoC_v2023.2/Logs/req_to_install.sh
    ```

1. For Ubuntu

    ``` sh
    sudo apt install lsb
    ```

1. [download libero_finish_install.sh](https://github.com/vicg42/microchip-fpga/tree/main/libero_finish_install.sh) to ~/Downloads

1. run

    ``` sh
    ~/Downloads/libero_finish_install.sh
    ```

1. Output of script
    * CentOS

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

    * Ubuntu

    ``` txt
    lmutil - Copyright (c) 1989-2018 Flexera. All Rights Reserved.
    Flexible License Manager status on Mon 1/29/2024 18:01

    License server status: 27000@xubuntu-22
        License file(s) on xubuntu-22: /home/program/microchip/common/lics/License.dat:

    xubuntu-22: license server UP (MASTER) v11.16.1

    Vendor daemon status (on xubuntu-22):

    actlmgrd: UP v11.16.1
        mgcld: UP v11.16.4
    ```

1. Open terminal and apply environment current session

    ```sh
    source /home/program/microchip/Libero_SoC_v2023.2/settings64.sh
    ```

1. Run Libero in the same terminal.

    ```sh
    libero &
    ```

1. Actions into Libero_SoC IDE
    * Help -> Select Default License.
        * Select License and press button `Set Default License`.
    * View -> Windows -> Catalog -> `Download them now!`
        * Wait end up load

1. Run SmartHLS in the same terminal:

    ```sh
    shls_ide &
    ```

1. `SmartHLS -> Tool Path Settings`:
    * `/home/program/microchip/Libero_SoC_v2023.2/SmartHLS-2023.2/SmartHLS/bin/shls`
    * `/home/program/microchip/Libero_SoC_v2023.2/ModelSimPro/modeltech/linuxacoem/vsim`
    * `/home/program/microchip/Libero_SoC_v2023.2/Libero/bin/libero`
