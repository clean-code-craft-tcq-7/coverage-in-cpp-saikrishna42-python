#include "typewise-alert.h"
#include <stdio.h>
#include<iostream>
#include<map>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

map<int, int> Cooling_Lower_limit { { 0, 0}, { 1,0 },{2,0} };
map<int, int> Cooling_Upper_limit { { 0, 35}, { 1,45 },{2,40}} ;

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = Cooling_Lower_limit[coolingType];
  int upperLimit = Cooling_Upper_limit[coolingType];
  
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

const char* convert_enum_to_string[] = {
    "NORMAL",
    "LOW",
    "HIGH"
    
};

void sendToEmail(BreachType breachType)
 {
  const char* recepient = "a.b@c.com";
  if(breachType==TOO_LOW || breachType==TOO_HIGH)
  {
      printf("To: %s\n", recepient);
      std::cout<<"Hi, the temperature is too "<<convert_enum_to_string[breachType] <<std::endl;
  }
  else{}
      
  }
