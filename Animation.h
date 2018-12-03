#ifndef ANIMATION_H
#define ANIMATION_H

enum class AnimationState : uint8_t {
  READY = 0,
  RUNNING = 1,
  COMPLETE = 2
};

class Animation {
  public:
    Animation() : _state(AnimationState::READY) {}

    virtual void update() = 0;

    AnimationState getState() {
      return _state;
    }

    virtual void reset() {
      _state = AnimationState::READY;
    }

    virtual void start() {
      _state = AnimationState::RUNNING;
    }

    bool isComplete() {
      return _state == AnimationState::COMPLETE;
    }

    bool isRunning() {
      return _state == AnimationState::RUNNING;
    }

  protected:
    AnimationState _state;
};

class ParallelAnimation : public Animation {
  public:
    ParallelAnimation(std::vector<Animation*> animations)
      : _animations(animations) {
    }

    virtual void start() {
      for (Animation* animation : _animations) {
        animation->start();
      }

      Animation::start();
    }

    virtual void update() {
      if (!isRunning()) {
        return;
      }

      bool isComplete = true;
      for (Animation* animation : _animations) {
        animation->update();
        isComplete &= animation->isComplete();
      }

      if (isComplete) {
        _state = AnimationState::COMPLETE;
      }
    }

  private:
    std::vector<Animation*> _animations;
};

class SequentialAnimation : public Animation {
  public:
    SequentialAnimation(std::vector<Animation*> animations)
      : _animations(animations),
        _currentIndex(0) {
    }

    virtual void reset() {
      _currentIndex = 0;
      Animation::reset();
    }

    virtual void update() {

      if (!isRunning()) {
        return;
      }

      Animation* animation = _animations[_currentIndex];
      if (!animation->isRunning()) {
        animation->start();
      }

      animation->update();

      if (animation->isComplete()) {
        animation->update();
        _currentIndex++;
      }

      if (_currentIndex >= _animations.size()) {
        _state = AnimationState::COMPLETE;
      }
    }

  private:
    std::vector<Animation*> _animations;
    uint8_t _currentIndex;
};

#endif
