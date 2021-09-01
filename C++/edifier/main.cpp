#include "pico/stdlib.h"

const uint VOL_UP_GPIO = 12;
const uint MUTE_GPIO = 11;
const uint VOL_DOWN_GPIO = 10;

volatile bool vol_up = false;
volatile bool mute = false;
volatile bool vol_down = false;

void irq_handler(uint gpio, uint32_t events) {
    // Track the pin states during the interrupt
    vol_up = gpio_get(VOL_UP_GPIO);
    mute = gpio_get(MUTE_GPIO);
    vol_down = gpio_get(VOL_DOWN_GPIO);
}

int main() {
    // Temporary LED for debugging
    const uint LED = 13;
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    // Initialize GPIO
    gpio_init(VOL_UP_GPIO);
    gpio_init(VOL_DOWN_GPIO);
    gpio_init(MUTE_GPIO);

    // Set GPIO direction
    gpio_set_dir(VOL_UP_GPIO, GPIO_IN);
    gpio_set_dir(VOL_DOWN_GPIO, GPIO_IN);
    gpio_set_dir(MUTE_GPIO, GPIO_IN);

    // Set GPIO interrupts on change
    gpio_set_irq_enabled_with_callback(VOL_UP_GPIO, 0b1100, true, irq_handler);
    gpio_set_irq_enabled_with_callback(MUTE_GPIO, 0b1100, true, irq_handler);
    gpio_set_irq_enabled_with_callback(VOL_DOWN_GPIO, 0b1100, true, irq_handler);

    // Main loop
    while (true) {
        // Flash patterns to show current button states
        if (vol_up) {
            gpio_put(LED, 1);
            sleep_ms(50);
            gpio_put(LED, 0);
            sleep_ms(50);
        } else if (mute) {
            gpio_put(LED, 1);
            sleep_ms(100);
            gpio_put(LED, 0);
            sleep_ms(100);
        } else if (vol_down) {
            gpio_put(LED, 1);
            sleep_ms(500);
            gpio_put(LED, 0);
            sleep_ms(500);
        } else {
            gpio_put(LED, 0);
        }
    }
}