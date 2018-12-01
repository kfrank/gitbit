#ifndef GESTURE_H
#define GESTURE_H

enum class  GestureState {
  READY = 0,
  IN_PROGRESS = 1,
  COMPLETE = 2
};

class Gesture {
  public:
    Gesture(uint32_t startValue, uint32_t endValue) : _startValue(startValue), _endValue(endValue), _state(GestureState::READY) {

    }

    virtual void update(uint32_t currentPosition) {
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

    virtual bool startGesture(uint32_t value) = 0;
    virtual bool endGesture(uint32_t value) = 0;

    GestureState getState() {
      return _state;
    }

  protected:
    uint32_t _startValue;
    uint32_t _endValue;

  private:
    GestureState _state;
};

class GestureRight : public Gesture {
  public:
    GestureRight(uint32_t startValue, uint32_t endValue) : Gesture(startValue, endValue) {
    }

    virtual bool startGesture(uint32_t value) {
      return 0 < value && value < _startValue;
    }

    virtual bool endGesture(uint32_t value) {
      return value > _endValue;
    }
};

class GestureLeft : public Gesture {
  public:
    GestureLeft(uint32_t startValue, uint32_t endValue) : Gesture(startValue, endValue) {
    }

    virtual bool startGesture(uint32_t value) {
      return value > _startValue;
    }

    virtual bool endGesture(uint32_t value) {
      return value > 0 && value < _endValue;
    }
};

#endif
