#include <LCDClass.h>
#include <IRremote.h>

int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results res;

const int ok=92;
const int back=90;
const int next=91;
const int settings=64;

long shiftNumber=65536;
LCD lcd(6,11,5,4,3,2);


void setup()
{
  Serial.begin(9600);
  lcd.init();
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&res)) {
    
    long results=res.value;
    if (results>0){
       if ((results==settings) || (results==settings+shiftNumber)){
      lcd.settingsButtonPushed();
    }
      if (results==ok || results==ok+shiftNumber){
      lcd.OKButtonPushed();
    } 
      if (results==back || results==back+shiftNumber){
      lcd.backButtonPushed();
    }
      if (results==next || results==next+shiftNumber){
      lcd.nextButtonPushed();
    }
      if (results<10){
      lcd.xButtonPushed(results);
    }

      if ((results<(10+shiftNumber)) && (results>=shiftNumber)){
      lcd.xButtonPushed(results-shiftNumber);
    }
    
    Serial.println(results);
    }

   
    
    irrecv.resume(); // Receive the next value
  }
  delay(70);
}


