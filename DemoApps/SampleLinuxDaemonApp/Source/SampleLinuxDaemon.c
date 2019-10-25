/******************************************************************************
 *
 *  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
 *	Licensed under the MIT. See LICENSE file in the project root for full license information.
 *  SPDX-License-Identifier: MIT
 * 
 *  SampleLinuxDaemon.c
 *
 ******************************************************************************/
 
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <stdlib.h>
#include <unistd.h>
#include "cppformat/format.h"

const std::string appIdentifier = "60023450000002";

std::string GetCurrentTimeStamp()
{
    std::string result = "";

    auto now = std::chrono::system_clock::now();
    time_t cnow = std::chrono::system_clock::to_time_t(now);
    struct tm* tmDateTime = std::localtime(&cnow);

    const char * timeFormatStr = "%02d%02d%02d-%02d%02d%02d";

    result = fmt::sprintf(timeFormatStr,
        (tmDateTime->tm_year + 1900),
        (tmDateTime->tm_mon + 1),
        tmDateTime->tm_mday,
        tmDateTime->tm_hour,
        tmDateTime->tm_min,
        tmDateTime->tm_sec);

    return result;
}

int main(void)
{   
    std::cout << "Starting Sample Linux Daemon" << std::endl;

    char* plcnextAppsDataDir = getenv("APPDATADIRECTORY");
    std::string appPersistentDataDir; 

    // Get Apps persistent Data directory
    if(plcnextAppsDataDir == NULL)
    {	// Variant 1 to get persistent data storage path (via app identifier)
	std::cout << "Couldn't get persistent data dir env variable, using default path" << std::endl;
	appPersistentDataDir = "/opt/plcnext/appshome/data/" + appIdentifier;
    }
    else
    {
	// Variant 2 to get to get persistent data storage path (via environment variable exported/passed in the init script)
        appPersistentDataDir = std::string(plcnextAppsDataDir);
    }
    std::cout << " Daemon persistent Data dir = " << appPersistentDataDir << std::endl;

    std::string   logFile = appPersistentDataDir + "/linuxDaemonOut.log";
    std::ofstream outfile(logFile, std::ofstream::out | std::ofstream::app);

    std::cout << " Daemon log data file = " << logFile << std::endl;

    unsigned int counterValue = 0;

    while(1)
    {
	outfile << GetCurrentTimeStamp() << "  - counter = " << counterValue++ << std::endl;
	std::cout << "Current Time Stamp = " << GetCurrentTimeStamp() << std::endl;
	sleep(1);
    }
    
    outfile.close();
    return 0;
}


