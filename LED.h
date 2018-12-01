#ifndef LED_H
#define LED_H

#include <FastLED.h>
#define NUM_LEDS 60
#define DATA_PIN 3
CRGB leds[NUM_LEDS];

struct Color {
  uint8_t hue;
  uint8_t saturation;
  uint8_t value;
};

class LED {
  public:
    LED(uint8_t index) : _index(index), _color( {
      0, 0, 0
    })
    {
    }

    void off(uint8_t index) {
      //set color to black
      leds[index] = CRGB::Black;
      FastLED.show();
    }

    void setColor(Color color) {
      setColor(color.hue, color.saturation, color.value);
    }

    void setColor(uint32_t hue, uint32_t saturation, uint32_t value) {
      //set the led
      leds[_index] = CHSV(hue, saturation, value);
      FastLED.show();
    }

  private:
    uint8_t _index;
    Color _color;
};

#endif
