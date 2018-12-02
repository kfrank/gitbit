#ifndef SELECTABLELCD_H
#define SELECTABLELCD_H
#include <ArduinoSTL.h>
#include "Adafruit_LiquidCrystal.h"

class SelectableLCD {
  public:
    SelectableLCD(uint32_t knobPin): _lcd(0), _knobPin(knobPin), _selectedIndex(0), _status() {
      _lcd.begin(16, 2);
      resetLCD();
    }

    void setValues(std::vector<String> values) {
      _values = values;
    }

    void update() {
      // check to see if the knob changes ??
      uint32_t knobPosition = analogRead(_knobPin);
      uint32_t index = std::min(3, (int)map(knobPosition, 0, 1023, 0, _values.size()));
      

      // if the knob position is different than when it was first read
      if (_selectedIndex != index) {
        _selectedIndex = index;
        _status = true;
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
    uint32_t _knobPin = 2;
    std::vector<String> _values;
    uint32_t _selectedIndex;
    boolean _status = false;

};

#endif
