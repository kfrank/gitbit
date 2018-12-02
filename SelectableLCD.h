#ifndef SELECTABLELCD_H
#define SELECTABLELCD_H
#include <ArduinoSTL.h>
#include "Adafruit_LiquidCrystal.h"

class SelectableLCD {
  public:
    SelectableLCD(uint8_t knobPin) :
      _lcd(0),
      _knobPin(knobPin),
      _selectedIndex(-1) {
    }

    void init(uint8_t numRows, uint8_t numCols) {
      _lcd.begin(numRows, numCols);
      resetLCD();

      pinMode(_knobPin, INPUT);
    }

    void setValues(std::vector<String> values) {
      _values = values;
    }

    void update() {
      // check to see if the knob changes ??
      uint16_t knobPosition = analogRead(_knobPin);
      uint8_t index = std::min((uint8_t)3, (uint8_t)map(knobPosition, 0, 1023, 0, _values.size()));

      // if the knob position is different than when it was first read
      if (_selectedIndex != index) {
        _selectedIndex = index;
        resetLCD();

        _lcd.print(_values[_selectedIndex]);
      }
    }

    bool isChanged() {
      //return _state == AnimationState::RUNNING;
    }

  private:
    void resetLCD() {
      _lcd.clear();
      _lcd.setCursor(0, 0);
    }

    Adafruit_LiquidCrystal _lcd;
    uint8_t _knobPin = 2;
    std::vector<String> _values;
    int8_t _selectedIndex;

};

#endif
