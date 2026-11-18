#include <stdint.h>

#ifndef SPA_STATE_H
#define SPA_STATE_H

namespace esphome {
namespace balboa_spa {

class SpaState {
    public:
        SpaState() {
            rest_mode = 254;
            heat_state = 254;
            target_temp = NAN;
            current_temp = NAN;
            reminder = 0;
            raw_status_len = 0;
        }
        uint8_t jet1 :2;
        uint8_t jet2 :2;
        uint8_t jet3 :2;
        uint8_t jet4 :2;
        uint8_t blower :1;
        uint8_t light :1;
        uint8_t light2 :1;
        uint8_t highrange:1;        
        uint8_t circulation:1;
        uint8_t cleanup_cycle:1;
        uint8_t hour:5;
        uint8_t minutes:6;
        uint8_t rest_mode;
        uint8_t heat_state;
        float target_temp;
        float current_temp;
        uint8_t reminder;
        // Raw payload of the last status update (FF AF 13), for diagnostics (raw_status text sensor)
        static const uint8_t RAW_STATUS_MAX = 40;
        uint8_t raw_status[RAW_STATUS_MAX];
        uint8_t raw_status_len;
};
}  // namespace balboa_spa
}  // namespace esphome

#endif