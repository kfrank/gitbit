#ifndef LED_H
#define LED_H

#include <FastLED.h>

struct Color {
  uint8_t hue;
  uint8_t saturation;
  uint8_t value;
};

class LED {
  public:
    LED(CRGB* ledAddr) : _ledAddr(ledAddr)
    {
    }

    void off() {
      setColor(0,0,0);
    }

    void setColor(Color color) {
      setColor(color.hue, color.saturation, color.value);
    }

    void setColor(uint8_t hue, uint8_t saturation, uint8_t value) {
      //set the led
      *_ledAddr = CHSV(hue, saturation, value);
      FastLED.show();
    }

  private:
    CRGB* _ledAddr;
};

#endif
