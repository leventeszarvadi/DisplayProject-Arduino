#include <LCDClass.h>
#include <IRremote.h>
#include <VirtualWire.h>


int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results res;

const long callAcceptButton=16753245;
const long phoneButton=16736925;
const long callDeclineButton=16769565;
const long chMinusButton=16720605;
const long chPlusButton=1671245;
const long eqButton=16761405;
const long backButton=16769055;
const long nextButton=16754775;
const long startStopButton=16748655;
const long minusButton=16750695;
const long plusButton=16756815;
const long Button0=16738455;
const long Button1=16724175;
const long Button2=16718055;
const long Button3=16743045;
const long Button4=16716015;
const long Button5=16726215;
const long Button6=16734885;
const long Button7=16728765;
const long Button8=16730805;
const long Button9=16732845;

const int redLed=7;
const int displaysRefreshTime=6000;
unsigned long previousMillis = 0;
 

LCD lcd(6,11,5,4,3,2);

void setup()
{
  Serial.begin(9600);
  lcd.init();
  pinMode(redLed,OUTPUT);
  irrecv.enableIRIn(); // Start the receiver

  vw_set_rx_pin(13);
  vw_set_tx_pin(12);
  vw_setup(4000);// speed of data transfer Kbps
}
long number=0;
void loop() {
  if (irrecv.decode(&res)) {
    
    long results=res.value;
    Serial.println(results,HEX);
    if (results>0)
    {
        bool correctSignal=true;
        
        switch(results)
        {
          case plusButton:
            lcd.settingsButtonPushed();
            break;
          case minusButton:
            lcd.cancelButtonPushed();
            break;
          case nextButton:
            lcd.nextButtonPushed();
            break;
          case backButton:
            lcd.backButtonPushed();
            break;
          case startStopButton:
            lcd.OKButtonPushed();
            break;
          case eqButton:
            lcd.displayBlockButtonPushed();
            break;
          case Button0:
            lcd.xButtonPushed(0);
            break;
          case Button1:
            lcd.xButtonPushed(1);
            break;
          case Button2:
            lcd.xButtonPushed(2);
            break;
          case Button3:
            lcd.xButtonPushed(3);
            break;
          case Button4:
            lcd.xButtonPushed(4);
            break;
          case Button5:
            lcd.xButtonPushed(5);
            break;
          case Button6:
            lcd.xButtonPushed(6);
            break;
          case Button7:
            lcd.xButtonPushed(7);
            break;
          case Button8:
            lcd.xButtonPushed(8);
            break;
          case Button9:
            lcd.xButtonPushed(9);
            break;
          case callAcceptButton:
            lcd.letterButtonPushed('A');
            break;
          case phoneButton:
            lcd.letterButtonPushed('B');
            break;
          case callDeclineButton:
            lcd.letterButtonPushed('C');
            break;
          default:
            correctSignal=false;
            break;
        }
        /*if(correctSignal)
        {
          digitalWrite(redLed,HIGH);
        }
        delay(50);
        digitalWrite(redLed,LOW);*/
    }
    irrecv.resume(); // Receive the next value
  }
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > displaysRefreshTime)
  {
    previousMillis = currentMillis;  
    char *message;
    String mes;
    Song actualSong=lcd.getActualSong();
    if (lcd.isDisplayBlocked()|| !actualSong.itWasSetUp)
    {
      mes=String("G////");
    }
    else
    {
      mes="G";
      if (actualSong.number!=0)
      {
        mes+=String(actualSong.number);
      }
      mes+="/";
      if (actualSong.version!='_')
      {
        mes+=String(actualSong.version);
      }
      mes+="/";
      if (actualSong.startVerse!=0)
      {
        mes+=String(actualSong.startVerse);
      }
      mes+="/";
       if (actualSong.endVerse!=0)
      {
        mes+=String(actualSong.endVerse);
      }
       mes+="/";
    }
    message=mes.c_str();
   // Serial.println(message);
    vw_send((uint8_t *)message, strlen(message));
    
  }
  else
  {
    delay(100);
  }
  
}


