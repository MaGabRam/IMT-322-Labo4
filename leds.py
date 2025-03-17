
import RPi.GPIO as GPIO
import time

leds = [23, 13, 6]
GPIO.setmode(GPIO.BCM)
GPIO.setup(leds, GPIO.OUT)

archivo = "texto_proob2.txt"

def read_interval():
    with open(archivo, "r") as file:
        interval = float(file.readline().strip())
        return max(0.1, interval)

while True:
    interval = read_interval()
    for led in leds:
        GPIO.output(led, GPIO.HIGH)
        time.sleep(interval)
        GPIO.output(led, GPIO.LOW)
