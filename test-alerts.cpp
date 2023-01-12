#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include <sstream>
#include <iostream>

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(30, 20, 30) == NORMAL);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
}

TEST_CASE("infers the breach according to Passive cooling limits") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH);
}

TEST_CASE("infers the breach according to Mid active limits") {
   REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45) == TOO_HIGH);
}

TEST_CASE("infers the breach according to Hi active limits") {
   REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
}

TEST_CASE("sendTo Controller check")
{ 
   std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    sendToController(NORMAL);
    
    //std::cout.rdbuf(p_cout_streambuf); // restore
std::cout.rdbuf(p_cout_streambuf);
    // test your oss content...
    REQUIRE(oss.str()  == "feed : 0\n");
    
}


TEST_CASE("sendTo email check TOO_LOW")
{ 
   std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    sendToEmail(TOO_LOW);
    
    //std::cout.rdbuf(p_cout_streambuf); // restore
std::cout.rdbuf(p_cout_streambuf);
    // test your oss content...
    REQUIRE(oss.str()  == "To: \na.b@c.com Hi, the temperature is too  Low\n");
    
}

TEST_CASE("sendTo email check TOO_High")
{ 
   std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    sendToEmail(TOO_HIGH);
    
    //std::cout.rdbuf(p_cout_streambuf); // restore
std::cout.rdbuf(p_cout_streambuf);
    // test your oss content...
    REQUIRE(oss.str()  == "To: \na.b@c.com Hi, the temperature is too  High\n");
    
}

TEST_CASE("sendTo email check Normal")
{ 
   std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    sendToEmail(NORMAL);
    
    //std::cout.rdbuf(p_cout_streambuf); // restore
std::cout.rdbuf(p_cout_streambuf);
    // test your oss content...
    REQUIRE(oss.str()  == "");
    
}

