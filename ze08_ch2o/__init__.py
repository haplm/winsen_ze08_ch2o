import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ['uart']
AUTO_LOAD = ['sensor']

ze08_ch2o_ns = cg.esphome_ns.namespace('ze08_ch2o')
ZE08CH2OSensor = ze08_ch2o_ns.class_('ZE08CH2OSensor', cg.PollingComponent, uart.UARTDevice)

CONF_ZE08_ID = 'ze08_ch2o_id'

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ZE08CH2OSensor),
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
}).extend(cv.polling_component_schema('5s'))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    uart_component = await cg.get_variable(config[CONF_UART_ID])
    cg.add(var.set_uart_parent(uart_component))