#ifndef __TEMP_SENSOR_NTC__
#define __TEMP_SENSOR_NTC__

#include "TempSensor.h"

class TempSensorNTC: public TempSensor {

public:
    TempSensorNTC(int pin);	
    virtual float getTemperature();
  
private:
    int pin;
};

#endif