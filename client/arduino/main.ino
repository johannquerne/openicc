#include <ArduinoJson.h>

const int delay_loop = 60000; //60000

int ledPin = 13;
String dataReceived = "";
int temperaturePin = 0;
int photosensorPin = 1;

int counter = 0;

float voltage, degreesC, degreesF; // Variables for temperature sensor
int luminosity; // Variable for luminosity sensor

StaticJsonBuffer<200> jsonBuffer;

void setup() {
  pinMode(ledPin, OUTPUT);
  //pinMode(photosensorPin, INPUT);
  Serial.begin(9600);
  Serial.println("Arduino's starting");

  // Get configuration from R-Pi

}

void loop()
{
  receiveAndReadData();
  readAndSendSensors();
  delay(1000);
}


void receiveAndReadData()
{
  if (Serial.available() > 0) {
    // say what you got:
    dataReceived = Serial.readString();
    Serial.print("I received: ");
    //Serial.println(Serial.parseInt());
    Serial.println(dataReceived);

    if(dataReceived == "1")
      digitalWrite(ledPin, HIGH);
    else
      digitalWrite(ledPin, LOW);

  }
}

void readAndSendSensors()
{
  counter++;
  if(counter == 60)
  {
    Serial.println(counter);

    // Get data from all sensors

    JsonObject& root = jsonBuffer.createObject();
    root["unit__"] = "xxx";
    
    /********************** 
     *  
     *  Temperature sensor
     *  
     *********************/
    getTemperature(); // 

    JsonArray& temperatureJSON = root.createNestedArray("temperature");
    temperatureJSON.add(degreesC);
    temperatureJSON.add(degreesF);


    /********************** 
     *  
     *  Luminosity sensor
     *  
     *********************/
    getLuminosity(); // 

    JsonArray& luminosityJSON = root.createNestedArray("luminosity");
    luminosityJSON.add(luminosity);

    // Print final JSON
    root.printTo(Serial);
    Serial.println();
    
    // Clear JSON buffer
    StaticJsonBuffer<200> jsonBuffer;

    // Reset counter
    counter = 0;
  }
}

void getTemperature()
{
  voltage = analogRead(temperaturePin) * 0.004882814;
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0/5.0) + 32.0;
}

void getLuminosity()
{
  luminosity = analogRead(photosensorPin);
}
