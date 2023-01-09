#include "typewise-alert.h"
#include <stdio.h>
#include<iostream>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

int coolingType_limit( CoolingType coolingType,int PASSIVE_COOLING_limit,int HI_ACTIVE_COOLING_limit,int MED_ACTIVE_COOLING_limit)
{
   
    switch(coolingType) {
    case PASSIVE_COOLING:
      return PASSIVE_COOLING_limit;
      
    case HI_ACTIVE_COOLING:
      return HI_ACTIVE_COOLING_limit;
    
    case MED_ACTIVE_COOLING:
      return MED_ACTIVE_COOLING_limit;
    
    }
 
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = coolingType_limit(coolingType,0,0,0);
  int upperLimit = coolingType_limit(coolingType,35,45,40);
  
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
