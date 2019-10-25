#!/bin/sh

# Get script arguments
APPIDENTIFIER="$1" 
APPDIRECTORY="$2"
APPDATADIRECTORY="$3"
APPTEMPDIRECTORY="$4"


echo "App Identifier = $APPIDENTIFIER"
echo "Persistent App data dir = $APPDATADIRECTORY"
echo "Temporary App data dir  = $APPTEMPDIRECTORY"
echo "App Directory = $APPDIRECTORY"

# Get current time stamp
DATETIME=`date "+%Y%m%d-%H%M%S"`

# Check if linux daemon output file exists

LINUXDAEMON_OUTPUT="$APPDATADIRECTORY/linuxDaemonOut.log"
echo "Linux Daemon output file path = $LINUXDAEMON_OUTPUT"
if [ -e $LINUXDAEMON_OUTPUT ]
then
   LOGFILECOPYPATH="$APPDATADIRECTORY/$DATETIME.copy.log"
   echo "Log file copy path = $LOGFILECOPYPATH"
   cp $LINUXDAEMON_OUTPUT $LOGFILECOPYPATH
else
   echo "Output log file not found!"
fi
