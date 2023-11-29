# leds 设备树代码分析

## 1. 参考书籍目录
## 1.2 参考书籍目录
- 设备树官网说明书(DeviceTree Specification)：[https://www.devicetree.org/specifications/](https://www.devicetree.org/specifications/)
- 设备树 Github 地址：[https://github.com/devicetree-org/devicetree-specification/releases/tag/v0.4](https://github.com/devicetree-org/devicetree-specification/releases/tag/v0.4)
- DeviceTree Specification 中文翻译博客：[https://blog.csdn.net/OnlyLove_/article/details/121963868](https://blog.csdn.net/OnlyLove_/article/details/121963868)
- linux 内核源码帮助文档（最快）： `Documentation/devicetree/bindings/arm/cpus.txt`

### 1.2 参考章节
- 3.7 /cpus Node Properties
- 3.8 /cpus/cpu* Node Properties

## 2. imx6ull 官方 `/cpus/cpu` 设备树节点展示
```dts
cpus {
	#address-cells = <1>;
	#size-cells = <0>;

	cpu0: cpu@0 {
		compatible = "arm,cortex-a7";
		device_type = "cpu";
		reg = <0>;
		clock-latency = <61036>; /* two CLK32 periods */
		operating-points = <
			/* kHz	uV */
			996000	1275000
			792000	1225000
			528000	1175000
			396000	1025000
			198000	950000
		>;
		fsl,soc-operating-points = <
			/* KHz	uV */
			996000	1175000
			792000	1175000
			528000	1175000
			396000	1175000
			198000	1175000
		>;
		fsl,low-power-run;
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
```

## 3. /cpus 节点属性
所有设备树都需要一个 /cpus 节点。它并不代表系统中的真实设备，而是充当代表系统 CPU 的子 CPU 节点的容器。

- `#address-cells` ：必需属性，U32。指定 reg 属性数组的每个元素在此节点的子节点中占用 1 个单元格。
- `#size-cells` ：必需属性，U32。指定在此节点的子节点的 reg 属性中不需要大小。

**注意：**  /cpus 节点中，所有其他标准属性都是可选的，也是允许使用的，如 `compatible、model、phandle、status、reg、virtual-reg、ranges、dma-ranges、dma-coherent、dma-noncoherent、name (deprecated)、device_type (deprecated)` 。

## 4. /cpus/cpu* 节点属性
一个 cpu 节点代表一个足够独立的硬件执行块，它能够运行操作系统而不会干扰可能运行其他操作系统的其他 CPU。

共享一个 MMU 的硬件线程通常表示在一个 cpu 节点下。如果设计了其他更复杂的 CPU 拓扑，则 CPU 的绑定必须描述拓扑（例如，不共享 MMU 的线程）。

CPU 和线程通过统一的数字空间进行编号，该空间应尽可能匹配中断控制器的 `CPUs/threads` 编号。

跨 cpu 节点具有相同值的属性可能会被放置在 /cpus 节点中。客户端程序必须首先检查特定的 cpu 节点，但如果未找到预期的属性，则应查看父 /cpus 节点。这导致在所有 CPU 上都相同的属性的更详细的表示。

每个 CPU 节点的节点名称应为 cpu。

### 4.1 /cpus/cpu* 节点的常规属性

这里仅展示当前 imx6ull 示例中用到的 /cpus/cpu* 节点的常规属性：

- `device_type` ：必需属性， string 。必需设为 `"cpu"` 。

- `reg` ：必需属性， array 。reg 的值是一个 `<prop-encoded-array>` ，它为 CPU 节点所代表的 `CPU/threads` 定义了一个唯一的 `CPU/thread` id。如果 CPU 支持多个线程（即多个执行流），则 reg 属性是一个数组，其中每个线程有 1 个元素。 `/cpus` 节点上的 `#address-cells` 指定数组的每个元素需要多少个单元。软件可以通过将 `reg` 的大小除以父节点的 `#address-cells` 来确定线程数。如果 `CPU/threads` 可以成为外部中断的目标，则 `reg` 属性值必须是可由中断控制器寻址的唯一 `CPU/threads` ID。如果 `CPU/threads` 不能成为外部中断的目标，则 `reg` 必须是唯一的并且超出中断控制器寻址的范围。如果 `CPU/threads` 的 PIR（挂起中断寄存器）是可修改的，则客户端程序应修改 PIR 以匹配 reg 属性值。如果无法修改 PIR 并且 PIR 值与中断控制器编号空间不同，则 CPU 绑定可以根据需要定义 PIR 值的绑定特定表示。

- `clock-frequency` ：可选属性， array 。如果可用，则表示 CPU 节点的时钟频率。
	- 一个 32 位整数，由一个组成，指定频率。
	- 一个 64 位整数，表示为指定频率。

### 4.2 其他属性

- `compatible` ：可选属性，string 。描述了节点兼容属性。

- `operating-points` : 可选属性，array 。一个 2 元组项的数组，每项由频率和电压组成，如 `<freq-kHz vol-uV>` 。SoC 具有一组标准的元组，由频率和电压对组成，设备将支持每个电压域。这些称为操作绩效点或 OPP。在内核文件 `Documentation/devicetree/bindings/power/opp.txt` 中有使用示例。
	- freq: clock frequency in kHz 。
	- vol: voltage in microvolt

- `fsl,soc-operating-points` ：可选属性，array 。用于调用驱动文件 `drivers/cpufreq/imx6q-cpufreq.c` ，启用 imx6 系列芯片的 opp 功能让 cpu 可以工作在不同频率。

- `fsl,low-power-run` ：用于启用 imx6 系列芯片的 24MHz 的低功耗运行模式。驱动文件 `drivers/cpufreq/imx6q-cpufreq.c` 中的 `imx6q_cpufreq_probe` 函数。

### 4.3 clock 属性
- `clocks` ：phandle 和时钟说明符对的列表，每个时钟输入对应设备。 注意：如果时钟提供程序为 #clock 单元指定“0”，则只会显示该对的 phandle 部分。

- `clock-names` ：按与 clocks 属性相同的顺序排序的时钟输入名称字符串列表。使用者驱动程序将使用 clock-names 将时钟输入名称与时钟说明符进行匹配。

设备树中 `clock` 的相关属性有：
- 必选属性：`clocks`
- 可选属性：`clock-names`/`clock-ranges` 。

内核帮助文档目录在 `Documentation/devicetree/bindings/clock/clock-bindings.txt` 。

