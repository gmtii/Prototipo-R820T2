/*
Main code by Richard Visokey AD7C - www.ad7c.com
Revision 2.0 - November 6th, 2013
*/

void R820T2_set_frequency(uint32_t freq);
extern uint32_t  r820t_freq;
  //uint32_t r820t_freq  = r820t_freq;  
  int mode = 1; //(1=LSB, 2=USB, 3=CW, 6=RTTY, 7=CW-REV, 9=RTTY-REV)  
  String received;  
  String command;  
  String parameter;  
  String sent;  



void cat_k() {    
  // Update the display and frequency if the new Freq NEQ the old Freq   
   //R820T2_set_frequency(r820t_freq);
   if(Serial.available() > 0)  
   {  
    received = Serial.readStringUntil(';');  
    received.toUpperCase();  
    received.replace("\n","");  
    command = received.substring(0,2);  
    parameter = received.substring(2,received.length()); 
     
    if (command == "FA")  
    {    
     if (parameter != "")  
     {  
      r820t_freq = parameter.toInt();  
      r820t_freq = r820t_freq;      
      //R820T2_set_frequency(r820t_freq);
     }  
    sent = "FA" // Return 11 digit frequency in Hz. 
     + String("00000000000").substring(0,11-(String(r820t_freq).length()))   
      + String(r820t_freq) + ";";  
      
    }  
   
    else if (command == "FB")  
    {    
     if (parameter != "")  
     {  
      r820t_freq = parameter.toInt();  
      r820t_freq = r820t_freq;  
      //R820T2_set_frequency(r820t_freq);
     }  
    sent = "FB" // Return 11 digit frequency in Hz. 
     + String("00000000000").substring(0,11-(String(r820t_freq).length()))   
      + String(r820t_freq) + ";";  
      
    }

    
    else if (command == "IF")  
    {  
     sent = "IF" // Return 11 digit frequency in Hz.  
     + String("00000000000").substring(0,11-(String(r820t_freq).length()))   
      + String(r820t_freq) + String("   ") + "+" + "0000" + "0" + "0" + String(" ") + "00" + "0" + String(mode) + "0" + "0" + "0" + "0" + "01" + String(" ") + ";";  
    }  
    else if (command == "MD")  
    {  
     if (parameter != "")  
     {  
      mode = parameter.toInt();    

     }  
     sent = "MD"   
      + String(mode) + ";";  
    }  
    else if (command == "ID")  
   {  
     sent = "ID"   
      + String("017") + ";";  
    }  
    else if (command == "TX")  
    {  
  //   digitalWrite(ledPin, HIGH); 
 
     sent = command  
      + String(parameter) + ";";   
    }  
    else if (command == "r820t_freq")  
    {  
  //   digitalWrite(ledPin, LOW); 

     sent = command  
      + String(parameter) + ";";   
    }  
    else if (command == "SM")  
    {  
     sent = command  
      + String(parameter) + "0010" + ";";   
    }  
   else  
   {  
       sent = command  
       + String(parameter) + ";";  
   }  
    Serial.print(sent);   
    sent = String("");   
    R820T2_set_frequency(r820t_freq); 
    Serial.flush();   
   }  
  
 }
