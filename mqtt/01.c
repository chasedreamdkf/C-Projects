#include<stdio.h>
#include<stdlib.h>
#include "MQTTClient.h"

#define SERVER_URL "tcp://117.78.5.125:1883"
#define Client_ID "NEC001_0_0_2025070605"
#define UserName "NEC001"
#define PassWord "4885ef12774422564c5a4e3dab756257b857d7f5f5e02911a7f63504d303162f"

// 失去连接回调
void LostConnection(void* context, char* cause){
    printf("失去连接!原因: %s\n", cause);
}

// 收到主题信息回调函数
int MsgArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message){
    printf("Receive topic: %s,message data: \n", topicName);
    printf("%.*s\n", message->payloadlen, (char*)message->payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

// 主题发布成功回调函数
void DeliveryMsg(void *context, MQTTClient_deliveryToken dt){
    printf("publish topic success,token = %d \n", dt);
}

int main(){
    // 创建MQTT客户端
    MQTTClient client;
    int ret = MQTTClient_create(&client, SERVER_URL, Client_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    if(ret != MQTTCLIENT_SUCCESS){
        printf("创建MQTT客户端失败!\nret: %d\n", ret);
        exit(EXIT_FAILURE);
    }
    
    // 创建并配置MQTT连接结构体
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.username = UserName;
    conn_opts.password = PassWord;
    conn_opts.keepAliveInterval = 60;   // 心跳时间
    conn_opts.cleansession = 1;         // 清除会话

    // 设置MQTT连接的回调函数
    MQTTClient_setCallbacks(client, NULL, LostConnection, MsgArrived, DeliveryMsg);

    // 连接到MQTT服务器
    ret = MQTTClient_connect(client, &conn_opts);
    if(ret != MQTTCLIENT_SUCCESS){
        printf("MQTT服务器连接失败!\nret: %d\n", ret);
        exit(EXIT_FAILURE);
    }
    printf("MQTT服务器连接成功!\n");

    sleep(30);
    return 0;
} 