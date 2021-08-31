# PIO Experiments
# Shivam Sharma
# 25/07/2021

from machine import Pin
import rp2
import time

@rp2.asm_pio(set_init=rp2.PIO.OUT_LOW)
def blink():
    set(pins, 1)
    set(x, 63)              [15]
    label('stay-high')
    nop()                   [29]
    jmp(x_dec, 'stay-high')

    set(pins, 0)
    set(x, 63)              [15]
    label('stay-low')
    nop()                   [29]
    jmp(x_dec, 'stay-low')

sm = rp2.StateMachine(0, blink, freq=2000, set_base=Pin(13))


sm.active(1)
time.sleep(60)
sm.active(0)