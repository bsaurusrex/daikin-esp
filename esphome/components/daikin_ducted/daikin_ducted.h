#pragma once

#include "esphome/components/climate/climate.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/homeassistant/homeassistant.h"
#include "homebus_rmt.h"

namespace esphome
{
   namespace daikin_ducted
   {
      class DaikinClimate : public climate::Climate
      {
      public:
         DaikinClimate();

         void control(const climate::ClimateCall &call);
         climate::ClimateTraits traits(void);

         // External power sensor integration (optional, for real-time COP)
         void set_external_power_sensor(Sensor *sensor) { this->external_power_sensor = sensor; }
         void update_realtime_cop(float power_watts);  // Called when external power sensor updates

         // Sensor pointers for thermistors (Th1-Th6)
         sensor::Sensor *thermistor_th1 = nullptr;
         sensor::Sensor *thermistor_th2 = nullptr;
         sensor::Sensor *thermistor_th3 = nullptr;
         sensor::Sensor *thermistor_th4 = nullptr;
         sensor::Sensor *thermistor_th5 = nullptr;
         sensor::Sensor *thermistor_th6 = nullptr;

         // Sensor pointers for energy data
         sensor::Sensor *energy_produced = nullptr;           // kWh (x0.1)
         sensor::Sensor *electricity_consumed = nullptr;      // kWh (x0.1)
         sensor::Sensor *runtime_hours = nullptr;             // system runtime hours
         sensor::Sensor *compressor_runtime_hours = nullptr;  // compressor runtime hours

         // COP sensors
         sensor::Sensor *cop_lifetime = nullptr;              // lifetime COP
         sensor::Sensor *cop_period = nullptr;                // COP since baseline (period)
         sensor::Sensor *cop_realtime = nullptr;              // real-time COP (integrated with external meter)

         // External power meter integration (optional)
         // TODO: Implement Home Assistant sensor subscription to wire up external power sensor
         // Currently, external_power_sensor pointer is declared but not integrated with HA
         Sensor *external_power_sensor = nullptr;             // External power meter (watts) from HA
         float external_power_watts = 0.0f;                   // Cache of latest power reading

         // Product info sensors
         text_sensor::TextSensor *product_name = nullptr;     // from packet 0xA1
         text_sensor::TextSensor *f_series_variant = nullptr; // detected F-series variant (A, B, C, L, LA, M, P, PA)

         // Operational state binary sensors
         binary_sensor::BinarySensor *compressor_active = nullptr; // from packet 0x10

         // COP calculation state
         struct {
            uint32_t baseline_energy_produced = 0;    // baseline for period calculation
            uint32_t baseline_electricity_consumed = 0;
            bool baselines_initialized = false;
         } cop_state_;

         // Field settings cache (up to 48 field settings: 0x60-0x8F, 3 packets each)
         struct {
            uint8_t settings[48];          // Field setting values
            uint32_t last_write_time = 0;  // Timestamp of last write attempt
            uint8_t pending_write_idx = 0xFF; // Index pending write (0xFF = none)
            uint32_t pending_write_value = 0;
            bool initialized = false;
         } field_settings_;

      protected:
         static void callback(void *arg, const uint8_t buffer[], const uint32_t buffer_length);
         HomebusRMT homebus_;

         bool mode_updated = false;
         bool fan_updated = false;
         bool target_temperature_updated = false;

         float last_temp_state;

         // COP and energy data cache for processing
         struct {
            uint32_t energy_produced = 0;
            uint32_t electricity_consumed = 0;
            uint32_t runtime_hours = 0;
            uint32_t compressor_runtime = 0;
            float th1 = 0, th2 = 0, th3 = 0, th4 = 0, th5 = 0, th6 = 0;
            bool compressor_state = false;
            char product_id[17] = {0};  // null-terminated
            char f_variant = 0;  // A, B, C, L, M, P, 0=unknown
            bool has_new_energy_data = false;
            bool has_new_thermistor_data = false;
            bool has_new_operating_status = false;
         } cache_;
      };

   } // namespace daikin_ducted
} // namespace esphome
