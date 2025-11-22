#include "GPIO.h"

void pinMode(int pin, Direction mode) {
  gpio_config_t cfg = {
      .pin_bit_mask = 1ULL << pin,
      .mode = mode,
  };
  gpio_config(&cfg);
}

void digitalWrite(int pin, GPIO_STATE value) {
  gpio_set_level(pin, value);
}

GPIO_STATE digitalRead(int pin) {
  return gpio_get_level(pin);
}