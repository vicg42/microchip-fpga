#Build
* cmake build

    ``` sh
    ./build-cmake.sh
    ```

* build with SmartHLS

    ``` sh
    ./build-shls.sh
    ```

# Debug settings for vscode (microchip-fpga/.vscode/launch.json)

``` json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "SystemC:Build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceRoot}/hls/prj-video-path//build/main",
            "args": [
                "-i ../image/toronto_1080p.bmp",
                "-o ../output-hls-01.bmp",
                "-c ../config-modules.toml",
            ],
            //"stopAtEntry": true,
            "cwd": "${workspaceRoot}/hls/prj-video-path/build/",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            // "preLaunchTask": "C/C++: gcc build active file",
            "miDebuggerPath": "/usr/bin/gdb"
        }
    ]
}
```
