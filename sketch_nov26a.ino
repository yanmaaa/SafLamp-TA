#include <Arduino.h>
#include "AsyncTelegram.h"
AsyncTelegram myBot;

const char* ssid = "masis";
const char* pass = "sandikeras";
const char* token = "6682234876:AAHtFtP-zpqXYklpXUaDfxHwiceMrWVC0NA";    

int led1 = 16;
int led2 = 5; 

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

  pinMode(led1, OUTPUT);
  digitalWrite(led1, HIGH); 

  pinMode(led2, OUTPUT);
  digitalWrite(led2, HIGH);
}

void loop() 
{
  TBMessage msg;

  if (myBot.getNewMessage(msg)) 
  {
    if (msg.text.equalsIgnoreCase("Off")) 
    {      
      digitalWrite(led1, LOW);                          
      myBot.sendMessage(msg, "Light is now Off");        
    }
    else if (msg.text.equalsIgnoreCase("On")) 
    {       
      digitalWrite(led1, HIGH);                         
      myBot.sendMessage(msg, "Light is now On");      
    }
    else if (msg.text.equalsIgnoreCase("Off1")) 
    {       
      digitalWrite(led2, LOW);                         
      myBot.sendMessage(msg, "Light2 is now Off");      
    }
    else if (msg.text.equalsIgnoreCase("On1")) 
    {       
      digitalWrite(led2, HIGH);                         
      myBot.sendMessage(msg, "Light2 is now On");      
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

