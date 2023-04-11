#include "awsMqttClient.h"

WiFiClientSecure wifiClient;               //create a object for WiFiClientSecure class
MqttClient mqttClient(wifiClient);         //create a object for MqttClient class

#define DEBUG_awsMqttClient                  //define debug comment

#ifdef DEBUG_awsMqttClient
#define awsMqttClientconsoleln(x) Serial.println(x)       //use a debug commanda instead for print function
#define awsMqttClientconsole(x) Serial.print(x)
#else
#define awsMqttClientconsole(...)
#define awsMqttClientconsoleln(...)
#endif



awsMqttClient::awsMqttClient(void)            //create a constructor function
{
}

esp_err_t awsMqttClient::wifi_connect(const char *ssid, const char *password)      //wifi_connect function for esp32
{
    WiFi.begin(ssid, password);                         //initialize a ssid and password
    awsMqttClientconsoleln(ssid);
    while (WiFi.status() != WL_CONNECTED)                  //check the wifi connection status
    {
        Serial.println("Ready for connect to device_wifi");
    
    }
    awsMqttClientconsole("IP ADDRESS : ");
    awsMqttClientconsoleln(WiFi.localIP());                //after wifi connected print the esp32 ip address
    if (WL_CONNECTED)
    {
        Serial.println("Wifi connected sucessfully");
        return ESP_OK;                                  //check the error codes
    }
    else
    {
        Serial.println("wifi not connected");
        return ESP_FAIL;                              //check the error codes
    }
}

esp_err_t awsMqttClient::mqtt_begin()                 //connect mqtt for mqtt_begin
{
    wifiClient.setCACert(AWS_CERT_CA);                //verify a amazon root CA1 certificate
    wifiClient.setCertificate(AWS_CERT_CRT);          //verify a Device certificate
    wifiClient.setPrivateKey(AWS_CERT_PRIVATE);       //verify a privatekey certificate
    if (mqttClient.connect(AWS_IOT_ENDPOINT, 8883))   //connect a aws endpoint and port
    {
        awsMqttClientconsoleln("You're connected to the MQTT broker!");  //connection established 
        awsMqttClientconsoleln();
        return ESP_OK;                                                //check the error codes
    }
    else
    {
        awsMqttClientconsole("MQTT connection failed! Error code = ");    //connection failed
        awsMqttClientconsoleln(mqttClient.connectError());
        return ESP_FAIL;                                             //check the error codes
    }
}

void awsMqttClient::mqtt_subscribe(const char *MQTT_SUB_TOPIC)       //subscribe function
{
    mqttClient.subscribe(MQTT_SUB_TOPIC);                    //subscribe a topic
    mqttClient.onMessage(messageHandler);                //msg recv function
}

void awsMqttClient::messageHandler(int messageSize)
{
    awsMqttClientconsole("Received a message with topic '");            
    awsMqttClientconsole(mqttClient.messageTopic());              //receive the topic
    //awsMqttClientconsoleln(messageSize);                        //receive the msg size

    // use the Stream interface to print the contents
    while (mqttClient.available())                         //check the status for esp32
    {
        awsMqttClientconsole((char)mqttClient.read());       //recive the msg from aws maqtt test client
    }

    awsMqttClientconsoleln("");
}

void awsMqttClient::mqtt_publish(const char *MQTT_PUB_TOPIC, char *payload)
{
    mqttClient.beginMessage(MQTT_PUB_TOPIC);                   //begin a pub topic from esp32 to aws

    mqttClient.print(payload);                        //print a msg from awsmqtt test client
    // mqttClient.print("this is test");
    mqttClient.endMessage();                          
}

void awsMqttClient::poll()                            //connection stay alive function
{
    mqttClient.poll();                //connection stay alive for esp32 and aws mqttclient 
}
