#include "credential.h"

//CONFIG
#define DEV 1 //1 if dev mode 0 production mode
#define BAUDRATE 115200
//The smaller the more accurate but the less battery life
#define PRECISON_CLOCK 5000 //in second


//Ecran TFT configuration
#define TFT_GREY 0x5AEB // Grey colour 
/* PIN ESP32  | PIN TFT
*       3,3V  | VCC 
*         GND | GND
*         D15 | CS
*          D4 | RESET
*          D2 | DC
*         D23 | MOSI
*         D18 | SCK
*       3,3V  | LED
*         D19 | MISO
*/

//Timer configuration
#define TIME_ZONE "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00"; //Time zone for the clock
/*==== Planet widget ==== */
//Size to display
#define SIZE_SUN 20             //in pixel
#define SIZE_EARTH 10           //in pixel
#define SIZE_MOON 5             //in pixel
#define ORBIT_RADIU_EARTH 60    //in pixel
#define ORBIT_RADIU_MOON 20     //in pixel
//Define in how many days it will do the entire rotation
#define TEMPS_REVOLUTION_EARTH 365  //in days
#define TEMPS_REVOLUTION_MOON 27    //in days
//the center of the planet widget x
#define CENTER_PLANET_X 150     //in pixels
#define CENTER_PLANET_Y 90      //in pixels
//Define the angle for the 1 of january
#define ANGLE_OFFSET M_PI_2     //in radian 


/*==== weather widget ====*/
//The weather widget is a small widget that display the weather
#define CENTER_WEATHER_X 150   //in pixels
#define TOP_WEATHER_Y 220   //in pixels
//define the URL to request :
#define WEATHER_APIKEY WEATHER_TOKEN
//USING Open weather API USE THIS : 
#define OPEN_WEATHER 1
//USING meteo-concept (FRANCE ONLY !):
#define METEO_CONCEPT 0
//Complete the following : 
#if OPEN_WEATHER
  #define WEATHER_CITY "Angers"
  #define WEATHER_CONTRY "FR"
  #define URL_API "XXXX" WEATHER_CITY "," WEATHER_CONTRY "&units=metric&APPID=" WEATHER_APIKEY
#endif
#if METEO_CONCEPT
  #define INSEE "XXXXX"
  #define URL_API "XXXX" INSEE "&token=" WEATHER_APIKEY
#endif