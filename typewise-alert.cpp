#include "typewise-alert.h"




BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

map<CoolingType,Limit> CoolingInfo = {{PASSIVE_COOLING,{0,35}},{MED_ACTIVE_COOLING,{0,40}},{HI_ACTIVE_COOLING,{0,45}}};
BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = CoolingInfo[coolingType].lowerlimit;
  int upperLimit = CoolingInfo[coolingType].upperlimit;
  
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
  std::cout<< std::hex << header<<" : ";
  std::cout<< std::hex << breachType<<std::endl;
//  printf("%x : %x\n", header, breachType);
}


map<BreachType,string> AlertInfo = {{TOO_LOW," Hi, the temperature is too  Low"},
                                      {TOO_HIGH," Hi, the temperature is too  High"},
                                      {NORMAL,""}};
void sendToEmail(BreachType breachType)
 {
  const char* recepient = "a.b@c.com";
  if(breachType!=NORMAL)
  {
      //printf("To: %s\n", recepient);
      std::cout<<"To: "<<std::endl<<recepient;
      std::cout<<AlertInfo[breachType] <<std::endl;
  }

      
  }
