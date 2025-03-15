import RPi.GPIO as GPIO
import time

buzzer_pin = 23  
button1_pin = 19  
button2_pin = 24 
 

def buzzer_on ():
    GPIO.output (buzzer_pin, GPIO.HIGH)

def buzzer_off ():
    GPIO.output(buzzer_pin, GPIO.LOW)

def main():
    GPIO.setwarnings (False)
    GPIO.setmode(GPIO.BCM) 
    GPIO.setup(buzzer_pin, GPIO.OUT)
    GPIO.setup(button1_pin, GPIO.IN, pull_up_down = GPIO.PUD_UP)
    GPIO.setup(button2_pin, GPIO.IN, pull_up_down = GPIO.PUD_UP)
    print("Presiona el botón 1 para activar el buzzer y el 2 para desactivarlo")
    
    try:
        while True:
            if GPIO.input(button1_pin) == GPIO.LOW:
                print("Button 1 on")
                buzzer_on()
                #time.sleep (0.5)
            if GPIO.input(button2_pin) == GPIO.LOW:
                print("Button 2 on")
                buzzer_off()
                #time.sleep (0.5)
    except KeyboardInterrupt:
        print("\nSaliendo del programa...")
        GPIO.cleanup()

main()
