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

const Color GREEN = {255, 255, 200};
const Color BLUE = {180, 255, 200};
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
Animation* pushAnimation;

void initializeLeds(const std::vector<uint8_t>& indexes) {
  for (uint8_t index : indexes) {
    LED* led = new LED(index, ledStrip);
    leds.push_back(led);
  }
}

void createPushAnimation() {
  std::vector<Animation*> pushAnimationScript;
  std::vector<Animation*> sequentialScript;
  //for (uint8_t index : STATUS_LEDS) {
    sequentialScript.push_back(new LEDAnimation(leds[0], BLUE, BLUE, 1000));
    sequentialScript.push_back(new LEDAnimation(leds[1], BLUE, BLUE, 1000));
  //}
  //pushAnimationScript.push_back(new SequentialAnimation(sequentialScript));

  /*std::vector<Animation*> parallelScript;
  for (uint8_t index : STATUS_LEDS) {
    parallelScript.push_back(new LEDAnimation(leds[index], BLACK, BLACK, 1000));
  }
  pushAnimationScript.push_back(new ParallelAnimation(parallelScript));
  pushAnimationScript.push_back(new LEDAnimation(leds.back(), GREEN, GREEN, 5000));*/
  pushAnimation = new SequentialAnimation(sequentialScript);
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
  initializeLeds(STATUS_LEDS);
  initializeLeds(TEAM_LEDS);

  for (uint8_t index : TEAM_LEDS) {
    teamCommitAnimations.push_back(new LEDAnimation(leds[index], GREEN, BLUE, 10000));
  }

  createPushAnimation();


  //animationScript.push_back(new LEDAnimation(led, {20, 255, 150}, {123, 255, 100}, 2000));

  /*statusParallelAnimation = new ParallelAnimation(animationScript);

    LED* led = new LED(teamLeds[3]);
    contributerAnimation = new LEDAnimation(led, {255, 255, 200}, {180, 255, 80}, 20000);


    std::vector<Animation*> script;

    script.push_back(new LEDAnimation(ledStrip[0], {20, 255, 150}, {123, 255, 100}, 2000));
    script.push_back(new LEDAnimation(ledStrip[1], {20, 255, 150}, {123, 255, 100}, 2000));

    std::vector<Animation*> parallelScript;
    parallelScript.push_back(new LEDAnimation(ledStrip[0], {20, 255, 150}, {123, 255, 100}, 2000));
    parallelScript.push_back(new LEDAnimation(ledStrip[1], {20, 255, 150}, {123, 255, 100}, 2000));

    script.push_back(new ParallelAnimation(parallelScript));

    testAnimation = new SequentialAnimation(script);*/

}



void loop() {
  swiper.update();
  selectableLCD.update();



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
