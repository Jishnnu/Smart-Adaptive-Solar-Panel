#include <Servo.h>       


Servo sg90;              
int initial_position = 90; 
int LDR1 = A1;           
int LDR2 = A2;           
int error = 5;           
int servopin = 9; 
const int lm35_pin = A0;   
int temp_adc_val; 
float temp_val; 

 

void setup() { 

  Serial.begin(9600);  
  sg90.attach(servopin);   
  pinMode(LDR1, INPUT);    
  pinMode(LDR2, INPUT); 
  sg90.write(initial_position);    
  delay(1000);  

  temp_adc_val = analogRead(lm35_pin); 
  temp_val = (temp_adc_val * 4.88);  
  temp_val = (temp_val/10); 
  Serial.print("Temperature = "); 
  Serial.print(temp_val); 
  Serial.println(" Degree Celsius"); 
  
  if(temp_val < 20){ 
    Serial.println("As the temperature is low, it's better if you don't put out your clothes to dry. Be careful today as the panel won't pull much juice."); 
    Serial.println("Don't forget to take your umbrella !"); 
  } 

  else{ 
    Serial.println("As the temperature is warm enough, feel free to dry your clothes outside."); 
    Serial.println("Don't forget to wear a sunscreen !"); 
  } 
}
 

void loop() { 

  int R1 = analogRead(LDR1);  
  int R2 = analogRead(LDR2);  
  int diff1= abs(R1 - R2);    
  int diff2= abs(R2 - R1);   

  if((diff1 <= error) || (diff2 <= error)) { 
    //if the difference is under the error then do nothing 
  }    

  else {     
    if(R1 < R2) { 
      initial_position = --initial_position;  //Move the servo towards 0 degree 
    } 

    if(R1 > R2) { 
      initial_position = ++initial_position; //Move the servo towards 180 degree 
    } 

    if(R1 == R2) { 
      initial_position = 90; 
    } 
  }   

  sg90.write(initial_position);  
  delay(100); 
} 