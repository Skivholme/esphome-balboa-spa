#pragma once
#include "esphome/components/text_sensor/text_sensor.h"
#include "../balboaspa.h"

namespace esphome
{
  namespace balboa_spa
  {

    // Diagnostic: publishes the raw payload of the spa's status update (FF AF 13) as hex,
    // one byte per field, so undecoded fields can be compared between situations
    // (e.g. normal vs. freeze protection). The clock bytes (payload 3 and 4) are masked
    // as "--" so the value only changes when something other than the time changes.
    class RawStatusTextSensor : public text_sensor::TextSensor
    {
    public:
      void set_parent(BalboaSpa *parent);
      void update(SpaState *spaState);

    private:
      uint8_t last_[SpaState::RAW_STATUS_MAX] = {0};
      uint8_t last_len_ = 0;
    };

  } // namespace balboa_spa
} // namespace esphome
