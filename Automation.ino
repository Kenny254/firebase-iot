
#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>

// give firebase details
#define FIREBASE_HOST "firebasedb name"
#define FIREBASE_AUTH "secret_token"

#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PSW"                                //Password of your wifi network 

#define D2 14 //D2
int val1;

#define D1 4  //D1
int val2;

void setup() 
{
  Serial.begin(115200);          // Select the same baud rate on Serial Monitor for debug
 
  pinMode(D2,OUTPUT);
  pinMode(D1,OUTPUT);
  
  digitalWrite(D2,LOW);
  digitalWrite(D1,LOW);
  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setString("light","0");                     
  Firebase.setString("fan","0"); 
  
  
}

void firebasereconnect()
{
    Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }

void loop() 
{
//if any error in operation
  if (Firebase.failed())
      {
      Serial.print("failed to connect");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }
      
 
  val1=Firebase.getString("fan").toInt();     //value  from the firebase          
  //Serial.println(val1);
  if(val1==1)                                                             // If, the Status is 1, turn on the PIN
     {
       digitalWrite(D2,HIGH);
      Serial.println("FAN ON");
    }
    else if(val1==0)                                                      // If, the Status is 0, turn Off the PIN
    {                                      
      digitalWrite(D2,LOW);
      Serial.println("Fan 2 OFF");
    }

   val2=Firebase.getString("light").toInt();  //value  from the firebase
  //Serial.println(val2);
  if(val2==1)                                    // If, the Status is 1, turn on the PIN
     {
      digitalWrite(D1,HIGH);
      Serial.println("Light ON");
    }
    else if(val2==0)                            // If, the Status is 0, turn Off the PIN
    {                                      
      digitalWrite(D1,LOW);
      Serial.println("light OFF");
    }

   delay(200);    //delay for rechecking 
      
}
