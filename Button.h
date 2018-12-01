#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
Button(uint32_t pin) : _pin(pin), 
_isTriggered(false), 
_isPushed(false) {
  
}

void update() {
  _isPushed = digitalRead(_pin) == HIGH;

  if(_isPushed && !_isTriggered) {
    _isTriggered = true;
  }  else {
    _isTriggered = false;
  }
}

bool isPushed() {
  return _isPushed;
}

bool isTriggered() {
  return _isTriggered;
}

private:
uint32_t _pin;
bool _isTriggered;
bool _isPushed;
  
};

#endif
