#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cjson/cJSON.h>
#include "MQTTClient.h"
#include "MQTTClientPersistence.h"

#define SERVER_URL "tcp://117.78.5.125:1883"
// #define SERVER_URL "ssl://0127321cbc.st1.iotda-device.cn-north-4.myhuaweicloud.com:8883"
#define Client_ID "MedicineBox1_0_0_2025070902"
#define UserName "MedicineBox1"
#define PassWord "a57f91e039e79f1e69bffd4f410e1fd9244147c7b50012a05e891fa4efc64ef3"
#define QOS 0

char topic_get[128] = "$oc/devices/MedicineBox1/sys/shadow/get/request_id=2";
char topic_response[128] = "$oc/devices/MedicineBox1/sys/shadow/get/response/request_id=2";
char topic_report[128] = "$oc/devices/MedicineBox1/sys/properties/report";
char* device_id = "MedicineBox1";

// 失去连接回调
void LostConnection(void* context, char* cause){
    printf("失去连接!原因: %s\n", cause);
}

// 收到主题信息回调函数
// 3. 在回调函数中处理影子数据
int MsgArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message){
    // printf("开始获取数据\n");
    // printf("收到消息, 主题: %s\n", topicName);
    if (strcmp(topicName, topic_response) == 0) {
        // printf("收到影子数据: %.*s\n", message->payloadlen, (char*)message->payload);
        // 解析 JSON 数据
        char *s = malloc(1024*sizeof(char));
        snprintf(s, message->payloadlen + 1, message->payload);
        cJSON *root = cJSON_Parse(s);
        cJSON* shadow = cJSON_GetObjectItem(root, "shadow");
        cJSON* reported = cJSON_GetObjectItem(cJSON_GetArrayItem(shadow, 0), "reported");
        cJSON* properties = cJSON_GetObjectItem(reported, "properties");
        cJSON* MedicineInfos = cJSON_GetObjectItem(properties, "MedicineInfos");
        int arrLen = cJSON_GetArraySize(MedicineInfos);
        // char *str = cJSON_Print(MedicineInfos);
        // printf("MedicineInfos: %s\n", str);
        // printf("arrLen: %d\n", arrLen);
        for(int i = 0; i < arrLen; i++){
            cJSON* MedicineInfo = cJSON_GetArrayItem(MedicineInfos, i);
            char* str2 = cJSON_Print(MedicineInfo);
            printf("%s\n", str2);
        }
    }
    // ... 其他处理 ...
    return 1;
}

char* needData(){
    // 创建数据根
    cJSON* root = cJSON_CreateObject();
    // 创建服务
    cJSON* servece = cJSON_CreateObject();
    // 添加NECcontrol服务id
    char* servece_id = "NECcontrol";
    cJSON* servece_id_obj = cJSON_CreateString(servece_id);
    int ret = cJSON_AddItemToObject(servece, "service_id", servece_id_obj);
    if(ret == cJSON_True){
        printf("为\"%s\"服务添加服务id失败!\n", servece_id);
    }
    // 创建需要上报的属性对象
    cJSON* properties = cJSON_CreateObject();
    // 向属性对象添加内容
    cJSON* AirConditionT = cJSON_CreateString("28");
    cJSON* AirConditionStatus = cJSON_CreateString("ON");
    cJSON* WindowsStatus = cJSON_CreateString("OFF");
    cJSON* TrunkStaus = cJSON_CreateString("ON");
    cJSON* CarLockStaus = cJSON_CreateString("ON");
    cJSON* LEDStatus = cJSON_CreateString("OFF");

    cJSON_AddItemToObject(properties, "AirConditionT", AirConditionT);
    cJSON_AddItemToObject(properties, "AirConditionStatus", AirConditionStatus);
    cJSON_AddItemToObject(properties, "WindowsStatus", WindowsStatus);
    cJSON_AddItemToObject(properties, "TrunkStaus", TrunkStaus);
    cJSON_AddItemToObject(properties, "CarLockStaus", CarLockStaus);
    cJSON_AddItemToObject(properties, "LEDStatus", LEDStatus);

    // 向服务添加需上报属性
    ret = cJSON_AddItemToObject(servece, "properties", properties);
    if(ret == cJSON_True){
        printf("添加上报属性失败!\n");
    }

    ret;
    // 创建服务数组
    cJSON* servece_arr = cJSON_CreateArray();
    ret = cJSON_AddItemToArray(servece_arr, servece);
    if(ret == cJSON_True){
        printf("向服务数组添加名内容失败!\n");

    }

    // MedicinBox服务
    // MedicinIfo
    char* service_id = "MedicinBox";
    cJSON* service_id_obj = cJSON_CreateString(service_id);
    cJSON* servece2 = cJSON_CreateObject();

    ret = cJSON_AddItemToArray(servece_arr, servece2);
    ret = cJSON_AddItemToObject(root, "services", servece_arr);

    char* msg1 = cJSON_Print(root);
    return msg1;
}

// 主题发布成功回调函数
void DeliveryMsg(void *context, MQTTClient_deliveryToken dt){
    printf("publish topic success,token = %d \n", dt);
}

int main(){
    // 创建MQTT客户端
    MQTTClient client;
    printf("SERVER_URL: %s\n", SERVER_URL);
    printf("Client_ID: %s\n", Client_ID);
    int ret = MQTTClient_create(&client, SERVER_URL, Client_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    if(ret != MQTTCLIENT_SUCCESS){
        printf("创建MQTT客户端失败!\nret: %d\n", ret);
        exit(EXIT_FAILURE);
    }
    
    // 配置ssl证书
    MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
    ssl_opts.trustStore = "/home/chasedream/ca/huaweicloud-iot-root-ca-list.pem"; // 替换为你的实际路径

    // 创建并配置MQTT连接结构体
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.username = UserName;
    conn_opts.password = PassWord;
    conn_opts.keepAliveInterval = 60;   // 心跳时间
    conn_opts.cleansession = 1;         // 清除会话
    // conn_opts.ssl = &ssl_opts;

    // 设置MQTT连接的回调函数
    MQTTClient_setCallbacks(client, NULL, LostConnection, MsgArrived, DeliveryMsg);

    // 连接到MQTT服务器
    ret = MQTTClient_connect(client, &conn_opts);
    if(ret != MQTTCLIENT_SUCCESS){
        printf("MQTT服务器连接失败!\nret: %d\n", ret);
        exit(EXIT_FAILURE);
    }
    printf("MQTT服务器连接成功!\n");

    // printf("订阅主题: %s\n", topic_response);
    // printf("发布主题: %s\n", topic_get);

    // 发送数据
    // char* payload = needData();
    // int pub_ret = MQTTClient_publish(client, topic_report, strlen(payload), payload, QOS, 0, NULL);
    // if(pub_ret == MQTTCLIENT_SUCCESS){
    //     printf("属性上报成功！\n");
    // } else {
    //     printf("属性上报失败，错误码: %d\n", pub_ret);
    // }
    // free(payload); // 如果needData用的是cJSON_Print，记得释放
    

    int i = 0;
    while(1){
        // 1. 订阅影子响应主题
        int sub_ret = MQTTClient_subscribe(client, topic_response, QOS);
        // printf("订阅返回值: %d\n", sub_ret);

        // 2. 发布获取影子数据的请求
        int pub_ret = MQTTClient_publish(client, topic_get, strlen("{}"), "{}", QOS, 0, NULL);
        printf("发布返回值: %d\n", pub_ret);
        
        MQTTClient_yield();
        if(pub_ret == 0){
            break;
        }
        sleep(3);
        printf("\n等待%d秒\n", 3);
    }
    return 0;
}