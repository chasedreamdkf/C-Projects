#include <stdio.h>
#include <cjson/cJSON.h>

int main(){
    // 创建数据根
    cJSON* root = cJSON_CreateObject();
    // 创建服务
    cJSON* servece = cJSON_CreateObject();
    // 添加服务id
    char* servece_id = "NECcontrol";
    cJSON* servece_id_obj = cJSON_CreateString(servece_id);
    int ret = cJSON_AddItemToObject(servece, "service_id", servece_id_obj);
    if(ret == cJSON_True){
        printf("为\"%s\"服务添加服务id失败!\n", servece_id);
    }
    // 创建需要上报的属性对象
    cJSON* properties = cJSON_CreateObject();
    // 向属性对象添加内容
    cJSON* AirConditionT = cJSON_CreateString("30");
    cJSON* AirConditionStatus = cJSON_CreateString("OFF");
    cJSON* WindowsStatus = cJSON_CreateString("ON");
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

    ret = cJSON_AddItemToObject(root, "services", servece_arr);

    char* msg1 = cJSON_Print(root);
    printf("msg1:\n%s\n", msg1);

    // 解析json字符串
    cJSON* root_data =  cJSON_Parse(msg1);

    cJSON* data = cJSON_GetObjectItem(root_data, "services");
    cJSON* data2 = cJSON_GetArrayItem(data, 0);
    char* msg2 = cJSON_Print(data2);
    printf("msg2:\n%s\n", msg2);

    return 0;
}

/**
 * {
  "services": [
    {
      "service_id": "NECcontrol",
      "properties": {
        "AirConditionT": "28",
        "AirConditionStatus": "OFF",
        "WindowsStatus": "ON",
        "TrunkStaus": "ON",
        "CarLockStaus": "ON",
        "LEDStatus": "OFF"
      }
    }
  ]
 */