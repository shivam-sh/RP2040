#include "pico/stdlib.h"

int main(int argc, char const *argv[]) {
    const uint LED = 13;
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    while (true) {
        gpio_put(LED, 0);
        sleep_ms(500);
        gpio_put(LED, 1);
        sleep_ms(500);
    }
}
