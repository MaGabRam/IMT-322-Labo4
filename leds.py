
import RPi.GPIO as GPIO
import time
leds = [23, 13, 6]
GPIO.setmode(GPIO.BCM)
GPIO.setup(leds, GPIO.OUT)
GPIO.setwarnings(False)
archivo = "texto_proob2.txt"

def read_interval():
    with open(archivo, "r") as file: # se cierre o no el archivo, se quedara con el ultimo numero que se ponga en el texto, por lo que se lo tomara en cuenta
        interval = float(file.readline().strip()) #primera linea del archivo
        return max(0.1, interval) #para que no sea tan pequena el tiempo de intervalo, igual se va a 0.1

try:
    while True:
        interval = read_interval()
        for led in leds:
            GPIO.output(led, GPIO.HIGH)
            time.sleep(interval)
            GPIO.output(led, GPIO.LOW)
except KeyboardInterrupt:
    print("\nSaliendo del programa...")
    GPIO.cleanup()
