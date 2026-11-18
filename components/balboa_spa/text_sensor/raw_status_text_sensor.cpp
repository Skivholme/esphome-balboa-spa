#include "raw_status_text_sensor.h"

namespace esphome
{
    namespace balboa_spa
    {
        static const char *TAG = "balboa_spa.text_sensor.raw_status";

        // Payload positions of the spa clock (hour, minute) - masked so they don't cause updates
        static const uint8_t RAW_STATUS_HOUR = 3;
        static const uint8_t RAW_STATUS_MINUTE = 4;

        void RawStatusTextSensor::set_parent(BalboaSpa *parent)
        {
            parent->register_listener(
                [this](SpaState *spaState)
                {
                    this->update(spaState);
                });
        }

        void RawStatusTextSensor::update(SpaState *spaState)
        {
            const uint8_t len = spaState->raw_status_len;
            if (len == 0)
                return;

            bool changed = (len != last_len_);
            for (uint8_t i = 0; i < len && !changed; i++)
            {
                if (i == RAW_STATUS_HOUR || i == RAW_STATUS_MINUTE)
                    continue;
                if (spaState->raw_status[i] != last_[i])
                    changed = true;
            }
            if (!changed)
                return;

            std::string out;
            out.reserve(len * 3);
            char buf[4];
            for (uint8_t i = 0; i < len; i++)
            {
                last_[i] = spaState->raw_status[i];
                if (i > 0)
                    out += ' ';
                if (i == RAW_STATUS_HOUR || i == RAW_STATUS_MINUTE)
                {
                    out += "--";
                    continue;
                }
                snprintf(buf, sizeof(buf), "%02X", spaState->raw_status[i]);
                out += buf;
            }
            last_len_ = len;

            ESP_LOGI(TAG, "Spa/raw_status: %s", out.c_str());
            this->publish_state(out);
        }

    } // namespace balboa_spa
} // namespace esphome
