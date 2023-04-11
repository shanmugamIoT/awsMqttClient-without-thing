//This example file is used for connect esp32 to AWS MqtttestClient 
//To use all function is mandatory for connection between the esp32 and aws mqtttest client 
//another mandatory purpose to users to change the secrets.h file 
//That file is located in .pio (lib_deps) folder 
//so you move to the folder and place your amazon certificates (root CA1,private key,Device)  and aws endpoint
//Above steps or completed your code is clearly compile
//configure wifi ssid and password used for #define and const char* data type
//configure a publish and subcribe topics in #define and const char*


#include <Arduino.h>
#include <awsMqttClient.h>          //include the awsMqttClient library

awsMqttClient client;               //create a object for awsMqttClient class


const char* MQTT_SUB_TOPIC  = " ";      //create a sub topic 
const char* MQTT_PUB_TOPIC =" ";       //create a pub topic
char* payload =" ";                 //type a payload msg for awsmqttclient (json is available)
int status;                       // create a int variable to use see a wifi and mqtt connection error codes

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                   //initialize a serial monitor
  client.wifi_connect(" "," ");          //configure a wifi for your ssid and password
  client.mqtt_begin();                   //connect the awsMqtt test client
  // status=client->mqtt_begin();        // This method use for you see a connection status with error codes
  // Serial.println(status);             //print to see the connection status
  client.mqtt_subscribe(MQTT_SUB_TOPIC);        //subscribe a topic and get a msg from aws  to esp32
  client.mqtt_publish(MQTT_PUB_TOPIC,payload);   //publisha a msg from esp32 to aws 
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  client.poll();      //This method use for protected stay alive connection between esp32 and awsMqtt test client
  //client->mqtt_publish(MQTT_PUB_TOPIC,payload);      //if you send a msg from aws continuously put a publish function in loop and fix a delay for your wish

 
}