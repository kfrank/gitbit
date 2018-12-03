#include "SelectableLCD.h"
#include "Button.h"
#include "LEDAnimation.h"
#include "Swiper.h"

// Configuration
const std::vector<String> BRANCH_NAMES = {"design/headersidebar", "design/challenges", "dev/npm", "kf/home_news"};
const std::vector<uint8_t> TEAM_LEDS = {1, 2, 3, 4, 5, 6};
const std::vector<uint8_t> STATUS_LEDS = {7, 8, 9, 10, 11};
const uint8_t NUM_LEDS = 60;
const uint8_t LED_DATA_PIN = 3;

const Color GREEN = {255, 255, 100};
const Color BLUE = {180, 255, 100};
const Color BLACK = {0, 0, 0};

//Swiper
Swiper swiper(3);

//LCD
SelectableLCD selectableLCD(2);

//LEDs
std::vector<LED*> leds;
CRGB ledStrip[NUM_LEDS];

//Button
Button teamMemberCommitTrigger(12);

//Animations
std::vector<Animation*> teamCommitAnimations;
Animation* progressAnimation;
Animation* pushCompleteAnimation;
Animation* pullCompleteAnimation;

void initializeLeds(const std::vector<uint8_t>& indexes) {
  for (uint8_t index : indexes) {
    LED* led = new LED(&ledStrip[index]);
    leds.push_back(led);
  }
}

void createPushPullAnimations() {
  std::vector<Animation*> sequentialScript;
  for (uint8_t i = 7; i < 10; i++) {
    sequentialScript.push_back(new SolidColorAnimation(leds[i], BLUE, 1));
  }

  progressAnimation = new SequentialAnimation(sequentialScript);
  pushCompleteAnimation = new SolidColorAnimation(leds[10], GREEN, 1);
  pullCompleteAnimation = new SolidColorAnimation(leds[6], GREEN, 1);
}

void setup() {
  Serial.begin(9600);

  swiper.init();
//  teamMemberCommitTrigger.init();

  selectableLCD.init(16, 2);
  selectableLCD.setValues(BRANCH_NAMES);

  // LED setup
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(ledStrip, NUM_LEDS);

  // initialize LEDs
  initializeLeds(TEAM_LEDS);
  initializeLeds(STATUS_LEDS);

  for (uint8_t i = 0; i < 6; i++) {
    teamCommitAnimations.push_back(new LEDAnimation(leds[i], GREEN, BLUE, 10));
  }

  createPushPullAnimations();
}

void loop() {

  for (Animation* animation : teamCommitAnimations) {
    animation->update();
  }

  // If you change branch, commit lights should clear

  if (selectableLCD.update()) {
    for (Animation* animation : teamCommitAnimations) {
      animation->reset();
    }
  }

  // If you press button, one commit should light up

  teamMemberCommitTrigger.update();

  if (teamMemberCommitTrigger.isTriggered()) {
    teamCommitAnimations[random(6)]->start();
  }

  // If you pull, the status leds should execute
  progressAnimation->update();
  pullCompleteAnimation->update();

  bool actionComplete = swiper.update();
  if (actionComplete && swiper.getPullState() == GestureState::COMPLETE) {
    progressAnimation->start();
  }
  if(progressAnimation->isComplete() && swiper.getPullState() == GestureState::COMPLETE) {
    pullCompleteAnimation->start();
    progressAnimation->reset();
    swiper.reset();
    for (Animation* animation : teamCommitAnimations) {
      animation->reset();
    }
  }

  //If you push, status leds should execute
  pushCompleteAnimation->update();
  if (actionComplete && swiper.getPushState() == GestureState::COMPLETE) {
    progressAnimation->start();
  }
  if(progressAnimation->isComplete() && swiper.getPushState() == GestureState::COMPLETE) {
    pushCompleteAnimation->start();
    progressAnimation->reset();
    swiper.reset();
  }
  
}
