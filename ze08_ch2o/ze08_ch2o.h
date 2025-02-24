#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace ze08_ch2o {

static const char *TAG = "ze08_ch2o";
static const uint8_t ZE08_SET_QA_MODE[] = {0xFF, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46};
static const uint8_t ZE08_QUESTION[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
static const char *ZE08_MODE_QA = "QA";
static const char *ZE08_MODE = ZE08_MODE_QA;

class ZE08CH2OSensor : public PollingComponent, public uart::UARTDevice {
 public:
  ZE08CH2OSensor() : uart::UARTDevice(nullptr) {}
  
  void set_uart_parent(uart::UARTComponent *parent) {
    this->parent_ = parent;
    this->uart::UARTDevice::set_uart_parent(parent);
  }
  
  void set_formaldehyde_sensor(sensor::Sensor *sensor) { this->ch2o_ppb_ = sensor; }
  
  void setup() override {
    this->set_update_interval(5000);
    if (ZE08_MODE == ZE08_MODE_QA) {
      write_array(ZE08_SET_QA_MODE, sizeof(ZE08_SET_QA_MODE));
    }
  }
  
  void update() override {
    write_array(ZE08_QUESTION, sizeof(ZE08_QUESTION));
    
    unsigned char buf[9];
    
    if (this->available() != sizeof(buf)) {
        ESP_LOGE(TAG, "Bad response from ZE08! received %d bytes.", this->available());
        return;
    }
    
    if (!read_array(buf, sizeof(buf))) {
      ESP_LOGE(TAG, "Error reading from ZE08!");
      return;
    }

    unsigned short concentration_ugm3 = (buf[2] << 8) | buf[3];
    unsigned short concentration_ppb = (buf[6] << 8) | buf[7];
    
    ESP_LOGD(TAG, "Received %u %u", concentration_ugm3, concentration_ppb);

    unsigned char checksum_calc = ~(buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + buf[7]) + 1;
    if (buf[8] != checksum_calc) {
        ESP_LOGE(TAG, "Bad checksum from ZE08! received %d != %d.", buf[8], checksum_calc);
    }

    if (this->ch2o_ppb_ != nullptr)
      this->ch2o_ppb_->publish_state(concentration_ppb);
  }

 protected:
  sensor::Sensor *ch2o_ppb_{nullptr};
  uart::UARTComponent *parent_{nullptr};
};

}  // namespace ze08_ch2o
}  // namespace esphome