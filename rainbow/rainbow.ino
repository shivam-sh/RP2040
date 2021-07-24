// RP2040 Rainbow
// Shivam Sharma
// 24/07/2021

#include <Adafruit_NeoPixel.h>
#include <rp2040_pio.h>

#define NEOPIXEL_PIN 16

Adafruit_NeoPixel pixel(1, NEOPIXEL_PIN, NEO_RGB);

void setup() {
    pixel.begin();
    pixel.show();
    pixel.setBrightness(100);
}

void loop() {
    rainbow(50);
}

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<pixel.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / pixel.numPixels());
      pixel.setPixelColor(i, pixel.gamma32(pixel.ColorHSV(pixelHue)));
    }
    pixel.show();
    delay(wait);
  }
}