# leds 设备树代码分析

## 1. 参考书籍目录
## 1.2 参考书籍目录
- linux 内核源码帮助文档（最快）： `Documentation/devicetree/bindings/clock/clock-bindings.txt`

### 1.2 参考章节
- devicetree/bindings/clock/clock-bindings

## 2. imx6ull 官方设备树节点展示
```dts
cpus {
	#address-cells = <1>;
	#size-cells = <0>;

	cpu0: cpu@0 {
		compatible = "arm,cortex-a7";
		...
		clocks = <&clks IMX6UL_CLK_ARM>,
			 <&clks IMX6UL_CLK_PLL2_BUS>,
			 <&clks IMX6UL_CLK_PLL2_PFD2>,
			 <&clks IMX6UL_CA7_SECONDARY_SEL>,
			 <&clks IMX6UL_CLK_STEP>,
			 <&clks IMX6UL_CLK_PLL1_SW>,
			 <&clks IMX6UL_CLK_PLL1_SYS>,
			 <&clks IMX6UL_PLL1_BYPASS>,
			 <&clks IMX6UL_CLK_PLL1>,
			 <&clks IMX6UL_PLL1_BYPASS_SRC>,
			 <&clks IMX6UL_CLK_OSC>;
		clock-names = "arm", "pll2_bus",  "pll2_pfd2_396m", "secondary_sel", "step",
			      "pll1_sw", "pll1_sys", "pll1_bypass", "pll1", "pll1_bypass_src", "osc";
	};
};

clocks {
	#address-cells = <1>;
	#size-cells = <0>;

	ckil: clock@0 {
		compatible = "fixed-clock";
		reg = <0>;
		#clock-cells = <0>;
		clock-frequency = <32768>;
		clock-output-names = "ckil";
	};

	osc: clock@1 {
		compatible = "fixed-clock";
		reg = <1>;
		#clock-cells = <0>;
		clock-frequency = <24000000>;
		clock-output-names = "osc";
	};

	ipp_di0: clock@2 {
		compatible = "fixed-clock";
		reg = <2>;
		#clock-cells = <0>;
		clock-frequency = <0>;
		clock-output-names = "ipp_di0";
	};

	ipp_di1: clock@3 {
		compatible = "fixed-clock";
		reg = <3>;
		#clock-cells = <0>;
		clock-frequency = <0>;
		clock-output-names = "ipp_di1";
	};
};

soc {
	...
	aips1: aips-bus@02000000 {
		...
		clks: ccm@020c4000 {
			compatible = "fsl,imx6ul-ccm";
			reg = <0x020c4000 0x4000>;
			interrupts = <GIC_SPI 87 IRQ_TYPE_LEVEL_HIGH>,
				     <GIC_SPI 88 IRQ_TYPE_LEVEL_HIGH>;
			#clock-cells = <1>;
			clocks = <&ckil>, <&osc>, <&ipp_di0>, <&ipp_di1>;
			clock-names = "ckil", "osc", "ipp_di0", "ipp_di1";
		};
	};
	...
};
```

## 3. Clock providers 属性
即上述示例中的 `clocks` 节点用到的属性。

必需的属性：
- `#clock-cells` ：时钟说明符中的单元数；对于具有单个时钟输出的节点，通常为 0，对于具有多个时钟输出的节点，通常为 1。

可选的属性：
- `clock-output-names`：建议作为时钟输出信号名称字符串的列表，由时钟说明符中的第一个单元格编制索引。但是，clock-output-names 的含义是特定于时钟提供程序的域，并且仅用于鼓励对大多数时钟提供程序使用相同的含义。 此格式可能不适用于使用复杂时钟说明符格式的时钟提供程序。 在这些情况下，建议省略此属性并创建绑定特定的 names 属性。时钟使用者节点绝不能直接引用提供程序的 clock-output-names 属性。

- `clock-indices` ：如果节点中时钟的标识号不是从零线性开始的，则允许将标识符映射到 `clock-output-names` 数组中。下面定义了两个时钟 <&oscillator 1> 和 <&oscillator 3> 。
	```dts
	oscillator {
		compatible = "myclocktype";
		#clock-cells = <1>;
		clock-indices = <1>, <3>;
		clock-output-names = "clka", "clkb";
	}
	```

## 4. Clock consumers 属性
必需属性：
- `clocks` ：phandle 和时钟说明符对的列表，每个时钟输入对应设备。 注意：如果时钟提供程序为 #clock 单元指定“0”，则只会显示该对的 phandle 部分。

可选属性：
- `clock-names` ：按与 clocks 属性相同的顺序排序的时钟输入名称字符串列表。使用者驱动程序将使用 clock-names 将时钟输入名称与时钟说明符进行匹配。
- `clock-ranges` ：空属性，指示子节点可以从此节点继承命名时钟。对于总线节点为其子节点提供时钟很有用。

## 5. clock 节点总结
由上述的每个属性的解释可以得出以下结论：
- `/clocks` 节点定义了四个时钟源，分别命名为 ckil（32768Hz）、osc（24MHz）、ipp_di0 和 ipp_di1。
- `/soc/aips1: aips-bus@02000000/clks: ccm@020c4000` 节点有四个父时钟源，其 `clocks` 属性使用了四个 phandle 指向 `/clocks` 节点定义的四个时钟源，CCM 模块的 "ckil" 时钟与 `/clocks/ckil` 时钟相连，"osc" 时钟与 `/clocks/osc` 时钟相连，"ipp_di0" 时钟与 `/clocks/ipp_di0` 时钟相连，"ipp_di1" 时钟与 `/clocks/ipp_di1` 时钟相连。

- `/cpus/cpu0: cpu@0` 节点中的 clocks 属性定义了 CPU 调用 CCM（时钟控制模块）的所有模式


32kHz 或 32.768kHz 晶振作为外部低频源（XTALOSC），进入 CCM 模块后被称为 CKIL，与 IPG_CLK 同步。

当系统处于功能模式时，CKIL与 ipg_clk 同步。

该芯片使用内部振荡器来生成参考时钟 （OSC）。内部振荡器连接到外部晶振（XTALOSC），外部晶振产生24 MHz参考时钟。

下面是芯片的一些 PLLs （锁相环，用来倍频）.
- PLL1 - ARM PLL (典型作用频率 )
- PLL2 - System PLL (作用频率 528 MHz)
- PLL3 - USB1 PLL (作用频率 480 MHz)
- PLL4 - Audio PLL
- PLL5 - Video PLL
- PLL6 - ENET PLL
- PLL7 - USB2 PLL (作用频率 480 MHz)

cpu 的根时钟选择
- `IMX6UL_CLK_ARM` ：使用PLL1 ARM时钟源
- `IMX6UL_CLK_PLL2_BUS` ：
- `IMX6UL_CLK_PLL2_PFD2` ：使用 PLL2 输出时钟，PFD2（Phase Fractional Dividers） 分频和门控后输出作为 CPU 时钟源；
- `IMX6UL_CA7_SECONDARY_SEL`
- `IMX6UL_CLK_STEP`
- `IMX6UL_CLK_PLL1_SW`
- `IMX6UL_CLK_PLL1_SYS`
- `IMX6UL_PLL1_BYPASS`
- `IMX6UL_CLK_PLL1`
- `IMX6UL_PLL1_BYPASS_SRC`
- `IMX6UL_CLK_OSC` ：osc_clk，24MHz 外部晶振。
