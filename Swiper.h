#ifndef SWIPER_H
#define SWIPER_H

#include "Gesture.h"

class Swiper {
  public:
    Swiper(uint32_t pin) : _pin(pin), _pullGesture(new GestureLeft(8, 2)), _pushGesture(new GestureRight(2, 8)) {

    }

    ~Swiper() {
      delete(_pullGesture);
      delete(_pushGesture);
    }

    GestureState getPullState() {
      return _pullGesture->getState();
    }

    GestureState getPushState() {
      return _pullGesture->getState();
    }

    void update() {
      uint32_t currentPosition = analogRead(_pin);
      currentPosition = map(currentPosition, 0, 1023, 0, 10);

      if(_pullGesture->getState() == GestureState::READY) {
        execute(_pushGesture, currentPosition, "push");
      } 

      if(_pushGesture->getState() == GestureState::READY) {
        execute(_pullGesture, currentPosition, "pull");
      }
    }

  private:
    void execute(Gesture* gesture, uint32_t currentPosition, const String& command) {
      if (nullptr == gesture) {
        return;
      }

      GestureState prevState = gesture->getState();
      gesture->update(currentPosition);

      if (prevState == GestureState::IN_PROGRESS && gesture->getState() == GestureState::COMPLETE) {
        Serial.println(command);
      }
    }

    uint32_t _pin;
    Gesture* _pullGesture;
    Gesture* _pushGesture;

};

#endif
