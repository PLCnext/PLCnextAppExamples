# PLCnext Technology Apps

[![Feature Requests](https://img.shields.io/github/issues/PLCnext/PLCnextAppExamples/feature-request.svg)](https://github.com/PLCnext/PLCnextAppExamples/issues?q=is%3Aopen+is%3Aissue+label%3Afeature-request+sort%3Areactions-%2B1-desc)
[![Bugs](https://img.shields.io/github/issues/PLCnext/PLCnextAppExamples/bug.svg)](https://github.com/PLCnext/PLCnextAppExamples/issues?utf8=✓&q=is%3Aissue+is%3Aopen+label%3Abug)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Web](https://img.shields.io/badge/PLCnext-Website-blue.svg)](https://www.phoenixcontact.com/plcnext)
[![Community](https://img.shields.io/badge/PLCnext-Community-blue.svg)](https://www.plcnext-community.net)

This repository contains documentation for creating PLCnext app containers as well as demo PLCnext Technology Apps for different app types including their source files.

## PLCnext App-Parts

For full documentation on how to create PLCnext Technology Apps and package them into the corresponding app container, refer to the guide [Building a PLCnext Control Function Extension](https://store.plcnext.help/st/Creating_a_Function_Extension/Building_a_PLCnext_Control_Function_Extension.htm) available in the [PLCnext Store - Info Center](https://store.plcnext.help/st/Home.htm).

A PLCnext App must contain a Metadata-App-part and at least one optional App-part.
| 9 | Update Configurations | Used to enable auto update mode, keep apps persistent/temporary data on update or to run an update shell script after installing the new app version | Optional |

| #   | App-Part                                      | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             | Type      | Firmware support                                                                                                                       |
| --- | --------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| 1   | Metadata                                      | App meta information such as identifier and version                                                                                                                                                                                                                                                                                                                                                                                                                                                                     | Mandatory | From version 19.0.0                                                                                                                    |
| 2   | PLCnext Engineer App                          | Contains a complete PLCnext Engineer project configuration (solution app)                                                                                                                                                                                                                                                                                                                                                                                                                                               | Optional  | From version 19.0.0                                                                                                                    |
| 3   | Command line tools                            | A command line tool can be integrated into a PLCnext system in the form of an app. The command line tool can then be started from a shell without specifying the full path.                                                                                                                                                                                                                                                                                                                                             | Optional  | From version 19.3.0                                                                                                                    |
| 4   | Shared libraries                              | Shared libraries can be integrated into the app container and made known to the Linux system when the app is installed/activated                                                                                                                                                                                                                                                                                                                                                                                        | Optional  | From version 19.0.0 <br> ❗ **Obsoleted:** Support is discarded and removed from firmware versions >= 2025.0.x |
| 5   | Linux Daemons                                 | A (Linux) daemon (exe) can be integrated into a PLCnext system in the form of an app                                                                                                                                                                                                                                                                                                                                                                                                                                    | Optional  | From version 19.3.0 <br>❗ **Obsoleted:** Support is discarded and removed from firmware versions >= 2025.0.x |
| 6   | PLCnext Extensions                            | Extensions of the PLCnext runtime can be integrated into a PLCnext system in the form of an app. With a PLCnext extension, the PLCnext runtime can be extended by the following elements: <ul><li> A process dependent on the PLCnext runtime (PLCnext process) </li><li> A PLCnext shared library (PLCnext library). Usually it belongs to a PLCnext component </li><li> A PLCnext component (PLCnext component) </li><ul>                                                                                             | Optional  | From version 19.3.0                                                                                                                    |
| 7   | Configuration of the PLCnext Runtime services | PLCnext system services can be enabled/disabled with this app part                                                                                                                                                                                                                                                                                                                                                                                                                                                      | Optional  | From version 19.3.0                                                                                                                    |
| 8   | File- / Data-Storage                          | When necessary, it is used to specify whether a persistent and/or temporary location is required for the App                                                                                                                                                                                                                                                                                                                                                                                                            | Optional  | From version 19.3.0 <br> Support for "directoriesToCreate" from firmware version 2025.0.x                                              |
| 9   | OCI container                                 | This app part provides the possibility for simplified integration and run of OCI (Open Container [Initiative](https://opencontainers.org/)) container images of apps on the PLCnext Technology device. For this topic the container engine Podman is used in conjunction with [systemd](https://systemd.io/) to allow efficient and reliable management of containerized applications, leveraging Podman's rootless and deamonless architecture while maintaining full control over service management through systemd. | Optional  | From version 2025.0.x                                                                                                                  |

The following shows the contents of an app description file in which all types of app parts are configured by way of example:

```json
{
    "plcnextapp": {
        "name": "Full Multipart App",
        "identifier": "00000000000000",
        "version": "Full 20.0 (112.12 DemoVersion)",
        "target": "AXC F 2152",
        "minfirmware_version": "20.0.0",
        "manufacturer":"Phoenix Contact",
        "licensetype":"Full",
        "linkToAppPage":"https://www.plcnextstore.com/testapp",
        "additionalInfo":"[{}]"
    },
    "engineerapp": {
        "folder": "/arp/PCWE"
    },
    "cmdtools":
    [
       {
         "path" : "/bin/DemoCmdTool"
       },
       {
         "path" : "<Path to cmd tool executable binary>"
       }
    ],
    "plcnextextensions" :
    [
        {
            "acfconfigpath"  : "/PLCnextRuntimeDaemon.acf.config"
        },
        {
            "acfconfigpath"  : "<path to PLCnext extension .acf.config file>"
        }
    ],
    "datastorage": {
        "persistentdata": true,
        "temporarydata" : true,
        "directoriesToCreate": {
            "temporary": [
                {
                    "path": "<folder name/path>"
                },
                {
                    "path": "/folder2"
                }
             ],
            "persistent": [
                {
                    "path": "<folder name/path>"
                },
                {
                    "path": "/folder3"
                }
             ],
        }
    },
    "ocicontainer":
    {
        "quadletFiles" :
        [
          {
                "type": "Main",
                "path": "/path/to/unitFile.pod"
          },
          {
                "type": "Dependency",
                "path": "/path/to/unitFile.network"
          },
          { "path": "<path to quadlet file>", "type": "<Main/Dependency>" }
        ],
        "environmentVariables":
        [
        {
            "name": "varName1",
            "value": "1"
          },
          {
            "name": "varName2",
            "value": "2"
          }
        ],
        "images":
        [
          {
            "name"  : "<name>",
            "id": "<idHash>",
            "path"   : "<path to image file>"
          }
        ]
    },
    "plcnextservices":
    [
       {
           "service": "<Service ID>",
           "action" : "EXCLUSIVE_ACCESS"
       },
       {
           "service": "WBM",
           "action" : "MUST_HAVE"
       },
       {
           "service" : "OPCUA",
           "action"  : "MUST_NOT_HAVE"
       }
    ],
    "updateconfigs": {
        "autoupdate_enabled": true,
        "keep_persistentdata": true,
        "keep_temporarydata" : false,
        "post_updatescript": "<Path to app update script>"
    }
}

```

**Note:** Up to firmware version 2025.0, the app parts Linux Daemons and Shared Libraries were supported. If these app parts are included, the following entries also belong in the app_info.json:

```json
{
  "linuxdaemons": [
    {
      "path": "/bin/daemon1exe",
      "cmdargs": "arg1  arg2 ... argN",
      "starttime": "40"
    },
    {
      "path": "<Path to daemon executable binary>",
      "cmdargs": "<arg1  arg2 ... argN>",
      "starttime": "99",
      "initScriptTemplate": "<Path to own template file>"
    }
  ],
  "sharedlibs": [
    {
      "libpath": "/lib/sharedlib1.so"
    },
    {
      "libpath": "<Path to shared library binary>"
    }
  ]
}
```

# Table of Content

This table describes the demo app examples in the git project folder DemoApps

| #   | Demo App                           | Description                                                                                                                                                                                                                                                   | Sources                                                                                                                                                                       |
| --- | ---------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1   | PLCnext Engineer App               | The demo app with an engineer part (solution app) contains a simple solution for flashing an LED (controlling a digital output) in an AXL F DO16 I/O module. The I/O module is controlled by the controller (AXC F 2152) via Axioline F                       | [DemoCmdToolApp](/DemoApps/DemoCmdToolApp/)                                                                                                                                   |
| 2   | Command Line Tool App              | To demonstrate an app with a CmdTool App-Part a simple tool was developed, which is installed in an app and displays a text message on the console when called from the command line                                                                          | [DemoEngineerApp](/DemoApps/DemoEngineerApp/)                                                                                                                                 |
| 3   | Linux shared library App           | n/a yet                                                                                                                                                                                                                                                       | n/a                                                                                                                                                                           |
| 4   | Linux daemon App                   | In the SampleLinuxDaemon app the simple program "SampleLinuxDaemon" is started as a Linux daemon, which permanently reads the current time stamp in an endless loop every second and writes it into a log file linuxDaemonOut.log.                            | [SampleLinuxDaemonApp](/DemoApps/SampleLinuxDaemonApp/)                                                                                                                       |
| 5   | PLCnext Extensions App             | Contains two examples for PLCnext Extensions Apps: <ul><li>Demo PLCnext Runtime App (PLCnext-Process) based on the example in the PLCnext Github Repo [SampleRuntime](https://github.com/PLCnext/SampleRuntime) </li><li>Demo PLCnext-Component App</li></ul> | [PlcnextSampleRuntimeApp](/DemoApps/DemoPlcnextExtensionsApps/PlcnextSampleRuntimeApp/) [WbmPlcnextComponentApp](/DemoApps/DemoPlcnextExtensionsApps/WbmPlcnextComponentApp/) |
| 6   | PLCnext services configuration App | In the demo app for configuring PLCnext system services, the WBM-PLCnext component is switched off. For this the action "MUST_NOT_HAVE" is configured for the Plcnext service with the ID "WBM", therefore the name "SC_WBM-MNH" is selected for the app.     | [DemoPlcnextServicesConfigApp](/DemoApps/DemoPlcnextServicesConfigApp/)                                                                                                       |
| 7   | Data Storage                       | The procedure for using and configuring a Data Storage App Part is explained in the demo apps "Demo PLCnext Runtime App" and "Demo Linux Daemon App"                                                                                                          | [PlcnextSampleRuntimeApp](/DemoApps/DemoPlcnextExtensionsApps/PlcnextSampleRuntimeApp/) [SampleLinuxDaemonApp](/DemoApps/SampleLinuxDaemonApp/)                               |
| 8   | Update configs                     | The update configs demo App contains an App container to update demo App [SampleLinuxDaemonApp](/DemoApps/SampleLinuxDaemonApp/) from app version 123.11.6.0 to 123.11.6.9                                                                                    | [SampleLinuxDaemonUpdateApp](/DemoApps/SampleLinuxDaemonUpdateApp/)                                                                                                           |
| 9   | OCI Container                      | This will be a simple example showcasing selected features of Container Apps.                                                                                 | Soon to be published as an individual repository/project                                                                                       |
