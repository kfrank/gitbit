#ifndef GESTURE_H
#define GESTURE_H

enum class  GestureState : uint8_t {
  READY = 0,
  IN_PROGRESS = 1,
  COMPLETE = 2
};

class Gesture {
  public:
    Gesture(uint8_t startValue, uint8_t endValue) : _startValue(startValue), _endValue(endValue), _state(GestureState::READY) {

    }

    virtual void update(uint8_t currentPosition) {
      switch (_state) {
        case GestureState::READY:
          if (startGesture(currentPosition)) {
            _state = GestureState::IN_PROGRESS;
          }
          break;
        case GestureState::IN_PROGRESS:
          if (endGesture(currentPosition)) {
            _state = GestureState::COMPLETE;
          } else if(currentPosition == 0) {
            _state = GestureState::READY;
          }
          break;
        case GestureState::COMPLETE:
          if (currentPosition == 0) {
            _state = GestureState::READY;
          }
          break;
      }
    }

    virtual bool startGesture(uint8_t value) = 0;
    virtual bool endGesture(uint8_t value) = 0;

    GestureState getState() {
      return _state;
    }

  protected:
    uint8_t _startValue;
    uint8_t _endValue;

  private:
    GestureState _state;
};

class GestureRight : public Gesture {
  public:
    GestureRight(uint8_t startValue, uint8_t endValue) : Gesture(startValue, endValue) {
    }

    virtual bool startGesture(uint8_t value) {
      return 0 < value && value < _startValue;
    }

    virtual bool endGesture(uint8_t value) {
      return value > _endValue;
    }
};

class GestureLeft : public Gesture {
  public:
    GestureLeft(uint8_t startValue, uint8_t endValue) : Gesture(startValue, endValue) {
    }

    virtual bool startGesture(uint8_t value) {
      return value > _startValue;
    }

    virtual bool endGesture(uint8_t value) {
      return value > 0 && value < _endValue;
    }
};

#endif
