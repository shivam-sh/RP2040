// Edifier IR
// Shivam Sharma
// 24/07/2021

#include <Adafruit_NeoPixel.h>
#include <IRLibSendBase.h>
#include <IRLib_P01_NEC.h>
#include <IRLibCombo.h>

#define VOL_UP_PIN 4
#define MUTE_PIN  5
#define VOL_DOWN_PIN 6

Adafruit_NeoPixel pixel(1, 16, NEO_RGB);

IRsend irLED;

int volUp = 0;
int volDown = 0;
int mute = 0;

void setup() {
    pinMode(VOL_UP_PIN, INPUT_PULLDOWN);
    pinMode(VOL_DOWN_PIN, INPUT_PULLDOWN);
    pinMode(MUTE_PIN, INPUT_PULLDOWN);

    pixel.begin();
    pixel.show();
    pixel.setBrightness(50);

    attachInterrupt(digitalPinToInterrupt(VOL_UP_PIN), volUpISR, RISING);
    attachInterrupt(digitalPinToInterrupt(VOL_DOWN_PIN), volDownISR, RISING);
    attachInterrupt(digitalPinToInterrupt(MUTE_PIN), muteISR, RISING);
}

void loop() {
    if (volUp > 0) {
        volUp--;
    }

    if (volDown > 0) {
        volDown--;
    }

    if (volUp > 0) {
        mute--;
    }
    
    if (volUp > 0 && mute > 0 && volDown > 0) {
        pixel.setPixelColor(0, pixel.gamma32(pixel.Color(volUp, volDown, mute)));
        delay(10);
    }
}

void volUpISR() {
    if (volUp < 80) {
        irLED.send(NEC, 0x8E73CC3, 0);
        volUp = 100;
    }
}

void volDownISR() {
    if (volDown < 80) {
        irLED.send(NEC, 0x8E7B24D, 0);
        volDown = 100;
    }
}

void muteISR() {
    if (mute < 80) {
        irLED.send(NEC, 0x8E7D42B, 0);
        mute = 100;
    }
}