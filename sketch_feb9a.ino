#include <WiFi.h> 
//WiFi.h is a core Arduino library for configuring and managing wifi connections for the boards.

#include <ThingESP.h>
//This is a custom library used for this particular project.

#include <DHT.h>
//This is the library used for configuring and handling the DHT sensor used in this project.

#define DHTPIN 5 
//Pin where the DHT11 sensor is connected.

#define DHTTYPE DHT11
//Specifies the type of DHT sensor used in this project which is DHT11.

DHT dht(DHTPIN, DHTTYPE);
//Instantiation of the DHT class with specified pin and type.

ThingESP32 thing("Rishabh", "temphumidity", "nodemcu");
//Instantiation of the ThingESP32 class.

unsigned long previousMillis = 0;
//Time tracker since the last data update.

const long INTERVAL = 6000;  
//Time interval for the updation of the data since the last update.

void setup()
{
  Serial.begin(115200);
  //This initialises a serial communication with a baud rate of 115200 between computer and the board. 

  thing.SetWiFi("Rishabh", "Rishabh");
  //This method from the ThingESP library is used to set up the wifi connection with our board.

  thing.initDevice();
  

}


String HandleResponse(String query)
{

 float h = dht.readHumidity();
  // Reads the humidity around the sensor.

  float t = dht.readTemperature();
  // Reads temperature as Celsius which is the deafult unit for temperature here.

  float f = dht.readTemperature(true);
  // Reads temperature as Fahrenheit when isFahrenheit is true.
  
  Serial.println("Temperature :");
  Serial.print(t);
  //Display the temperature value in celcius.

  Serial.println("Humidity");
  Serial.print(h);
  //Display the humidity level in terms of percentage.

  String humid = "Humidity: " + String(h) + " % \n";
  //Description of the humidity level value.

  String temp = "Temperature: " + String(t) + "°C, " + String(f) + "°F \n";
  //Description of the temperature value in Celcius and the conversion formula for the fahrenheit temperature value.

  
  if (query == "temperature") {
   
    return temp;
  }
  //When the user gives the prompt "temperature" the bot would give the temperature around the sensor in both celcius and fahrenheit.

  else if (query == "humidity") {
  
    return humid;
  }
  //When the user gives the prompt "humidity" the bot would give the humidity levels around the sensor in terms of percentage.
 
  else return "Your query was invalid..";
  //In case of any other prompts, the bot would declare the request as invalid.

}


void loop()
{ 

  thing.Handle();

}