#include <Arduino.h>

#define PARAM_H


struct pin 
{

    int btn_droit = 22;
    int btn_devant = 24;
    int btn_gauche = 26;
    int btn_180 = 28;

};

typedef struct pin Pin;

