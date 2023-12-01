#include <Arduino.h>
#include "AsyncTelegram.h"
AsyncTelegram myBot;

const char* ssid = "masis";
const char* pass = "sandikeras";
const char* token = "6682234876:AAHtFtP-zpqXYklpXUaDfxHwiceMrWVC0NA";    

int led = 16; 

void setup() 
{
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");

  WiFi.setAutoConnect(true);   
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, pass);
  delay(500);
  while (WiFi.status() != WL_CONNECTED) 
  {
  Serial.print('.');
  delay(500);
  }

  myBot.setUpdateTime(1000);
  myBot.setTelegramToken(token);
  
  Serial.print("\nTest Telegram connection... ");
  myBot.begin() ? Serial.println("OK") : Serial.println("NOK");

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH); 
}

void loop() 
{
  TBMessage msg;

  if (myBot.getNewMessage(msg)) 
  {
    if (msg.text.equalsIgnoreCase("Off")) 
    {      
      digitalWrite(led, LOW);                          
      myBot.sendMessage(msg, "Light is now Off");        
    }
    else if (msg.text.equalsIgnoreCase("On")) 
    {       
      digitalWrite(led, HIGH);                         
      myBot.sendMessage(msg, "Light is now On");      
    }
    else 
    {                                                  
      // generate the message for the sender
      String reply;
      reply = "Welcome In DIYPROJECTSLAB.Com BOT\n" ;
      reply += "You can use below commands to operate:\n" ;
      reply += "============================\n\n" ;
      //reply += msg.sender.username;
      reply += ". Light on = On\n";
      reply += ". Light off = Off\n";
      myBot.sendMessage(msg, reply);
    }
  } 
}
