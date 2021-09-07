#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/pwm.h"

const uint VOL_UP_GPIO = 12;
const uint MUTE_GPIO = 11;
const uint VOL_DOWN_GPIO = 10;

volatile bool vol_up = false;
volatile bool mute = false;
volatile bool vol_down = false;

void irq_handler(uint gpio, uint32_t events);
void ir_send(uint16_t address, uint8_t data, uint pin);

void send_vol_up();
void send_mute();
void send_vol_down();

int main() {
    const uint IR = 27;
    gpio_init(IR);
    gpio_set_dir(IR, GPIO_OUT);

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

    // Set PWM pin
    gpio_set_function(28, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(28);

    // PWM at 38 KHz with 50% duty cycle
    pwm_set_wrap(slice_num, 999);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 499);
    pwm_set_clkdiv(slice_num, 3.28947);
    pwm_set_enabled(slice_num, true);

    gpio_init(13);
    gpio_set_dir(13, GPIO_OUT);

    // Main loop
    while (true) {
        if (vol_up) {
            multicore_reset_core1();
            multicore_launch_core1(send_vol_up);
            sleep_ms(200);
        } else if (mute) {
            multicore_reset_core1();
            multicore_launch_core1(send_mute);
            sleep_ms(1000);
        } else if (vol_down) {
            multicore_reset_core1();
            multicore_launch_core1(send_vol_down);
            sleep_ms(200);
        }
    }
}

void irq_handler(uint gpio, uint32_t events) {
    // Track and update the pin states during the interrupt
    vol_up = gpio_get(VOL_UP_GPIO);
    mute = gpio_get(MUTE_GPIO);
    vol_down = gpio_get(VOL_DOWN_GPIO);
}

void send_vol_up() {
    ir_send(0xe710, 0x3c, 27);
    while(true) {
        sleep_ms(10);
    }
}

void send_mute() {
    ir_send(0xe710, 0x2b, 27);
    while(true) {
        sleep_ms(10);
    }
}

void send_vol_down() {
    ir_send(0xe710, 0x4d, 27);
    while(true) {
        sleep_ms(10);
    }
}

void ir_send(uint16_t address, uint8_t data, uint pin) {
    bool buffer[32] = {0};
    float base = 562.5;

    for (uint i = 0; i < 16; ++i) {
        buffer[i] = (address >> i) & 0x1;
    }

    for (uint i = 16; i < 24; ++i) {
        buffer[i] = (data >> (i - 16)) & 0x1;
    }

    for (uint i = 24; i < 32; ++i) {
        buffer[i] = ~(data >> (i - 24)) & 0x1;
    }

    gpio_put(pin, true);
    sleep_us(base * 16);
    gpio_put(pin, false);
    sleep_us(base * 8);

    for (uint i = 0; i < 32; ++i) {
        switch (buffer[i]) {
        case 0:
            gpio_put(pin, true);
            sleep_us(base);
            gpio_put(pin, false);
            sleep_us(base);
            break;
        case 1:
            gpio_put(pin, true);
            sleep_us(base);
            gpio_put(pin, false);
            sleep_us(base * 3);
            break;
        }
    }

    gpio_put(pin, true);
    sleep_us(base);
    gpio_put(pin, false);
}
