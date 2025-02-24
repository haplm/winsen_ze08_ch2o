import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_VOLATILE_ORGANIC_COMPOUNDS,
    STATE_CLASS_MEASUREMENT,
    UNIT_PARTS_PER_BILLION,
)
from . import ZE08CH2OSensor, ze08_ch2o_ns

CONF_FORMALDEHYDE = "formaldehyde"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.use_id(ZE08CH2OSensor),
    cv.Required(CONF_FORMALDEHYDE): sensor.sensor_schema(
        unit_of_measurement=UNIT_PARTS_PER_BILLION,
        device_class=DEVICE_CLASS_VOLATILE_ORGANIC_COMPOUNDS,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
})

async def to_code(config):
    parent = await cg.get_variable(config[CONF_ID])
    
    if CONF_FORMALDEHYDE in config:
        sens = await sensor.new_sensor(config[CONF_FORMALDEHYDE])
        cg.add(parent.set_formaldehyde_sensor(sens))