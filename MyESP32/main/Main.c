#include "include/GPIO.h"
#include "include/Timer.h"

#include <stdio.h>


#define LED_PIN 2

void setup() { pinMode(LED_PIN, OUTPUT); }
void app_main(void) {

  while (1) {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
  }
}
