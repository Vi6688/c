#include "driver/gpio.h"

typedef enum {
  INPUT = GPIO_MODE_INPUT,
  OUTPUT = GPIO_MODE_OUTPUT,
} Direction;

typedef enum {
  LOW = 0,
  HIGH = 1,
} GPIO_STATE;

void pinMode(int pin, Direction mode);
void digitalWrite(int pin, GPIO_STATE value);
GPIO_STATE digitalRead(int pin);