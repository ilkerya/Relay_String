

#include "Variables.h"
// Create a new String object to be split
//String input = "Relay1,  17.34,   Temperature1,  22.18,Relay2,  1.8,   Current,  4.4";
String input = "Relay1,  20.34,   Temperature1,  21.18,Relay2,  4.0,   Current,  4.4";
// Declare the variables of the parts of the String
String RLlVal;
String RL2Val;


float RL1Min, RL1Max, RL2Min,RL2Max;
bool RELAY1 , RELAY2;
float CompValue;
float CurrentAD = 0.95;
//float Temp_si072_1 = 24.67;

void Parse_FileString(){
  String Relay1str, RlStr2, RlStr4;
  String Relay2str, RlStr6,  RlStr8;
  int DelimCount=0;
  int j = 0;
  for (int i = 0; i < input.length(); i++) {
    if (input.substring(i, i+1) == ",") {
      switch(DelimCount){
        case 0:Relay1str = input.substring(j, i);
        break;
        case 1:RlStr2 = input.substring(j,i);
        break;
        case 2:RLlVal = input.substring(j,i);
        break;
        case 3:RlStr4 = input.substring(j,i);
        break;
        case 4:Relay2str = input.substring(j,i);
        break;
        case 5:RlStr6 = input.substring(j,i);
        break; 
        case 6:RL2Val = input.substring(j,i);
             j = i+1;
             RlStr8 = input.substring(j);
        break; 
        default:
        break;   
      }
      j = i+1;
      DelimCount++;
    }
  }
  Relay1str.trim();//remove leadig & last space characters
  RlStr2.trim();
  RLlVal.trim();
  RlStr4.trim();
  Relay2str.trim();
  RlStr6.trim();
  RL2Val.trim();
  RlStr8.trim();

  RL1Min =RlStr2.toFloat();
  RL1Max= RlStr4.toFloat(); 
  RL2Min= RlStr6.toFloat();
  RL2Max= RlStr8.toFloat();



    Serial.println("'''''''''''''''''");
    Serial.println(Relay1str);
  Serial.println(RlStr2);
  Serial.println(RLlVal);
  Serial.println(RlStr4);
  Serial.println(Relay2str);
  Serial.println(RlStr6);
  Serial.println(RL2Val);
  Serial.println(RlStr8);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start");

 Parse_FileString();


}

#define Relay1_Val 8
#define Relay2_Val 4

float GetValue(byte Relay){
  String Val = "";
  if(Relay == Relay1_Val) Val =  RLlVal;
  if(Relay == Relay2_Val) Val =  RL2Val;
  if(Val == "Temperature1")return Values.TemperatureSi072_Ch1;
  if(Val == "Temperature2")return Values.TemperatureSi072_Ch2;
  if(Val == "Temperature3")return  Values.TemperatureSi072_Ch3;
  if(Val == "Humidity1")return Values.Humidity_Ch1;
  if(Val == "Humidity2")return  Values.Humidity_Ch2;
  if(Val == "Humidity3")return  Values.Humidity_Ch3;
  if(Val == "PM2.5")return  Values.PM25;
  if(Val == "PM10")return  Values.PM10;
  if(Val == "Current") return  CurrentAD;
  return 0;
}

void loop() {
  Parse_FileString();
  CompValue = GetValue(Relay1_Val);
  if((CompValue < RL1Min)&& (RELAY1 == 1)) RELAY1 = 0;
  if((CompValue > RL1Max)&& (RELAY1 == 0)) RELAY1 = 1;

   // put your main code here, to run repeatedly:
  Serial.print("RL1Min: ");Serial.println(RL1Min);
  Serial.print(RLlVal+":  ");Serial.print(CompValue); 
  Serial.print("     RELAY1: ");Serial.println(RELAY1); 
  Serial.print("RL1Max: ");Serial.println(RL1Max); 

  CompValue = GetValue(Relay2_Val);
  if((CompValue < RL2Min)&& RELAY2) RELAY2 = 0;
  if((CompValue > RL2Max)&& !RELAY2) RELAY2 = 1; 
  
  Serial.print("RL2Min: ");Serial.println(RL2Min);
  Serial.print(RL2Val+":  ");Serial.print(CompValue);
  Serial.print("      RELAY2: ");Serial.println(RELAY2);
  Serial.print("RL2Max: ");Serial.println(RL2Max); 


    CurrentAD += 0.2;
    Values.TemperatureSi072_Ch1 -= 0.35;

    if( CurrentAD > 6.00) CurrentAD = 0.1;
     if( Values.TemperatureSi072_Ch1 < 13.00) Values.TemperatureSi072_Ch1 = 27.3;  

  delay(2000);
}
