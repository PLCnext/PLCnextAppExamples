/******************************************************************************
 *
 *  Copyright PHOENIX CONTACT Electronics GmbH
 *
 *****************************************************************************/

/*************************************************************************/
/*  INCLUDES                                                             */
/*************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <libgen.h>
#include <linux/limits.h>
#include <unistd.h>
#include <syslog.h>
#include "Arp/System/ModuleLib/Module.h"
#include "Arp/System/Commons/Environment.hpp"

#include "CSampleRuntime.h"

using namespace std;
using namespace Arp::System::Commons;

CSampleRuntime* g_pRT;

const string appIdentifier = "cmd2EngPdataRuntime";
const string acfSettingsLocalPath ="SampleRuntime/Default.acf.settings";

int main(int argc, char** argv) {

	// we use syslog for logging until the PLCnext logger isn't ready
	openlog ("PLCnextSampleRuntime", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

	syslog (LOG_INFO, "PLCnextSampleRuntime started");

	string acfSettingsRelPath("");

	if(argc != 2)
	{
		syslog (LOG_ERR, "Invalid command line arguments. Only relative path to the acf.settings file must be passed");
		return -1;
	}
	else
	{
		acfSettingsRelPath = argv[1];
	}

	char szExePath[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", szExePath, PATH_MAX);
	string strDirPath;
	if (count != -1) {
		strDirPath = dirname(szExePath);
	}
	string strSettingsFile(strDirPath);
    strSettingsFile += "/" + acfSettingsRelPath;
	syslog(LOG_INFO, string("Acf settings file path: " + strSettingsFile).c_str());

	// First intialize PLCnext module application
	// Arguments:
	//  arpBinaryDir:    Path to Arp binaries
	//  applicationName: Arbitrary Name of Application
	//  acfSettingsPath: Path to *.acf.settings document to set application up
    if (ArpSystemModule_Load("/usr/lib", "PLCnextSampleRuntime", strSettingsFile.c_str()) != 0)
    {
    	syslog (LOG_ERR, "Could not load Arp System Module Application");
        return -1;
    }
	syslog (LOG_INFO, "Loaded Arp System Module Application");
	closelog();

	g_pRT = new CSampleRuntime();

	// loop forever
	for (;;)
	{
		WAIT1s;
	}

	return 0;
}

