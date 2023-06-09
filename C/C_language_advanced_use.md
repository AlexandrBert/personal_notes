# **C语言高级用法：** #


----------


## 宏定义 ##

### #、##的使用 ###

> `#define    ABC(x)    #x    //字符串化`
> 
> `#define    ABC(x，y)    x##y   //连接符号替换`

**#** 是在预处理阶段实现字符串化，将字符串加上双引号。

**##** 是在预处理阶段实现字符串的连接，可以将两个字符粘连起来，例如上述实例中如果在程序中使用 `int ABC(date,1);` 在预处理时会将其替换为 `int date1;` ，提高了代码的灵活性。


----------


## 省略符号： ##

在C语言中会见到下面的用法：

    int printf (const char *__format, ...);

省略号告诉编译器，在函数调用时不检查形参类型是否与实参类型相同，也不检查参数个数。编译器只检查第一个参数是否为 `const char *` ，而不对其他参数进行检查。

上述用法一般用于需要用到可变参数的函数，对于可变参数的函数，需要进行特殊的处理。首先需要引用 `<stdarg.h>` 头文件，然后利用 `va_list` 类型和 `va_start` 、`va_arg` 、`va_end` 3个宏读取传递到函数中的参数值。

	void va_start( va_list arg_ptr, prev_param ); 
	type va_arg( va_list arg_ptr, type );
	void va_end( va_list arg_ptr );

 `va_start` 函数将参数 `arg_ptr` 设置为可变参数列表的第一个参数。参数 `arg_ptr` 的类型必须为 `va_list`。参数 `prev_param` 是在可变参数列表之前的那一个参数。也就是说在 ANSI C 中，如果一个函数有可变参数，那么在该可变参数前必须有一个明确定义的参数，否则无法调用函数 `va_start` ，例如函数 `int add(int i,...）` 是合法的，而函数 `int add(...)`是不合法的。

`va_arg` 函数将返回 `arg_ptr` 所指位置的值，并将 `arg_ptr` 指向下一个参数。

`va_end` 函数的作用是在所有参数被回收后将用到的指针指向NULL。

下面为一个用该方法实现了一个返回多个数相加结果的函数：

    //gcc 7.4.0
    
    #include  <stdio.h>
    #include <stdarg.h>
    
    int add(int pre,...)  //求和函数
    {
    va_list arg_ptr;
    
    int sum=0;
    int nArgValue;
    
    sum+=pre;
    
    va_start(arg_ptr,pre);
    do
    {
    nArgValue=va_arg(arg_ptr,int);
    sum+=nArgValue;
    
    }while(nArgValue!=0);   //自定义结束条件是输入参数为0
    
    va_end(arg_ptr);
    
    return sum;
    }
    
    int main()
    {
       printf("%d\n",add(1,2,3,0));  //必须以0结尾，因为参数列表结束的判断条件是读到0停止
       return 0;
    }

返回结果为：

    Compilation time: 0.12 sec, absolute running time: 0.15 sec, cpu time: 0.01 sec, memory peak: 5 Mb, absolute service time: 0,35 sec
    6

----------
