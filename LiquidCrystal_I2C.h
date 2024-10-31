#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define Soil_Moisture_pin A0 
#define Pump_Pin 9           
#define LED_Pin 7             

int threshold = 400;          
bool pumpStatus = false;     
unsigned long lastCheckTime = 0;      
const unsigned long checkInterval = 6000;   
const unsigned long messageDuration = 4000; 

void setup() {
  Serial.begin(9600);  
  pinMode(Soil_Moisture_pin, INPUT);
  pinMode(Pump_Pin, OUTPUT);
  pinMode(LED_Pin, OUTPUT);
  digitalWrite(Pump_Pin, LOW);  
  digitalWrite(LED_Pin, LOW);   
  
  
  lcd.begin(16, 2);  
  lcd.setCursor(0, 0);
  lcd.print("Smart Garden");    
  lcd.setCursor(0, 1);
  lcd.print("Watering System");
  delay(4000);                   
  lcd.clear();                  
}

void loop() {
  
  if (millis() - lastCheckTime >= checkInterval) {
    lastCheckTime = millis(); 

    int moistureLevel = analogRead(Soil_Moisture_pin);  
    Serial.print("Soil Moisture Level: ");
    Serial.println(moistureLevel);  

    if (moistureLevel < threshold && !pumpStatus) {  
      pumpStatus = true;             
      digitalWrite(Pump_Pin, HIGH);  
      digitalWrite(LED_Pin, HIGH);   
      Serial.println("Watering the garden...");

      
      lcd.setCursor(0, 0);
      lcd.print("Watering the    ");
      lcd.setCursor(0, 1);
      lcd.print("Garden...       ");
      delay(messageDuration);  

    
      lcd.setCursor(0, 0); 
      lcd.print("Moisture: ");
      lcd.print(moistureLevel);
      lcd.print("   ");
      lcd.setCursor(0, 1);
      lcd.print("Pump: ON        ");
      
    } else if (moistureLevel >= threshold && pumpStatus) {  
      pumpStatus = false;          
      digitalWrite(Pump_Pin, LOW);  
      digitalWrite(LED_Pin, LOW);   
      Serial.println("Soil is sufficiently wet.");
      
      
      lcd.setCursor(0, 0);
      lcd.print("Soil is        ");
      lcd.setCursor(0, 1);
      lcd.print("sufficiently wet");
      delay(messageDuration);  

      
      lcd.setCursor(0, 0); 
      lcd.print("Moisture: ");
      lcd.print(moistureLevel);
      lcd.print("   ");
      lcd.setCursor(0, 1);
      lcd.print("Pump: OFF       ");
    }
  }
}
