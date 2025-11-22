#include "esp32/rom/ets_sys.h"
#include <stdint.h>
#include "../include/Timer.h"
#include "esp_timer.h"

void delay(timeInMs ms) {
    uint32_t start = esp_timer_get_time();  // microseconds
    while ((esp_timer_get_time() - start) < (ms * 1000)) {
    }
}



