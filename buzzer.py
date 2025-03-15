import RPi.GPIO as GPIO
import time

buzzer_pin = 23  
button_pin = 19  
 

def buzzer_on ():
    GPIO.output (buzzer_pin, GPIO.HIGH)

def buzzer_off ():
    GPIO.output(buzzer_pin, GPIO.LOW)

def main():
    GPIO.setwarnings (False)
    GPIO.setmode(GPIO.BCM) 
    GPIO.setup(buzzer_pin, GPIO.OUT)
    GPIO.setup(button_pin, GPIO.IN, pull_up_down = GPIO.PUD_UP)
    print("Presiona el botón")
    
    try:
        while True:
            if GPIO.input(button_pin) == GPIO.LOW:
                print("Button on")
                buzzer_on()
                #time.sleep (0.5)
            else:
                buzzer_off()
                #time.sleep(0.1)  # delay
    except KeyboardInterrupt:
        print("\nSaliendo del programa...")
        GPIO.cleanup()

main()
