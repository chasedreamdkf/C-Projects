#include<stdio.h>
#include<cjson/cJSON.h>
// #include<cjson/cJSON_Utils.h>

int main(){
    // printf("1111\n");
    cJSON* obj = cJSON_CreateObject();
    cJSON* num = cJSON_CreateNumber(100);
    cJSON_bool ret =  cJSON_AddItemToObject(obj, "num", num);
    if(ret == cJSON_True){
        printf("ret:%b\n", ret);
        printf("添加测试数字失败!\n");
    }

    int nums[] = {1, 2, 3, 4, 5};
    cJSON* arr = cJSON_CreateIntArray(nums, 5);
    ret =  cJSON_AddItemToObject(obj, "arr", arr);
    if(ret == cJSON_True){
        printf("ret:%b\n", ret);
        printf("添加数组失败!\n");
    }

    char* str = "Test data";
    cJSON* string = cJSON_CreateString(str);
    ret = cJSON_AddItemToObject(obj, "str", string);
    if(ret == cJSON_True){
        printf("添加测试字符串失败!\n");
    }

    char* s = cJSON_Print(obj);
    printf("%s\n", s);
    return 0;
}