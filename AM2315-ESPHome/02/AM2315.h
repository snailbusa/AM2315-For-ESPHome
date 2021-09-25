#include "esphome.h"

#include "Adafruit_AM2315.h"

class AM2315 : public PollingComponent, public Sensor {
 public:
  Adafruit_AM2315 mySensor;

  Sensor *temperature_sensor = new Sensor();
  Sensor *humidity_sensor = new Sensor();

  AM2315() : PollingComponent (10000) {}
  float get_setup_priority() const override { return esphome::setup_priority::BUS; }

  void setup() override {
    // Initialize the device here. Usually Wire.begin() will be called in here,
    // though that call is unnecessary if you have an 'i2c:' entry in your config

    mySensor.begin();
    
  }
  void update() override {
    // This is the actual sensor reading logic.
    float temperature;
    float humidity;
    
    mySensor.readTemperatureAndHumidity(&temperature, &humidity);
    
    temperature_sensor->publish_state(temperature);
    humidity_sensor->publish_state(humidity);
  }
};