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
std::vector<LED*> teamLeds;
std::vector<LED*> statusLeds;
CRGB ledStrip[NUM_LEDS];

//Button
Button teamMemberCommitTrigger(12);

//Animations
std::vector<Animation*> teamCommitAnimations;
Animation* progressAnimation;
Animation* pushCompleteAnimation;
Animation* pullCompleteAnimation;

void initializeLeds(const std::vector<uint8_t>& indexes, std::vector<LED*>& leds) {
  for (uint8_t index : indexes) {
    LED* led = new LED(&ledStrip[index]);
    leds.push_back(led);
  }
}

void createPushPullAnimations() {
  std::vector<Animation*> sequentialScript;
  for (LED* led : statusLeds) {
    sequentialScript.push_back(new SolidColorAnimation(led, BLUE, 1));
  }

  progressAnimation = new SequentialAnimation(sequentialScript);

  pushCompleteAnimation = new SolidColorAnimation(statusLeds.back(), GREEN, 1);
  pullCompleteAnimation = new SolidColorAnimation(statusLeds.front(), GREEN, 1);
}

void setup() {
  Serial.begin(9600);

  swiper.init();
  teamMemberCommitTrigger.init();

  selectableLCD.init(16, 2);
  selectableLCD.setValues(BRANCH_NAMES);

  // LED setup
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(ledStrip, NUM_LEDS);

  // initialize LEDs
  initializeLeds(TEAM_LEDS, teamLeds);
  initializeLeds(STATUS_LEDS, statusLeds);

  for (LED* led : teamLeds) {
    teamCommitAnimations.push_back(new LEDAnimation(led, GREEN, BLUE, 10));
  }

  createPushPullAnimations();
}

void loop() {
  swiper.update();
  selectableLCD.update();

  if (!teamCommitAnimations[0]->isRunning()) {
    teamCommitAnimations[0]->start();
  }

  teamCommitAnimations[0]->update();

  if (teamCommitAnimations[0]->isComplete()) {
    teamCommitAnimations[0]->reset();
  }

  

  // LEDs


  // Triggers
  //

  // Change branch
  /*if (_selectedIndex != index) { If knob index is different
    contributerAnimation->reset();
    }*/

  // Button
  /*button.update();

    if (button.isTriggered()) {
    contributerAnimation->start();
    }

    contributerAnimation->update();

    // Pull
    if (swiper.getPullState() == GestureState::COMPLETE) {
    Serial.println("pull complete");
    // Sequence animation
    if (!statusParallelAnimation->isRunning()) {
      statusParallelAnimation->start();
    }


    // Parallel animation
    // Black
    // Set 11 to Green
    }
    statusParallelAnimation->update();

    if (statusParallelAnimation->isComplete()) {
    statusParallelAnimation->reset();
    }*/

  /*if (!testAnimation->isRunning()) {
    testAnimation->start();
    }

    testAnimation->update();

    if (testAnimation->isComplete()) {
    testAnimation->reset();
    }*/



  // Pull
  /* if(_pullGesture->getState() == GestureState::READY) {
     // Sequence animation reverse
     // Parallel animation
     // Black
     // Set 7 to Green
    }  */
}
