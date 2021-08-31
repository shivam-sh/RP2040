# Edifier IR
# Shivam Sharma
# 24/07/2021

from machine import Pin
from ir_tx.nec import NEC
import utime

volUpPin = Pin(18, Pin.IN, Pin.PULL_DOWN)
volDownPin = Pin(19, Pin.IN, Pin.PULL_DOWN)
mutePin = Pin(20, Pin.IN, Pin.PULL_DOWN)

timer = 0

def SendVolUp(self):
        NEC(Pin(13, Pin.OUT, value = 0)).transmit(0xe710, 0x3c)
        print("Volume up")

def SendVolDown(self):
        NEC(Pin(13, Pin.OUT, value = 0)).transmit(0xe710, 0x4d)
        print("Volume down")

def SendMute(self):
        NEC(Pin(13, Pin.OUT, value = 0)).transmit(0xe710, 0x2b)
        print("Mute")

volUpPin.irq(trigger=Pin.IRQ_RISING, handler=SendVolUp)
volDownPin.irq(trigger=Pin.IRQ_RISING, handler=SendVolDown)
mutePin.irq(trigger=Pin.IRQ_RISING, handler=SendMute)

SendVolUp(0)
# utime.sleep(1)
# SendVolDown(0)
# utime.sleep(1)
# SendMute(0)

# led = Pin(13, Pin.OUT, value = 0)

# while True:
#     timer += 1

#     if timer % 5 == 0:
#         led.toggle()

#     utime.sleep(0.1)

#   e710    3c
#   e710    4d
#   e710    2b