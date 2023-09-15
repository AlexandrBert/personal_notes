# cJSON 的使用

JSON是一种轻量级的数据交换格式，可读性强、编写简单。键值对组合编写规则，键名使用双引号包裹，冒号：分隔符后面紧跟着数值，有两种常用的数据类型是对象和数组。

对象：使用花括号 { } 包裹起来的内容，数据结构 {"key1": "value1", "key2":"value2" ......}，key为对象的属性，value 为对象的值。

数值：使用中括号 [ ] 包裹起来的内容，数据结构 {"key": ["value1", "value2", "value3" ......]} 。

```json
1. {"name": "JSON"}
2. {"object": "student",
    "info": [
         {
             "name": "lily",
             "age": 20 
         },
         {
              "name":"luci",
              "age":23
          }
       ]
    }
```

## cJSON 安装及函数

1. 下载开源库源码，[GitHub地址](https://github.com/DaveGamble/cJSON) 。
2. 解压并安装到库环境中，交叉编译环境需要交叉编译器编译，并将安装路径下的 lib 放到目标机文件系统。
    ```bash
        tar -xvf cJSON-1.3.2.tar.gz
        cd cJSON-1.3.2
        sudo make
        sudo make install
        idconfig
    ```

## 库函数介绍

### 创建函数
```C
函数：extern cJSON *cJSON_CreateObject(void)
用法：创建JSON结构对象

函数：extern cJSON *cJSON_CreateNumber(double num)
用法：创建一个整型的数据类型

函数：extern cJSON *cJSON_CreateString(const char *string)
用法：创建一个字符串数据类型

函数：extern cJSON *cJSON_CreateArray(void)
用法：创建一个数组数据类型函数：

cJSON *cJSON_CreateIntArray(const int *numbers, int count)
用法：将多个整型数据类型增加到数组中
```

### 解析函数
```C
函数：extern cJSON *cJSON_Parse(const char *value)
用法：从JSON文件数据缓冲区解析JSON的对象结构，使用完成后要必须要释放对象结构
```

### 打印
```C
函数：extern char *cJSON_Print(cJSON *item)
用法：将传入JSON结构对象转换为字符串
```

### 释放
```C
函数：void cJSON_Delete(cJSON *c)
用法：释放申请的JSON结构缓存空间
```

### 添加
```C
函数：void cJSON_AddItemToArray(cJSON *array, cJSON *item)
用法：将数组增加到JSON对象中

函数：void cJSON_AddItemToObject(cJSON *json, cJSON *, cJSON_CreateArray())
用法：向对象中增加对象

函数：void cJSON_AddItemToArray(cJSON *array, cJSON *item)
用法：向数组中增加对象
```

### 获取
```C
函数：extern cJSON *cJSON_GetObjectItem(cJSON *object, const char *string)
用法：根据键名在JSON中查找子节点

函数：extern int cJSON_HasObjectItem(cJSON *object, const char *string)
用法：判断JSON对象是否包含键名string。

函数：extern int cJSON_GetArraySize(cJSON *array)
用法：获取数组的大小

函数：extern cJSON *cJSON_GetArrayItem(cJSON *array, int index)
用法：在数组查找指定下标的节点对象
```
