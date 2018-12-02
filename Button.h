#ifndef BUTTON_H
#define BUTTON_H

class Button {
  public:
    Button(uint8_t pin) : _pin(pin),
      _isTriggered(false),
      _isPushed(false) {

    }

    void init() {
      pinMode(_pin, INPUT);
    }

    void update() {
      bool pushed = digitalRead(_pin) == HIGH;

      if (_isPushed != pushed && pushed) {
        _isTriggered = true;
      }  else {
        _isTriggered = false;
      }

      _isPushed = pushed;
    }

    bool isPushed() {
      return _isPushed;
    }

    bool isTriggered() {
      return _isTriggered;
    }

  private:
    uint8_t _pin;
    bool _isTriggered;
    bool _isPushed;

};

#endif
