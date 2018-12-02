#include "SelectableLCD.h"
#include "Button.h"

//
// INCLUDES
//
const std::vector<String> branchNames = {"design/headersidebar", "design/challenges", "dev/npm", "kf/home_news"};
SelectableLCD* selectableLCD;

// LCD


// LED
#include "LEDAnimation.h"
#include "Swiper.h"
Swiper swiper(3);

// LEDs
const std::vector<uint8_t> teamLeds = {1, 2, 3, 4, 5, 6};

Animation* contributerAnimation;

const std::vector<uint8_t> statusLeds = {7, 8, 9, 10, 11};

std::vector<LED*> ledStrip;
std::vector<Animation*> animationScript;
Animation* statusParallelAnimation;

// Button
uint32_t buttonState = 0;

//
// ARDUINO
//

SequentialAnimation* testAnimation;

void setup() {
  Serial.begin(9600);

  // LCD pot
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  // Prototype Button
  pinMode(12, INPUT);

  // LCD setup
  selectableLCD = new SelectableLCD(2);
  selectableLCD->setValues(branchNames);

  // LED setup
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // Contributer LEDs
  //LED* contributer = new LED(contributerLed);

  // Status LEDs
  for (uint32_t statusLed : statusLeds) {
    LED* led = new LED(statusLed);
    ledStrip.push_back(led);

    //animationScript.push_back(new LEDAnimation(led, {20, 255, 150}, {123, 255, 100}, 2000));
  }

  /*statusParallelAnimation = new ParallelAnimation(animationScript);

  LED* led = new LED(teamLeds[3]);
  contributerAnimation = new LEDAnimation(led, {255, 255, 200}, {180, 255, 80}, 20000);*/


  std::vector<Animation*> script;

  script.push_back(new LEDAnimation(ledStrip[0], {20, 255, 0}, {20, 255, 150}, 500));
  script.push_back(new LEDAnimation(ledStrip[1], {20, 255, 0}, {20, 255, 150}, 500));

  std::vector<Animation*> parallelScript;
  parallelScript.push_back(new LEDAnimation(ledStrip[0], {20, 255, 150}, {123, 255, 100}, 2000));
  parallelScript.push_back(new LEDAnimation(ledStrip[1], {20, 255, 150}, {123, 255, 100}, 2000));

  script.push_back(new ParallelAnimation(parallelScript));

  testAnimation = new SequentialAnimation(script);

}

Button button(12);

void loop() {
  // Soft Pot push and pull
  swiper.update();

  // Knob + LCD
  selectableLCD->update();

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

  if (!testAnimation->isRunning()) {
    testAnimation->start();
  }

  testAnimation->update();

  if (testAnimation->isComplete()) {
    testAnimation->reset();
  }



  // Pull
  /* if(_pullGesture->getState() == GestureState::READY) {
     // Sequence animation reverse
     // Parallel animation
     // Black
     // Set 7 to Green
    }  */
}
