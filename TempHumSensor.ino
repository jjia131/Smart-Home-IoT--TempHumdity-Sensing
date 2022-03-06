// Include the libraries:
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wlkata_Mega_Sensor_Shield.h>

// Set DHT pin:
#define DHTPIN 11

// Set DHT type
#define DHTTYPE DHT11   // DHT 11 

// Initialize DHT sensor for normal 16mhz Arduino:
DHT dht = DHT(DHTPIN, DHTTYPE);


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int TRYTIME = 1;

void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);

  // Setup sensor:
  dht.begin();

  pinMode(4,OUTPUT); //Red
  pinMode(5,OUTPUT); //Blue
}

void loop() {
  // Wait a few seconds between measurements:
  delay(5000);

  // Read the humidity in %:
  float h = dht.readHumidity();
  // Read the temperature as Celsius:
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again):
  if (isnan(h) || isnan(t)) { //Check if NAN
    Serial.print("Attempt: ");
    Serial.println(TRYTIME);
    if(TRYTIME > 3){
      Serial.println("Exit");
      exit(0);
    }
    Serial.println("Failed to read from DHT sensor!");
    return;
    TRYTIME = TRYTIME + 1;
  }
  
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" \xC2\xB0"); //DEGREE SIGN
  Serial.println("C | ");

  if(t>=25){ //RED
    Serial.println("TEMP greater than 25 degrees");
    digitalWrite(4,HIGH); //Turn on 
    delay(1000);
    digitalWrite(4,LOW); //Turn OFF
    delay(1000);

    display.println("TEMP greater than 25");
    display.display();
    for(int i = 0; i <3;i++){ //Buzzer Warning
      shieldBuzzer(ON);
      delay(200);
      shieldBuzzer(OFF);
    }                 
  }
  if(h>=90){ //BLUE
    Serial.println("HUM greater than 90");
    digitalWrite(5,HIGH); //Turn on 
    delay(1000);
    digitalWrite(5,LOW); //Turn OFF
    delay(1000);

    display.println("HUM greater than 90");
    display.display();
    for(int i = 0; i <3;i++){ //Buzzer Warning
      shieldBuzzer(ON);
      delay(200);
      shieldBuzzer(OFF);
    }    
  }
}
