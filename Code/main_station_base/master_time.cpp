//Header file
#include "master_time.h"
//config
#include "config.h"


//Libraries Importing
#include "time.h"
#include "sntp.h"
#include "config.h"

static const char* ntpServer1 = "fr.pool.ntp.org";
static const char* ntpServer2 = "ntp.sophia.mines-paristech.fr";
static const long  gmtOffset_sec = 3600;
static const int   daylightOffset_sec = 3600;

static const char* time_zone = TIME_ZONE;  // TimeZone rule for Europe/Paris
static struct tm timeinfo;

//Constructor
TimeM::TimeM(void){
    second = 0;
    min = 0;
    hour = 0;
    day = 0;
    month = 0;
    year = 0;
    daylight_saving = 0;
}

#if DEV
// Callback function (get's called when time adjusts via NTP)
void TimeM::timeavailable(struct timeval *t)
{   
    #if DEV
        Serial.println("Got time adjustment from NTP!");
    #endif
}
#endif

//Init the connection to the NTP server
void TimeM::init(void){
    #if DEV
    // set notification call-back function
    sntp_set_time_sync_notification_cb( timeavailable );
    #endif
    
    configTzTime(time_zone, ntpServer1, ntpServer2);
}

//Public methods
bool TimeM::update_time(void)
{
    bool check = getLocalTime(&timeinfo);
    if(!check){
        #if DEV
        Serial.println("No time available (yet)");
        #endif
    }else{
        day = timeinfo.tm_mday;
        hour = timeinfo.tm_hour;
        min = timeinfo.tm_min;
        second = timeinfo.tm_sec;
        month = timeinfo.tm_mon + 1;
        year = timeinfo.tm_year + 1900;
        daylight_saving = timeinfo.tm_isdst;
        #if DEV
        Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S, %I");
        Serial.println(year);
        #endif
    }
    return check;
}


