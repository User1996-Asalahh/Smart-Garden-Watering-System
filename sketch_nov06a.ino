#include <LiquidCrystal.h>

#define Soil_Moisture_Pin A3 
#define Pump_Pin 8           
#define LED_Pin 9 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int threshold = 400;

bool pumpStatus = false;     
unsigned long lastCheckTime = 0;      
unsigned long lastDisplaySwitchTime = 0;  
const unsigned long checkInterval = 4000;   
const unsigned long displaySwitchInterval = 4000; 
bool showStatus = true;  

void setup() {
  Serial.begin(9600);  
  pinMode(Soil_Moisture_Pin, INPUT);
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

    int moistureLevel = analogRead(Soil_Moisture_Pin);  
    Serial.print("Soil Moisture Level: ");
    Serial.println(moistureLevel);  

    
    if (moistureLevel < threshold && !pumpStatus) {  
      pumpStatus = true;             
      digitalWrite(Pump_Pin, HIGH);  
      digitalWrite(LED_Pin, HIGH);   
      Serial.println("Watering the garden...");
      
    } else if (moistureLevel >= threshold && pumpStatus) {  
      pumpStatus = false;          
      digitalWrite(Pump_Pin, LOW);  
      digitalWrite(LED_Pin, LOW);   
      Serial.println("Soil is adequately wet.");
    }
  }

 
  if (millis() - lastDisplaySwitchTime >= displaySwitchInterval) {
    lastDisplaySwitchTime = millis(); 
    
    int moistureLevel = analogRead(Soil_Moisture_Pin); 
    
    lcd.clear();

    
    if (showStatus) {
      
      lcd.setCursor(0, 0); 
      lcd.print("Moisture-Lev:");
      lcd.print(moistureLevel);
      lcd.setCursor(0, 1);
      lcd.print("Pump turns ");
      lcd.print(pumpStatus ? "ON" : "OFF");
    } else
    {
      
      lcd.setCursor(0, 0);
      if (pumpStatus) {
        lcd.print("Watering the");
        lcd.setCursor(0, 1);
        lcd.print("Garden...");
      } else {
        lcd.print("Soil is");
        lcd.setCursor(0, 1);
        lcd.print("adequately wet.");
      }
    }
    showStatus = !showStatus;
  }  
}
