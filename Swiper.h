#ifndef SWIPER_H
#define SWIPER_H

#include "Gesture.h"

class Swiper {
  public:
    Swiper(uint8_t pin) : _pin(pin), _pullGesture(8, 2), _pushGesture(2, 8) {

    }

    GestureState getPullState() {
      return _pullGesture.getState();
    }

    GestureState getPushState() {
      return _pullGesture.getState();
    }

    void init() {
      pinMode(_pin, INPUT);
    }

    void update() {
      uint32_t currentPosition = analogRead(_pin);
      currentPosition = map(currentPosition, 0, 1023, 0, 10);

      if(_pullGesture.getState() == GestureState::READY) {
        execute(&_pushGesture, currentPosition, "push");
      } 

      if(_pushGesture.getState() == GestureState::READY) {
        execute(&_pullGesture, currentPosition, "pull");
      }
    }

  private:
    void execute(Gesture* gesture, uint8_t currentPosition, const String& command) {
      if (nullptr == gesture) {
        return;
      }

      GestureState prevState = gesture->getState();
      gesture->update(currentPosition);

      if (prevState == GestureState::IN_PROGRESS && gesture->getState() == GestureState::COMPLETE) {
        Serial.println(command);
      }
    }

    uint8_t _pin;
    GestureLeft _pullGesture;
    GestureRight _pushGesture;

};

#endif
