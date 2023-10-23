# LED 驱动编写
LED 的驱动实际就是控制 GPIO 输出一个高低电平。

## 1. 编写 LED 驱动
## 1.1 GPIO 相关函数
GPIO 相关函数在 `include/linux/gpio.h` 文件中，具体如下：
- GPIO 申请： `int gpio_request(unsigned int gpio, const char *label)`
- GPIO 初始化： `int gpio_direction_output(unsigned int gpio, int value)`
- GPIO 输出电平： `int gpio_set_value(unsigned int gpio, int value)`
- GPIO 释放： `void gpio_free(unsigned int gpio)`

