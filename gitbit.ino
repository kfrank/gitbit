#include "SelectableLCD.h"
#include "Button.h"
#include "LEDAnimation.h"
#include "Swiper.h"

// Configuration
const std::vector<String> BRANCH_NAMES = {"gitbit/testing", "gitbit/design", "gitbit/source", "gitbit/master"};
const std::vector<uint8_t> TEAM_LEDS = {1, 2, 3, 4, 5, 6};
const std::vector<uint8_t> STATUS_LEDS = {7, 8, 9, 10, 11};

const Color GREEN = {0, 180, 0};
const Color BLUE = {0, 0, 200};
const Color BLACK = {0, 0, 0};

//Swiper
Swiper swiper(3);

//LCD
SelectableLCD selectableLCD(2);

//LEDs
LED teamLed(2);
std::vector<LED*> leds;
//CRGB ledStrip[NUM_LEDS];

//Button
Button teamMemberCommitTrigger(12);

//Animations
std::vector<Animation*> teamCommitAnimations;
Animation* progressAnimation;
Animation* pushCompleteAnimation;
Animation* pullCompleteAnimation;

void initializeLeds(const std::vector<uint8_t>& indexes) {
  for (uint8_t index : indexes) {
    LED* led = new LED(index);
    leds.push_back(led);
  }
}

void createPushPullAnimations() {
  std::vector<Animation*> sequentialScript;
  for (uint8_t i = 6; i < 11; i++) {
    sequentialScript.push_back(new SolidColorAnimation(leds[i], BLUE, 1));
  }

  progressAnimation = new SequentialAnimation(sequentialScript);
  pushCompleteAnimation = new SolidColorAnimation(leds[10], GREEN, 2);
  pullCompleteAnimation = new SolidColorAnimation(leds[6], GREEN, 2);
}

// Adafruit Neopixel library example function
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<12; i++) {
    ledStrip.setPixelColor(i, c);
    ledStrip.show();
    delay(wait);
  }
}

void setup() {
  Serial.begin(9600);

  swiper.init();
  teamMemberCommitTrigger.init();

  selectableLCD.init(16, 2);
  selectableLCD.setValues(BRANCH_NAMES);

  // LED setup
  ledStrip.setBrightness(BRIGHTNESS);
  ledStrip.begin();
  colorWipe(ledStrip.Color(0, 180, 0), 50);
  colorWipe(ledStrip.Color(0, 0, 200), 50);
  colorWipe(ledStrip.Color(0, 0, 0, 255), 50);

  // initialize LEDs
  initializeLeds(TEAM_LEDS);
  initializeLeds(STATUS_LEDS);

  for (uint8_t i = 0; i < 6; i++) {
    teamCommitAnimations.push_back(new LEDAnimation(leds[i], GREEN, BLUE, 10));
  }

  createPushPullAnimations();
}

void loop() {

  // Non-blocking team led animations
  
  for (Animation* animation : teamCommitAnimations) {
    animation->update();
  }

  // If you change branch, commit lights should clear

  if (selectableLCD.update()) { 
    for (Animation* animation : teamCommitAnimations) {
      animation->reset();
    }
  }

  // Non-blocking team commit led button trigger
  
  teamMemberCommitTrigger.update();

  // If you press button, one commit should light up

  if (teamMemberCommitTrigger.isTriggered()) {
    teamCommitAnimations[random(6)]->start();
  }


  // Non-blocking status led animations 
  
  progressAnimation->update();
  bool actionComplete = swiper.update();
  
  // If you pull, the status leds should execute
  
  pullCompleteAnimation->update();
  
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

  // If you push, status leds should execute
  
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
