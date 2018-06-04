import serial #Serial imported for Serial communication
import time #Required to use delay functions
 
ArduinoSerial = serial.Serial('/dev/ttyACM0',9600) #Create Serial port object called arduinoSerialData
time.sleep(2) #wait for 2 secounds for the communication to get established

print (ArduinoSerial.readline()) #read the serial data and print it as line

while True: #Do this forever
    
    print (ArduinoSerial.readline())
