#include "RTPScreen.hpp"


RTPScreen::RTPScreen(){

}

void RTPScreen::begin(){
  lcd.init();
  lcd.backlight();
}

void RTPScreen::print(String firstLine, String secondLine){
  lcd.clear();
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}
