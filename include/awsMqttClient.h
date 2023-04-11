#ifndef NTS_AWS_MQTTCLIENT_H
#define NTS_AWS_MQTTCLIENT_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoMqttClient.h>
#include "secrets.h"                                      //certicate a library(users changeable mandatory)

class awsMqttClient  
{
public:
   
    awsMqttClient();                                        //call a constructor function
    esp_err_t wifi_connect(const char* ssid, const char* password);    //connect the wifi
    esp_err_t mqtt_begin();                                           //connect the awsmqtt test client
    void mqtt_subscribe(const char* MQTT_SUB_TOPIC);                 //subscribe topic and get msg from aws
    void mqtt_publish(const char* MQTT_PUB_TOPIC, char* payload);    //publish a topic and send msg TO aws
    void poll();                                                  //stay alive the connection

private:
 
    static void messageHandler(int messageSize);                 
    const char* MQTT_SUB_TOPIC = "";                          //define a sub topic
    const char* MQTT_PUB_TOPIC = "";                         //define a pub topic
    char* payload;                                       //define a payload
};

#endif