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
    LED(uint8_t index, CRGB* ledStrip) : _index(index), _ledStrip(ledStrip), _color( {
      0, 0, 0
    })
    {
    }

    void off() {
      setColor(0,0,0);
    }

    void setColor(Color color) {
      setColor(color.hue, color.saturation, color.value);
    }

    void setColor(uint32_t hue, uint32_t saturation, uint32_t value) {
      //set the led
      _ledStrip[_index] = CHSV(hue, saturation, value);
      FastLED.show();
    }

  private:
    uint8_t _index;
    CRGB* _ledStrip;
    Color _color;
};

#endif
