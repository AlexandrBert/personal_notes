# **C语言高级用法：** #


----------


## 1. container of() 宏定义
### 2.1 定义原型
```c
/* @include ：内核版本4.4源码存放位置在 include/linux/stddef.h 文件中
 * @func ：获取结构体类型 TYPE 中的成员 MEMBER 的相对地址，地址0表示指向结构体起始地址。
 */

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

/* 内核版本4.4源码存放位置在 include/linux/kernel.h 文件中
 * @func ：从 ptr 指向的 type 类型的结构体成员 member 的指针地址获取 type 类型结构体指针的地址。即利用成员地址获取源结构体地址。
 * @param ptr : 指向结构体变量的指针
 * @param type : 结构体类型
 * @param member : 结构体变量中某个成员的名字
 * @return : 返回结构体变量中某个成员的地址。（返回代码块的最后一条语句的值）
 */
#define container_of(ptr, type, member) ({				\
	void *__mptr = (void *)(ptr);					\
	BUILD_BUG_ON_MSG(!__same_type(*(ptr), ((type *)0)->member) &&	\
			 !__same_type(*(ptr), void),			\
			 "pointer type mismatch in container_of()");	\
	((type *)(__mptr - offsetof(type, member))); })

/* 旧版内核版本 4.1.15 写法，源码存放位置在 include/linux/kernel.h 文件中 */
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
```

### 2.2 用法示例
根据结构体中的成员 dev 的地址获取结构体的地址。
```c
struct led_chrdev {
    struct cdev dev;
    ...,
    unsigned int clock_offset;
};

struct led_chrdev *led_cdev =
        (struct led_chrdev *)container_of(inode->i_cdev, struct led_chrdev, dev);
```