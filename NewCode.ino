#include <Arduino.h>
#include "AsyncTelegram.h"
AsyncTelegram myBot;

const char* ssid = "ABYAN";
const char* pass = "ctkleksana";
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
    if (msg.text.equalsIgnoreCase("Off1")) 
    {      
      digitalWrite(led1, LOW);                          
      myBot.sendMessage(msg, "Light1 is now Off");        
    }
    else if (msg.text.equalsIgnoreCase("On1")) 
    {       
      digitalWrite(led1, HIGH);                         
      myBot.sendMessage(msg, "Light1 is now On");      
    }
    else if (msg.text.equalsIgnoreCase("Off2")) 
    {       
      digitalWrite(led2, LOW);                         
      myBot.sendMessage(msg, "Light2 is now Off");      
    }
    else if (msg.text.equalsIgnoreCase("On2")) 
    {       
      digitalWrite(led2, HIGH);                         
      myBot.sendMessage(msg, "Light2 is now On");      
    }
    else if (msg.text.equalsIgnoreCase("/command1")) 
    {       
      digitalWrite(led1, HIGH);                         
      myBot.sendMessage(msg, "Light1 is now On");      
    }
    else if (msg.text.equalsIgnoreCase("/command2")) 
    {       
      digitalWrite(led1, LOW);                         
      myBot.sendMessage(msg, "Light1 is now Off");      
    }
    else if (msg.text.equalsIgnoreCase("/command3")) 
    {       
      digitalWrite(led2, HIGH);                         
      myBot.sendMessage(msg, "Light2 is now On");      
    }
    else if (msg.text.equalsIgnoreCase("/command4")) 
    {       
      digitalWrite(led2, LOW);                         
      myBot.sendMessage(msg, "Light2 is now Off");      
    }
    else if (msg.text.equalsIgnoreCase("/command5")) 
    {
      digitalWrite(led1, HIGH);       
      digitalWrite(led2, HIGH);                         
      myBot.sendMessage(msg, "Your lights are all on");      
    }
    else if (msg.text.equalsIgnoreCase("/command6")) 
    {
      digitalWrite(led1, LOW);       
      digitalWrite(led2, LOW);                         
      myBot.sendMessage(msg, "Your lights are all off");      
    }
    else 
    {                                                  
      // generate the message for the sender
      String reply;
      reply = "Welcome In SafLamp BOT\n" ;
      reply += "You can use below commands to operate this bot or use shortcut menu in bottom left of the message:\n" ;
      reply += "============================\n\n" ;
      //reply += msg.sender.username;
      reply += ". Light 1 on = On1\n";
      reply += ". Light 1 off = Off1\n";
      reply += ". Light 2 on = On2\n";
      reply += ". Light 2 off = Off2\n";
      myBot.sendMessage(msg, reply);
    }
  }
}
