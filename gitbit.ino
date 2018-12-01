#include "SelectableLCD.h"

//
// INCLUDES
//
const std::vector<String> branchNames = {"design/headersidebar", "design/challenges", "dev/npm", "kf/home_news"};
SelectableLCD* selectableLCD;

// LCD


// LED
#include "LEDAnimation.h"
#include "Swiper.h"

// LEDs
const std::vector<uint32_t> statusLeds = {3, 4, 5, 6, 7};
Swiper swiper(3);

std::vector<LED*> ledStrip;
std::vector<Animation*> animationScript;
Animation* animation;

//
// ARDUINO
//

void setup() {
  Serial.begin(9600);
  
  // LCD pot
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  selectableLCD = new SelectableLCD(2);
  selectableLCD->setValues(branchNames);

  for(uint32_t statusLed : statusLeds) {
    LED* led = new LED(statusLed);
    ledStrip.push_back(led);

    animationScript.push_back(new LEDAnimation(led, {255,255,200}, {180, 255, 20}, 2000));
  }

  animation = new ParallelAnimation(animationScript);
  
}

void loop() {
//  lcdBranchChange(); // todo: change this to lcd.update();
  swiper.update();
  selectableLCD->update();

  if(!animation->isRunning()) {
    animation->start();
  }

  animation->update();

  if(animation->isComplete()) {
    animation->reset();
  }
}
