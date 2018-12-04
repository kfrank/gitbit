#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
const uint8_t NUM_LEDS = 60;
const uint8_t LED_DATA_PIN = 3;
#define BRIGHTNESS 30
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(NUM_LEDS, LED_DATA_PIN, NEO_RGB + NEO_KHZ800);

struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

class LED {
  public:
    LED(uint16_t* ledAddr) : _ledAddr(ledAddr)
    {
    }

    void off() {
      setColor(0,0,0);
    }

    void setColor(Color color) {
      setColor(color.red, color.green, color.blue);
    }

    void setColor(uint8_t red, uint8_t green, uint8_t blue) {
      //set the led
      ledStrip.setPixelColor(_ledAddr, ledStrip.Color(red, green, blue));
      ledStrip.show();
    }

  private:
    uint16_t* _ledAddr;
};

#endif
