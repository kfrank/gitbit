#ifndef LEDANIMATION_H
#define LEDANIMATION_H

#include <ArduinoSTL.h>
#include "Animation.h"
#include "LED.h"

class SolidColorAnimation : public Animation {
  public:
    SolidColorAnimation(LED* led, Color color, uint32_t duration_msec) :
      _led(led),
      _color(color),
      _startTime_msec(0),
      _duration_msec(duration_msec) {
    }

    virtual void start() {
      Animation::start();
      _startTime_msec = millis();
    }

    virtual void update() {
      switch (getState()) {
        case AnimationState::READY:
          _led->off();
          return;
        case AnimationState::RUNNING:
          {
            uint16_t currentTime = millis();
            if (checkComplete(currentTime)) {
              _state = AnimationState::COMPLETE;
              return;
            }

            _led->setColor(_color);
            return;
          }
        case AnimationState::COMPLETE:
          _led->off();
          return;
      }
    }

  private:
    bool checkComplete(uint16_t currentTime) {
      return (currentTime - _startTime_msec) >= _duration_msec;
    }
    Color _color;
    LED* _led;

    uint32_t _duration_msec;
    uint32_t _startTime_msec;
};

class DualColorAnimation : public Animation {
  public:
    DualColorAnimation(LED* led, Color startColor, Color endColor, uint32_t duration_msec) :
      _led(led),
      _startValue(startColor),
      _endValue(endColor),
      _startTime_msec(0),
      _duration_msec(duration_msec) {
    }

    void setLED(LED* led) {
      _led = led;
    }

    void setDuration(uint32_t duration_msec) {
      _duration_msec = duration_msec;
    }

    virtual void start() {
      Animation::start();
      _startTime_msec = millis();
    }

    virtual void update() {
      switch (getState()) {
        case AnimationState::READY:
          _led->off();
          return;
        case AnimationState::RUNNING:
          {
            
            uint32_t currentTime = millis();
            if (checkComplete(currentTime)) {
              _state = AnimationState::COMPLETE;
              return;
            }

            Color currentColor = {
              linearInterpolation(_startValue.red, _endValue.red, currentTime),
              linearInterpolation(_startValue.green, _endValue.green, currentTime),
              linearInterpolation(_startValue.blue, _endValue.blue, currentTime)
            };

            _led->setColor(currentColor);
            return;
          }
        case AnimationState::COMPLETE:
          _led->setColor(_endValue);
          return;
      }
    }

  private:
    bool checkComplete(uint16_t currentTime) {
      return (currentTime - _startTime_msec) >= (uint32_t)_duration_msec;
    }

    uint32_t linearInterpolation(int16_t startValue, int16_t endValue, uint32_t currentTime) {
      double deltaTime = (currentTime - _startTime_msec);
      double progress = ( deltaTime / (double)_duration_msec);
      int32_t deltaValue = startValue + progress * (endValue - startValue);

      return std::max((int32_t)0, deltaValue);
    }

    Color _startValue;
    Color _endValue;
    LED* _led;

    uint32_t _duration_msec;
    uint32_t _startTime_msec;
};

#endif
