#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN A12   
#define DHTTYPE DHT11

DHT dht (DHTPIN, DHTTYPE);
#define BAUD_RATE 9600
#define TERM_CHAR '\n'
#define BUF_LEN  30


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
byte ip[] = { 192, 168, 1, 180 }; 
byte gateway[] = { 192, 168, 1, 1 }; 
byte subnet[] = { 255, 255, 255, 0 }; 
EthernetServer server(80);                                  
byte sampledata=50; 

char Link[]= "http://www.bnu.tv/camera/embed?camera=sete-de-setembro"; //video link

float h; 
float t;
int i;
int count=0;
boolean DispAlarme = false;
boolean FlagAlarme = false;
boolean AIMode = false;
char c;
String readString = String(BUF_LEN);

int ContatoSecoState1 = 0; 
int ContatoSecoState2 = 0;
int ContatoSecoState3 = 0;
int ContatoSecoState4 = 0;
int ContatoSecoState5 = 0;
int ContatoSecoState6 = 0; 
int ContatoSecoState7 = 0; 
int ContatoSecoState8 = 0;  

int optoacopladorState1 = 0;   
int optoacopladorState2 = 0; 

const int rele1 =  22;  
const int rele2 =  23;  
const int rele3 =  24;   
const int rele4 =  25;  
const int rele5 =  26;   
const int rele6 =  27;   
const int rele7 =  28;   
const int rele8 =  29;   
const int rele9 =  42;    
const int rele10 =  43; 

const int contatoseco8 = 41;    
const int contatoseco7 = 40;    
const int contatoseco6 = 49;   
const int contatoseco5 = 48;  
const int contatoseco4 = 47;    
const int contatoseco3 = 46;    
const int contatoseco2 = 45;   
const int contatoseco1 = 44;   

const int optoacopladorbutton1 = 18;   
const int optoacopladorbutton2 = 19;  
const int Sirene = 33;    //Saida de 12 volts Até 1,5A
const int Discadora = 32;  //Saida de 12 volts até 1A  

LiquidCrystal lcd(39, 38, 34, 35, 36, 37);

void setup(){
  lcd.begin(16, 2);
  
  pinMode(rele1, OUTPUT); 
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT); 
  pinMode(rele4, OUTPUT);
  pinMode(rele5, OUTPUT); 
  pinMode(rele6, OUTPUT);
  pinMode(rele7, OUTPUT); 
  pinMode(rele8, OUTPUT);
  pinMode(rele9, OUTPUT); 
  pinMode(rele10, OUTPUT);
  pinMode(Discadora, OUTPUT);
  pinMode(Sirene, OUTPUT);

  pinMode(contatoseco6, INPUT);  
  pinMode(contatoseco5, INPUT);  
  pinMode(contatoseco4, INPUT);  
  pinMode(contatoseco3, INPUT);
  pinMode(contatoseco2, INPUT);  
  pinMode(contatoseco1, INPUT);
  pinMode(contatoseco2, INPUT);  
  pinMode(contatoseco1, INPUT);

  pinMode(optoacopladorbutton1, INPUT);
  pinMode(optoacopladorbutton2, INPUT);
  
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  lcd.print(Ethernet.localIP());

  Serial.begin(9600);
  Serial2.begin(9600); //Porta bluetooth
  Serial3.begin(9600); //Porta Xbee
  // Todas as portas declaradas aqui conseguem acionar reles com o seguinte comando _r1on e _r1off para o rele 2 _r2on e _r2off e assim por diante
}
 
void loop(){
  
  leserial();
  rede();
  count++;
  
  if(count == 1000){
  h = dht.readHumidity(); 
  t = dht.readTemperature(); 
  lcd.setCursor(0,1);
  lcd.print("RH:     ");
  lcd.setCursor(4,1);
  lcd.print(h);
  
  lcd.setCursor(8,1);
  lcd.print("Temp:      ");
  lcd.setCursor(13,1);
  lcd.print(t);
  count=0;
  }
              if(readString.indexOf("r1on") >0)
          {
            
            digitalWrite(rele1, HIGH);   
            Serial.println("Ligando Rele 1");
            Serial3.println("Ligando Rele 1");
            Serial.println(readString);
          }
              if(readString.indexOf("r1off") >0)
          {
            
            digitalWrite(rele1, LOW);   
            Serial.println("Desligando Rele 1");
            Serial3.println("Desligando Rele 1");
            Serial.println(readString);
          }
              if(readString.indexOf("r2on") >0)
          {    
            digitalWrite(rele2, HIGH);        
            Serial.println("Ligando Rele 2");
            Serial3.println("Ligando Rele 2");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r2off") >0)
          {
           
            digitalWrite(rele2, LOW);   
            Serial.println("Desligando Rele 2");
            Serial3.println("Desligando Rele 2");
            Serial.println(readString);
          }
          if(readString.indexOf("r3on") >0)
          {    
            digitalWrite(rele3, HIGH);         
            Serial.println("Ligando Rele 3");
            Serial3.println("Ligando Rele 3");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r3off") >0)
          {
          
            digitalWrite(rele3, LOW);  
            Serial.println("Desligando Rele 3");
            Serial3.println("Desligando Rele 3");
            Serial.println(readString);
          }
            if(readString.indexOf("r4on") >0)
          {    
            digitalWrite(rele4, HIGH);       
            Serial.println("Ligando Rele 4");
            Serial3.println("Ligando Rele 4");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r4off") >0)
          {
           
            digitalWrite(rele4, LOW);  
            Serial.println("Desligando Rele 4");
            Serial3.println("Desligando Rele 4");
            Serial.println(readString);
          }
          
            if(readString.indexOf("r5on") >0)
          {    
            digitalWrite(rele5, HIGH);     
            Serial.println("Ligando Rele 5");
            Serial3.println("Ligando Rele 5");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r5off") >0)
          {
            
            digitalWrite(rele5, LOW);   
            Serial.println("Desligando Rele 5");
            Serial3.println("Desligando Rele 5");
            Serial.println(readString);
          }
          
            if(readString.indexOf("r6on") >0)
          {    
            digitalWrite(rele6, HIGH);     
            Serial.println("Ligando Rele 6");
            Serial3.println("Ligando Rele 6");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r6off") >0)
          {
           
            digitalWrite(rele6, LOW);   
            Serial.println("Desligando Rele 6");
            Serial3.println("Desligando Rele 6");
            Serial.println(readString);
          }
            if(readString.indexOf("r7on") >0)
          {    
            digitalWrite(rele7, HIGH);   
            Serial.println("Ligando Rele 7");
            Serial3.println("Ligando Rele 7");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r7off") >0)
          {
            
            digitalWrite(rele7, LOW);  
            Serial.println("Desligando Rele 7");
            Serial3.println("Desligando Rele 7");
            Serial.println(readString);
          }
            if(readString.indexOf("r8on") >0)
          {    
            digitalWrite(rele8, HIGH);        
            Serial.println("Ligando Rele 8");
            Serial3.println("Ligando Rele 8");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r8off") >0)
          {
           
            digitalWrite(rele8, LOW); 
            Serial.println("Desligando Rele 8");
            Serial3.println("Desligando Rele 8");
            Serial.println(readString);
          }
            if(readString.indexOf("r9on") >0)
          {    
            digitalWrite(rele9, HIGH);      
            Serial.println("Ligando Rele 9");
            Serial3.println("Ligando Rele 9");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r9off") >0)
          {
           
            digitalWrite(rele9, LOW); 
            Serial.println("Desligando Rele 9");
            Serial3.println("Desligando Rele 9");
            Serial.println(readString);
          }
            if(readString.indexOf("r10on") >0)
          {    
            digitalWrite(rele10, HIGH);     
            Serial.println("Ligando Rele 10");
            Serial3.println("Ligando Rele 10");
            Serial.println(readString);
            
          }
              if(readString.indexOf("r10off") >0)
          {
            
            digitalWrite(rele10, LOW);  
            Serial.println("Desligando Rele 10");
            Serial3.println("Desligando Rele 10");
            Serial.println(readString);
          }
////////////////////////////Aciona sirene ou dicadora ////////////////////////////////////////////

          if(readString.indexOf("all=Ativar+Alarme") >0)
          {
            FlagAlarme = true;
            lcd.setCursor(0,1);
            lcd.print(" Alarme Ativado ");
            
          }
          if(readString.indexOf("all=Desativar+Alarme") >0)
          {
            FlagAlarme = false;
            DispAlarme = false;
            digitalWrite(Discadora, LOW); 
            digitalWrite(Sirene, LOW);
            lcd.setCursor(0,1);
            lcd.print(" Alarme Desativado ");
            
          }
          if(readString.indexOf("all=DiscadoraON") >0)
          {
            digitalWrite(Discadora, HIGH);
          }
          if(readString.indexOf("all=DiscadoraOff") >0)
          {
            digitalWrite(Discadora, LOW);
          }
          
          if (FlagAlarme == true){
            le_sensores();          
  
      
            if (DispAlarme == true){ 
            digitalWrite(Sirene, HIGH);   
            digitalWrite(Discadora, HIGH);
            lcd.setCursor(0,1);
            lcd.print("Falha na Seguranca");
            
            }
            }
//Teste de opto acopladores detectam 9~12v podem ser usados tambem como zonas de alarmes principalmente para sensores de portas e janelas
        optoacopladorState1 = digitalRead(optoacopladorbutton1);
        optoacopladorState2 = digitalRead(optoacopladorbutton2);
        
            if(optoacopladorState1 == 0){
              lcd.setCursor(0,1);
            lcd.print("12v entrada 1");              
            }
            if(optoacopladorState2 == 0){
              lcd.setCursor(0,1);
            lcd.print("12v entrada 2");              
            }
            
//////////////////////////////////////////////////////////////////////////////////////////////////////          
          readString=""; 
 } 
 
////////////////////////////////////////////////////////////////////////////////////////////////////// 
//Função Alarme UP
void le_sensores(){
  ContatoSecoState1 = digitalRead(contatoseco1);
  ContatoSecoState2 = digitalRead(contatoseco2);
  ContatoSecoState3 = digitalRead(contatoseco3);
  ContatoSecoState4 = digitalRead(contatoseco4);
  ContatoSecoState5 = digitalRead(contatoseco5);
  ContatoSecoState6 = digitalRead(contatoseco6);
  ContatoSecoState7 = digitalRead(contatoseco7);
  ContatoSecoState8 = digitalRead(contatoseco8);
  
  if (ContatoSecoState1 == LOW){
      DispAlarme = true;
  } 
  
  if (ContatoSecoState2 == LOW){
      DispAlarme = true;
  } 
  if (ContatoSecoState3 == LOW){
      DispAlarme = true;
  } 
  
  if (ContatoSecoState4 == LOW){
      DispAlarme = true;
  } 
  if (ContatoSecoState5 == LOW){
      DispAlarme = true;
  } 
  if (ContatoSecoState6 == LOW){
      DispAlarme = true;
  }
  if (ContatoSecoState7 == LOW){
      DispAlarme = true;
  } 
  if (ContatoSecoState8 == LOW){
      DispAlarme = true;
  }  
  
}

void leserial(){
 
 while(Serial.available()){
    c = (char) Serial.read();
    if (readString.length() < 100)
      {
       
        readString += c; 
      }
    delay(1); 
  }
  while(Serial2.available()){
    c = (char) Serial2.read();
    if (readString.length() < 100)
      {
       
        readString += c; 
      }
    delay(1); 
  }
    while(Serial3.available()){
    c = (char) Serial3.read();
    if (readString.length() < 100)
      {
       
        readString += c; 
      }
    delay(1); 
  }
  
}  
/////////////////////////////////////////////////////////////////////////////////////////////////////////  
//Função que recebe string do navegador 
 void rede(){
 
EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
  if (client.available()) {
    c = client.read();
   
    if (readString.length() < 100)
      {
        
        readString += c; 
      }
       
        if (c == '\n') {
         
          if (readString.indexOf("?") <0)
          {
           
          }
         
            //--------------------------HTML------------------------          



client.println("HTTP/1.1 200 OK");

client.println("Content-Type: text/html");


client.println();



client.print("<html><head>");

client.print("<title>I-Casa Control</title>");

client.println("</head>");

client.print("<body bgcolor='#CCCCCC'>");

client.println("<br><hr />");

client.println("<h1><div align='center'><font color='#2076CD'>Automacao Residencial I-Casa Control</font color></div></h1>");
client.println("<h1><div align='center'><font color='#2076CD'>Douglas Rodrigues</font color></div></h1>");

client.println("<hr /><br>");

client.println("<div align='left'><font face='Verdana' color='#000000'>Painel de Controle WEB:</font></div>");

client.println("</tr>");
client.println("</table>");
client.println("<br>");

if (FlagAlarme == 0)
client.println("<form method=get><input type=submit name=all value='Ativar Alarme'></form>");
else
client.println("<form method=get><input type=submit name=all value='Desativar Alarme'></form>");

client.println("<br>");

client.println("<div align='left'><font face='Verdana' color='#000000'>Temperatura:");
client.print(t);
client.println("</font></div>");

client.println("<div align='left'><font face='Verdana' color='#000000'>Umidade:");
client.print(h);
client.println("</font></div>");

client.println("<br>");

client.println("<table border='1' width='100%' cellpadding='5'>");

client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Sala<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r1on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r1off value='Apagar'></form></td>");


if (digitalRead(rele1)==HIGH)
  client.println("<td align='center'><font color='green' size='5'>LIG");
else
client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");

client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Cozinha<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r2on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r2off value='Apagar'></form></td>");

if (digitalRead(rele2) == HIGH)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Garagem<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r3on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r3off value='Apagar'></form></td>");

if (digitalRead(rele3) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Suite<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r4on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r4off value='Apagar'></form></td>");

if (digitalRead(rele4) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Quarto<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r5on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r5off value='Apagar'></form></td>");

if (digitalRead(rele5) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Banheiro Suite<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r6on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r6off value='Apagar'></form></td>");

if (digitalRead(rele6) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Escritorio<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r7on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r7off value='Apagar'></form></td>");

if (digitalRead(rele7) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Banheiro<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r8on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r8off value='Apagar'></form></td>");

if (digitalRead(rele8) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Portao Social<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r9on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r9off value='Apagar'></form></td>");

if (digitalRead(rele9) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
client.println("<tr bgColor='#222222'>");

client.println("<td bgcolor='#222222'><font face='Verdana' color='#CFCFCF' size='2'>Portao Garagem<br></font></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r10on value='Acender'></form></td>");

client.println("<td align='center' bgcolor='#222222'><form method=get><input type=submit name=r10off value='Apagar'></form></td>");

if (digitalRead(rele10) == 1)
 client.println("<td align='center'><font color='green' size='5'>LIG");
else
 client.println("<td align='center'><font color='#CFCFCF' size='5'>DES");
 
client.println("</tr>");
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
client.println("</tr>");

client.println("</table>");

client.println("<br>");

if (FlagAlarme == 0)
client.println("<form method=get><input type=submit name=all value='Ativar Alarme'></form>");
else
client.println("<form method=get><input type=submit name=all value='Desativar Alarme'></form>");
client.println("<h1><div align='center'><font color='#2076CD'>Video Monitoramento </font color></div></h1>");

client.print("<div align='center'><iframe width=100% height=100% src=");
client.print(Link); 
client.println(" frameborder=1 allowfullscreen></iframe>");


//client.println("<br>");
//client.println("<form method=get><input type=submit name=all value='DiscadoraON'></form>");
//client.println("<form method=get><input type=submit name=all value='DiscadoraOff'></form>");

//client.println("<form style='height: 257px;' method='get' action='?' name='fomlu_id'></form>");
//client.println("<form method=get><input name='ip' size='17' maxlength=17>");
//client.println("<form method=get><input value='Salvar' type=submit></form>");
client.println("<br>");
client.println("<br>");

client.println("</body></html>");
          
          client.stop();
            }              
          }        
        }               
      } 
 } 
