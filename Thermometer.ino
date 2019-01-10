#include <TM1637.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//physical
#define ONE_WIRE_BUS 5
#define WARN_PIN 10
#define DANG_PIN 11
#define SPEAKER 4
#define CLK A2
#define DIO A3
#define LED 13
OneWire oneWire(ONE_WIRE_BUS);
//const uint8_t adress[] = {0x28, 0xFF, 0xAC, 0x17, 0xB1, 0x15, 0x01, 0xBE};
DallasTemperature sensor(&oneWire);
TM1637 disp(CLK,DIO);
RBD::Button warn_button(WARN_PIN, false);
RBD::Button dang_button(DANG_PIN, false);

//logical
#define TEMPERATURE_PRECISION 10
#define INTERVAL 1000
#define STEP 1
RBD::Timer interval(1000);
RBD::Timer setting(2000);
bool beeped_warning = false;
const int WARN_INIT = 60;
const int DANG_INIT = 80;
int warning_temp = WARN_INIT+10;
int danger_temp = DANG_INIT+10;
int cur_temp = 0;

float read_temp() {
  sensor.requestTemperatures();
  return(sensor.getTempCByIndex(0));
}

void setup() {
  pinMode(SPEAKER, OUTPUT);
  pinMode(LED, OUTPUT);
  sensor.begin();
  delay(200);
  sensor.setResolution(TEMPERATURE_PRECISION);
  delay(200);
  disp.init();
  delay(200);
  disp.set(BRIGHT_TYPICAL);
  interval.restart();
  warn_button.setDebounceTimeout(10);
  dang_button.setDebounceTimeout(10);
  tone(SPEAKER, 440, 100);
}

inline void main_logic() {
  disp.point(true);
  digitalWrite(LED, HIGH);
  disp.display(cur_temp);
  cur_temp = read_temp();
  disp.point(false);
  digitalWrite(LED, LOW);
  disp.display(cur_temp);
  if (cur_temp >= danger_temp)  //Danger 
  {
    tone(SPEAKER, 1397, INTERVAL/2);
    beeped_warning = false;
  } 
  else
  {
    if (cur_temp >= warning_temp && !beeped_warning) //warning
    {
      tone(SPEAKER, 440, INTERVAL/2);
      beeped_warning = true; 
    } 
    else
    {
      if (cur_temp >= warning_temp && beeped_warning)
      {
        noTone(SPEAKER);
      }
      else //normal temp
      {
        beeped_warning = false;
        noTone(SPEAKER);
      }
    }
  }
}

inline void edit_logic() {
  if (warn_button.onPressed())
  {
    warning_temp=((warning_temp-WARN_INIT+STEP)%20)+WARN_INIT;
    setting.restart();
  }
  if (dang_button.onPressed())
  {
    danger_temp=((danger_temp-DANG_INIT+STEP)%20)+DANG_INIT;
    setting.restart();
  }
  disp.point(true);
  disp.display(warning_temp*100 + danger_temp);
}

void loop() {
  if (setting.isActive())
  {
    edit_logic();
  }
  else if ((warn_button.onPressed() or dang_button.onPressed()) and !setting.isActive())
  {
    //go to setting mode
    interval.stop();
    setting.restart();
  }
  if (interval.isExpired() or setting.isExpired())
  {
    setting.stop();
    interval.restart();
    main_logic();
  }
}
