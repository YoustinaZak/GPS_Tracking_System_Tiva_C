#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "GPS.h"
#include "../MCAL/GPIO.h"
#include "../MCAL/UART.h"
#include "../LIB/STD_TYPES.h"

	
void Get_Data(uint8_t data[])
	{
		uint8_t i;
		while((UART2_FR_R & (1<<4))!=0){} //receive flag
		if( UART2_DR_R =='$')
				  {
						for(i=0; i<50; i++)
						{
					    data[i]= UART2_DR_R;
							if(data[i]=='*')
								{
									break;
								}
							while((UART2_FR_R & (1<<4))!=0){}
				    }		 
	        }
					
	}
	
	
uint8_t Check_fix (uint8_t inputChar)
{
		if(inputChar =='1')
			{
				return 1;
			}
		else
			{
				return 0;
			}
}


void Process_str(uint8_t input[], double * latitude, double * longitude) 
	{
		
		char *token;
		int fieldCount = 0;
		
		// divide input string by comma
    token = strtok(input, ",");
		
    while (token != NULL && fieldCount < MAX_FIELDS) ////////////check the token condtion seems wired
			{
				
				if(fieldCount==2)
					{
						*latitude = atof(token);
						 
				  }
				else if(fieldCount==4)
					{
						 *longitude = atof(token);
				  }
					else if(fieldCount==6)
					{
						if(!Check_fix(*token))     //check that the data is valid
						{
							*latitude=0;
							*longitude =0;
						}
						break;
					} 
		if(fieldCount == 3 && *token == 'S'){*latitude = - (*latitude) ;}
            	if(fieldCount == 5 && *token == 'W'){*longitude = - (*longitude) ;}
				
        fieldCount++;
        token = strtok(NULL, ",");    //get another string starting from Null to ,
      }		
}


void Get_Map_Coordinates(double latitude, double longitude, uint8_t i)
	{
     uint8_t lat_deg=0;
     float lat_min=0;
		
     float lon_deg=0;
     float lon_min=0;

    //calc latitude
    lat_deg = (uint8_t)(latitude / 100);
    lat_min = latitude - lat_deg * 100;
    //latitude = lat_deg + lat_min / 60;
    Extracted_Coordinates[i][0]= lat_deg + lat_min / 60;

    //calc longitude
     lon_deg = (uint8_t)(longitude / 100);
     lon_min = longitude - lon_deg * 100;
     //longitude = lon_deg + lon_min / 60;
		 Extracted_Coordinates[i][1]= lon_deg + lon_min / 60;
				
}
float toRad(float num) {
    return num * PI / 180;
}

float Get_GPS_distance(float currentlong, float currentlat, float deslong, float deslat) {
    float currentlongRad = toRad(currentlong);
    float currentlatRad = toRad(currentlat);
    float deslongRad = toRad(deslong);
    float deslatRad = toRad(deslat);

    // Haversine formula to calculate distance
    float dlon = deslongRad - currentlongRad;
    float dlat = deslatRad - currentlatRad;
    float a = pow(sin(dlat / 2), 2) + cos(currentlatRad) * cos(deslatRad) * pow(sin(dlon / 2), 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float distance = 6371 * c; // Radius of the Earth in kilometers

    return distance;
}
