#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hello.pio.h"

int main(int argc, char const *argv[]) { PIO pio = pio0;

    uint offset = pio_add_program(pio, &hello_program);

    uint sm = pio_claim_unused_sm(pio, true);
    hello_program_init(pio, sm, offset, 13);

    while (true) {
        pio_sm_put_blocking(pio, sm, 1);
        sleep_ms(500);
        pio_sm_put_blocking(pio, sm, 0);
        sleep_ms(500);
    }
}
