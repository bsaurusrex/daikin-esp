import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, sensor, text_sensor, binary_sensor, homeassistant
from esphome.const import CONF_ID

AUTO_LOAD = ["climate"]

daikin_ns = cg.esphome_ns.namespace("daikin_ducted")
DaikinClimate = daikin_ns.class_("DaikinClimate", climate.Climate)

# Configuration keys for optional sensors
CONF_THERMISTOR_TH1 = "thermistor_th1"
CONF_THERMISTOR_TH2 = "thermistor_th2"
CONF_THERMISTOR_TH3 = "thermistor_th3"
CONF_THERMISTOR_TH4 = "thermistor_th4"
CONF_THERMISTOR_TH5 = "thermistor_th5"
CONF_THERMISTOR_TH6 = "thermistor_th6"

CONF_ENERGY_PRODUCED = "energy_produced"
CONF_ELECTRICITY_CONSUMED = "electricity_consumed"
CONF_RUNTIME_HOURS = "runtime_hours"
CONF_COMPRESSOR_RUNTIME = "compressor_runtime_hours"

CONF_COP_LIFETIME = "cop_lifetime"
CONF_COP_PERIOD = "cop_period"
CONF_COP_REALTIME = "cop_realtime"

CONF_PRODUCT_NAME = "product_name"
CONF_F_SERIES_VARIANT = "f_series_variant"
CONF_COMPRESSOR_ACTIVE = "compressor_active"

# External power meter for real-time COP
CONF_EXTERNAL_POWER_SENSOR_ID = "external_power_sensor_id"

CONFIG_SCHEMA = climate.CLIMATE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(DaikinClimate),
        # Optional thermistor sensors (6 temperature sensors)
        cv.Optional(CONF_THERMISTOR_TH1): sensor.sensor_schema(
            unit_of_measurement="°C", accuracy_decimals=2
        ),
        cv.Optional(CONF_THERMISTOR_TH2): sensor.sensor_schema(
            unit_of_measurement="°C", accuracy_decimals=2
        ),
        cv.Optional(CONF_THERMISTOR_TH3): sensor.sensor_schema(
            unit_of_measurement="°C", accuracy_decimals=2
        ),
        cv.Optional(CONF_THERMISTOR_TH4): sensor.sensor_schema(
            unit_of_measurement="°C", accuracy_decimals=2
        ),
        cv.Optional(CONF_THERMISTOR_TH5): sensor.sensor_schema(
            unit_of_measurement="°C", accuracy_decimals=2
        ),
        cv.Optional(CONF_THERMISTOR_TH6): sensor.sensor_schema(
            unit_of_measurement="°C", accuracy_decimals=2
        ),
        # Optional energy counters
        cv.Optional(CONF_ENERGY_PRODUCED): sensor.sensor_schema(
            unit_of_measurement="kWh", accuracy_decimals=1
        ),
        cv.Optional(CONF_ELECTRICITY_CONSUMED): sensor.sensor_schema(
            unit_of_measurement="kWh", accuracy_decimals=1
        ),
        cv.Optional(CONF_RUNTIME_HOURS): sensor.sensor_schema(
            unit_of_measurement="h", accuracy_decimals=0
        ),
        cv.Optional(CONF_COMPRESSOR_RUNTIME): sensor.sensor_schema(
            unit_of_measurement="h", accuracy_decimals=0
        ),
        # Optional COP sensors
        cv.Optional(CONF_COP_LIFETIME): sensor.sensor_schema(
            unit_of_measurement="", accuracy_decimals=2
        ),
        cv.Optional(CONF_COP_PERIOD): sensor.sensor_schema(
            unit_of_measurement="", accuracy_decimals=2
        ),
        cv.Optional(CONF_COP_REALTIME): sensor.sensor_schema(
            unit_of_measurement="", accuracy_decimals=2
        ),
        # Optional product info sensors
        cv.Optional(CONF_PRODUCT_NAME): text_sensor.text_sensor_schema(),
        cv.Optional(CONF_F_SERIES_VARIANT): text_sensor.text_sensor_schema(),
        # Optional operational state sensors
        cv.Optional(CONF_COMPRESSOR_ACTIVE): binary_sensor.binary_sensor_schema(),

        # Optional external power meter for real-time COP
        cv.Optional(CONF_EXTERNAL_POWER_SENSOR_ID): cv.string,
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await climate.register_climate(var, config)

    # Register thermistor sensors
    if CONF_THERMISTOR_TH1 in config:
        sens = await sensor.new_sensor(config[CONF_THERMISTOR_TH1])
        cg.add(var.thermistor_th1 = sens)
    if CONF_THERMISTOR_TH2 in config:
        sens = await sensor.new_sensor(config[CONF_THERMISTOR_TH2])
        cg.add(var.thermistor_th2 = sens)
    if CONF_THERMISTOR_TH3 in config:
        sens = await sensor.new_sensor(config[CONF_THERMISTOR_TH3])
        cg.add(var.thermistor_th3 = sens)
    if CONF_THERMISTOR_TH4 in config:
        sens = await sensor.new_sensor(config[CONF_THERMISTOR_TH4])
        cg.add(var.thermistor_th4 = sens)
    if CONF_THERMISTOR_TH5 in config:
        sens = await sensor.new_sensor(config[CONF_THERMISTOR_TH5])
        cg.add(var.thermistor_th5 = sens)
    if CONF_THERMISTOR_TH6 in config:
        sens = await sensor.new_sensor(config[CONF_THERMISTOR_TH6])
        cg.add(var.thermistor_th6 = sens)

    # Register energy counter sensors
    if CONF_ENERGY_PRODUCED in config:
        sens = await sensor.new_sensor(config[CONF_ENERGY_PRODUCED])
        cg.add(var.energy_produced = sens)
    if CONF_ELECTRICITY_CONSUMED in config:
        sens = await sensor.new_sensor(config[CONF_ELECTRICITY_CONSUMED])
        cg.add(var.electricity_consumed = sens)
    if CONF_RUNTIME_HOURS in config:
        sens = await sensor.new_sensor(config[CONF_RUNTIME_HOURS])
        cg.add(var.runtime_hours = sens)
    if CONF_COMPRESSOR_RUNTIME in config:
        sens = await sensor.new_sensor(config[CONF_COMPRESSOR_RUNTIME])
        cg.add(var.compressor_runtime_hours = sens)

    # Register COP sensors
    if CONF_COP_LIFETIME in config:
        sens = await sensor.new_sensor(config[CONF_COP_LIFETIME])
        cg.add(var.cop_lifetime = sens)
    if CONF_COP_PERIOD in config:
        sens = await sensor.new_sensor(config[CONF_COP_PERIOD])
        cg.add(var.cop_period = sens)
    if CONF_COP_REALTIME in config:
        sens = await sensor.new_sensor(config[CONF_COP_REALTIME])
        cg.add(var.cop_realtime = sens)

    # Register text sensors
    if CONF_PRODUCT_NAME in config:
        text_sens = await text_sensor.new_text_sensor(config[CONF_PRODUCT_NAME])
        cg.add(var.product_name = text_sens)
    if CONF_F_SERIES_VARIANT in config:
        text_sens = await text_sensor.new_text_sensor(config[CONF_F_SERIES_VARIANT])
        cg.add(var.f_series_variant = text_sens)

    # Register binary sensors
    if CONF_COMPRESSOR_ACTIVE in config:
        bin_sens = await binary_sensor.new_binary_sensor(config[CONF_COMPRESSOR_ACTIVE])
        cg.add(var.compressor_active = bin_sens)

    # Register external power sensor for real-time COP (optional)
    # External power sensors are referenced as Home Assistant entity IDs
    if CONF_EXTERNAL_POWER_SENSOR_ID in config:
        power_sensor_id = config[CONF_EXTERNAL_POWER_SENSOR_ID]
        # Configuration validated: power_sensor_id = e.g., "sensor.enermon_ac_red_watts"
        #
        # TODO: Future enhancement - integrate with Home Assistant sensor subscription
        # to automatically call update_realtime_cop() when power sensor updates.
        # For now, the configuration is accepted but not wired to C++ code.
        #
        # Implementation would involve:
        # 1. Register Home Assistant service to subscribe to entity state changes
        # 2. On state change, call var->update_realtime_cop(power_value)
        # 3. Support per-phase monitoring (Red/Yellow/Blue phases for multi-unit setups)
        pass
