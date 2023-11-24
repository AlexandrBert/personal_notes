# Linux 设备树

Linux内核从3.x开始引入设备树的概念，实现驱动代码与设备信息相分离。 设备树用于描述一个硬件平台的硬件资源。这个“设备树”可以被bootloader(uboot)传递到内核， 内核可以从设备树中获取硬件信息。

第一，以“树状”结构描述硬件资源。例如本地总线为树的“主干”在设备树里面称为“根节点”， 挂载到本地总线的IIC总线、SPI总线、UART总线为树的“枝干”在设备树里称为“根节点的子节点”， IIC 总线下的IIC设备不止一个，这些“枝干”又可以再分。

第二，设备树可以像头文件（.h文件）那样，一个设备树文件引用另外一个设备树文件， 这样可以实现“代码”的重用。例如多个硬件平台都使用i.MX6ULL作为主控芯片， 那么我们可以将i.MX6ULL芯片的硬件资源写到一个单独的设备树文件里面一般使用“.dtsi”后缀， 其他设备树文件直接使用“# includexxx”引用即可。

## 设备树文件格式
DTS 是指.dts格式的文件，是一种ASII 文本格式的设备树描述，也是我们要编写的设备树源码，一般一个.dts文件对应一个硬件平台，位于Linux源码的“/arch/arm/boot/dts”目录下。

DTSI 是指由NXP官方提供，是一个imx6ull平台“共用”的设备树文件。

DTC 是指编译设备树源码的工具，一般情况下我们需要手动安装这个编译工具。

DTB 是设备树源码编译生成的文件，类似于我们C语言中“.C”文件编译生成“.bin”文件。

DTBO 是设备树叠加层编译生成的文件，可以对DTB进行叠加补充。

## 设备树源码展示

设备树文件在内核源码 `/arch/arm/boot/dts/` 目录中， 其中imx6ull-mmc-npi.dts和imx6ull-nand-npi.dts分别为野火imx6ull的emmc和nand核心板使用的主设备树文件。

```dts
 #include <dt-bindings/input/input.h>
 #include "imx6ull.dtsi"

 / {
     model = "Seeed i.MX6 ULL NPi Board";
     compatible = "fsl,imx6ull-14x14-evk", "fsl,imx6ull";

     aliases {
             pwm0 = &pwm1;
             pwm1 = &pwm2;
             pwm2 = &pwm3;
             pwm3 = &pwm4;
     };
     chosen {
             stdout-path = &uart1;
     };

     memory {
             reg = <0x80000000 0x20000000>;
     };

     /*-------------以下内容省略-------------*/
 };

 &cpu0 {
     dc-supply = <&reg_gpio_dvfs>;
     clock-frequency = <800000000>;
 };

 &clks {
     assigned-clocks = <&clks IMX6UL_CLK_PLL4_AUDIO_DIV>;
     assigned-clock-rates = <786432000>;
 };

 /*-------------以下内容省略--------------*/
```

1. imx6ull.dtsi 文件由NXP官方提供，这是一个imx6ull平台“共用”的设备树文件(用于外设基地址定义之类的内容)。 可直接使用include包含。

2. “/{……}”为设备树的根节点(可想象为树干)，每个设备树只有一个根节点。

3. “aliases {…}、chosen {…}、memory {…}” 为根节点的子节点(树枝); 除此之外，在子节点下还能包含各种子节点(“设备树”正在茁壮成长)。

4. “&cpu0{……}”表示直接引用cpu0节点，向并向其中添加/修改新的属性信息，这些存在的节点 可能定义在在“ imx6ull-mmc-npi.dtb / imx6ull-nand-npi.dtb ”文件， 也可能定义在“imx6ull.dtsi”文件所包含的设备树文件里