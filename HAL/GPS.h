#ifndef GPS_H_
#define GPS_H_


#include "STD_TYPES.h"
#define MAX_FIELDS 14
#define MAX_FIELD_LENGTH 20
#define NO_OF_COORDINATES 20  //should be 200
#define PI 3.14159265358979323846 // Standard value of pi


extern float Extracted_Coordinates[1000][2];

float toRad(float num);
void Get_Data(uint8_t data[]);
uint8_t Check_fix();

void Process_str(uint8_t input[], double * latitude, double * longitude);
void Get_Map_Coordinates(double latitude, double longitude, uint8_t i);
float Get_GPS_distance(float currentlong, float currentlat, float deslong, float deslat);

#endif
