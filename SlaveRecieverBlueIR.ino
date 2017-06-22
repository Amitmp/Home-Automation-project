./* CONNECTIONS
 * SLAVE RECIVER 
 * arduino 10,11,12,13 to relay 1,2,3,4
 * IR 8
 * EN 7
 * gar1 2
 * 2 3
 * bluetooth rx to rx, tx to tx
 * 
 * SDA to SDA, SCL to SCL
 */

 #include <IRremote.h>
#include <Wire.h>
int RECV_PIN = 8;

IRrecv irrecv(RECV_PIN);

decode_results results;

String voice;
void allon(){
     digitalWrite(12, HIGH); 
     digitalWrite(13, HIGH); 
     digitalWrite(10, HIGH); 
     digitalWrite(11, HIGH);  
}
void alloff(){
     digitalWrite(12, LOW); 
     digitalWrite(13, LOW); 
     digitalWrite(10, LOW); 
     digitalWrite(11, LOW);  
}
//-----------------------------------------------------------------------//  
void setup() {

  irrecv.enableIRIn();

  pinMode (2, OUTPUT); 
  pinMode (3, OUTPUT);
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}


//-----------------------------------------------------------------------//  
void loop() {

if (digitalRead(7)==HIGH){
if (irrecv.decode(&results)) {



irrecv.resume();

if (results.value == 0x1FEE01F){ //0 

digitalWrite(13,HIGH);

}else if(results.value == 0x1FE50AF){ //1 

digitalWrite(13,LOW);
}

else if(results.value == 0x1FED827){ //2 

digitalWrite(12,HIGH);
} 
else if(results.value == 0x1FEF807){ //3 

digitalWrite(12,LOW);
}
else if(results.value == 0x1FE30CF){ //4

digitalWrite(11,HIGH);
} 
else if(results.value == 0x1FEB04F){ //5

digitalWrite(11,LOW);
}
else if(results.value == 0x1FE708F){ //6 

digitalWrite(10,HIGH);
} 
else if(results.value == 0x1FE00FF){ //7 

digitalWrite(10,LOW);
}

else if(results.value == 0x1FEF00F){ //8 GARAGE DOOR OPEN

digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(700);digitalWrite(2, HIGH);
} 
else if(results.value == 0x1FE9867){ //9 GARAGE  DOOR CLOSE 

digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
  delay(700);digitalWrite(3, HIGH);
}

}
    
}

else{
  while (Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = Serial.read(); //Conduct a serial read
  if (c == '#') {break;} //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  }  
  if (voice.length() > 0) {
    Serial.println(voice); 
//-----------------------------------------------------------------------//    
  //----------Control Multiple Pins/ LEDs----------//  
       if(voice == "*all on") { allon();}  //Turn Off All Pins (Call Function)
  else if(voice == "*turn off everything"){ alloff();} //Turn On  All Pins (Call Function)
  
  //----------Turn On One-By-One----------// 
  else if(voice == "*living room lights on") { digitalWrite(12, HIGH);} 
  else if(voice == "*fan on") { digitalWrite(13, HIGH);}
  else if(voice == "*dining hall lights on") { digitalWrite(10, HIGH);}
  else if(voice == "*bedroom lights on") { digitalWrite(11, HIGH);}
  else if(voice == "*open garage door") { digitalWrite(3, HIGH); digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(700);digitalWrite(2, HIGH);
  }
 
  //----------Turn Off One-By-One----------// 
  else if(voice == "*living room lights off") { digitalWrite(12, LOW);} 
  else if(voice == "*fan off") { digitalWrite(13, LOW);}
  else if(voice == "*dining hall lights off") { digitalWrite(10, LOW);}
  else if(voice == "*bedroom lights off") { digitalWrite(11, LOW);}
  else if(voice == "*close garage door") { digitalWrite(2, HIGH); digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
  delay(700);digitalWrite(3, HIGH);}
  
  
//-----------------------------------------------------------------------//  
voice="";}} 

}


void receiveEvent(int howMany) {
  while (1 < Wire.available()) { 
    char c = Wire.read(); 
    Serial.print(c);         
  }
  int x = Wire.read();    
  Serial.println(x);

  switch(x){
    case 0:  allon();
          break;
    case 1:  alloff();
          break;
    case 2: digitalWrite(12, HIGH);
          break;
    case 3:digitalWrite(13, HIGH);
          break;
    case 4:digitalWrite(10, HIGH);
          break;
    case 5:digitalWrite(11, HIGH);
          break;
    case 6:digitalWrite(12, LOW);
          break;
    case 7:digitalWrite(13, LOW);
          break;
    case 8:digitalWrite(10, LOW);
           break;
    case 9:digitalWrite(11, LOW);
           break;
           
    }}

    
