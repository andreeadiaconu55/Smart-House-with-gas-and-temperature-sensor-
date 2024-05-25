#include <Wire.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define DHTTYPE DHT11
#define dhtpin 13
#define gas_detector A1
#define LEDPIN_t 2
#define LEDPIN_g 3
#define buton_plus 6
#define buton_minus 5
#define emergency 7
#define buzzer 8

Servo myservo;
int angle=0;
int open=0;
float high_gas_lvl=450;
float high_temp_lvl=27;
DHT temp(dhtpin,DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define PWM 12 // Motor B PWM Speed

#define DIR 11 // Motor B Direction

// the actual values ​​for "fast" and "slow" depend on the motor

#define PWM_SLOW 0 // arbitrary slow speed PWM duty cycle

#define PWM_FAST 200 // arbitrary fast speed PWM duty cycle

#define DIR_DELAY 1000 // brief delay for abrupt motor changes

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  myservo.attach(9);
  myservo.write(0);
  Serial.begin(9600);
  pinMode( DIR, OUTPUT );

  pinMode( PWM, OUTPUT );

  digitalWrite( DIR, LOW );

  digitalWrite( PWM, LOW );
  //Serial.println("DHTxx test!");

  temp.begin();
  //pinMode(buzzer,  OUTPUT);
  pinMode(gas_detector, INPUT);
  pinMode(buton_plus,INPUT_PULLUP);
  pinMode(buton_minus,INPUT_PULLUP);
  pinMode(emergency,INPUT_PULLUP);
  

}
void loop() {

  if(digitalRead(buton_plus)==LOW)
      {
        high_temp_lvl=high_temp_lvl+0.5;
        //Serial.println("merge");
      }
        
  if(digitalRead(buton_minus)==LOW)
      high_temp_lvl=high_temp_lvl-0.5;
  lcd.setCursor(11,0);
  lcd.print(high_temp_lvl);
  if(digitalRead(emergency)==HIGH)
    {
      for (int angle = 0; angle <= 180; angle += 10) {
        myservo.write(angle);
        delay(100);
        open=1;
        Serial.println("BUTON");
      }
      delay(500);
    }
      
  float t = temp.readTemperature();
  float g=analogRead(gas_detector);
    Serial.println(t);
    Serial.println(g);
    Serial.println(high_temp_lvl);
    delay(1500);
  if(isnan(t)){
    Serial.println("Fail");
    return;
  }
  if(t>high_temp_lvl) 
  {
    digitalWrite(LEDPIN_t, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Hot :");
    lcd.print(t);
    lcd.print(">");
    lcd.print(high_temp_lvl);
  }
  else 
  {
    digitalWrite(LEDPIN_t, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Cold:");
    lcd.print(t);
    lcd.print("<");
    lcd.print(high_temp_lvl);
  }


  
  if (g > high_gas_lvl) {
      tone(buzzer,880);
    // Rotate 180 degrees
      lcd.setCursor(0, 1);
      lcd.print("gas level: high! ");
      digitalWrite(LEDPIN_g, HIGH);
    if(open==0)
     { for (int angle = 0; angle <= 180; angle += 10) {
        myservo.write(angle);
        delay(100);
        open=1;
      }
      delay(500);
      noTone(buzzer);

     }
  }
    //delay(10000); // Wait for 1 minute (60,000 milliseconds)
    else 
        { noTone(buzzer);
          if( g < high_gas_lvl )
          {   digitalWrite(LEDPIN_g,LOW);
              lcd.setCursor(0, 1);
              lcd.print("gas level: safe");
            // Rotate back to initial position
            if(open==1)
              for (int angle = 180; angle >= 0; angle -= 10)
              {
                myservo.write(angle);
                delay(15);
                open=0;
              }   
          
          if(t>high_temp_lvl)
          {
            delay( DIR_DELAY );
            digitalWrite( DIR, HIGH );
            analogWrite(PWM, 255-PWM_FAST );
          }
          else
          {
            digitalWrite(DIR, LOW );
            digitalWrite(PWM, LOW );
          }
        }
        }
        delay(500);

}
