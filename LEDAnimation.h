#ifndef LEDANIMATION_H
#define LEDANIMATION_H

#include <ArduinoSTL.h>
#include "Animation.h"
#include "LED.h"

class SolidColorAnimation : public Animation {
  public:
    SolidColorAnimation(LED* led, Color color, uint8_t duration_sec) :
      _led(led),
      _color(color),
      _startTime_sec(0),
      _duration_sec(duration_sec) {
    }

    virtual void start() {
      Animation::start();
      _startTime_sec = millis() / 1000;
    }

    virtual void update() {
      switch (getState()) {
        case AnimationState::READY:
          _led->off();
          return;
        case AnimationState::RUNNING:
          {
            uint16_t currentTime = millis() / 1000;
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
      return (currentTime - _startTime_sec) >= _duration_sec;
    }
    Color _color;
    LED* _led;

    uint8_t _duration_sec;
    uint16_t _startTime_sec;
};

class LEDAnimation : public Animation {
  public:
    LEDAnimation(LED* led, Color startColor, Color endColor, uint8_t duration_sec) :
      _led(led),
      _startValue(startColor),
      _endValue(endColor),
      _startTime_msec(0),
      _duration_sec(duration_sec) {
    }

    void setLED(LED* led) {
      _led = led;
    }

    void setDuration(uint8_t duration_sec) {
      _duration_sec = duration_sec;
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
              linearInterpolation(_startValue.hue, _endValue.hue, currentTime),
              linearInterpolation(_startValue.saturation, _endValue.saturation, currentTime),
              linearInterpolation(_startValue.value, _endValue.value, currentTime)
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
      return (currentTime - _startTime_msec) >= (uint32_t)_duration_sec * 1000;
    }

    uint32_t linearInterpolation(uint8_t startValue, uint8_t endValue, uint32_t currentTime) {
      float deltaTime = (currentTime - _startTime_msec);
      float progress = ( deltaTime / ((float)_duration_sec * 1000));
      uint8_t deltaValue = startValue + progress * ((int16_t)endValue - (int16_t)startValue);

      return std::max((uint8_t)0, deltaValue);
    }

    Color _startValue;
    Color _endValue;
    LED* _led;

    uint8_t _duration_sec;
    uint32_t _startTime_msec;
};

#endif
