# U-Boot 启动流程

uboot 的启动分为两个阶段：
stage1 ：通常是开发板的配置等设备初始化代码，需要依赖SOC体系结构，通常用汇编语言实现；
stage2 ：主要是对外部设备如网卡、Flash等的初始化以及 uboot 命令集等的自身实现，通常用C语言实现，这样可以实现复杂的功能，而且有更好的可读性和移植性。

## stage1 （start.S代码结构）

uboot 的 stage1 代码通常放在 start.S文件中，该文件位于uboot/arch/arm/cpu/armv7/start.S，用汇编语言编写，其主要代码部分如下：
1. 定义入口。系统复位转入 uboot 的 stage1 入口点，通常这个入口放在 rom（falsh） 的 0x00 地址，因此，必须通知编译器以使其知道这个入口，该工作可通过修改连接器脚本来完成。
2. 设置异常向量。
3. 设置 CPU 的速度、时钟频率及终端控制寄存器。
4. 初始化内存控制器，为 stage2 准备 RAM 空间。
5. 将 uboot 的 stage2 拷贝到 RAM 中。
6. 初始化堆栈、数据段。
7. 转到 stage2 的入口点。

### 1. _start

**_start** : `arch/arm/lib/vector.S`

_start 是 uboot 启动后的第一个执行地址。对于任何程序，入口函数是在链接时决定的，uboot 的入口是由链接脚本决定的。uboot 下链接脚本默认目录为：`arch/arm/cpu/u-boot.lds` .

```S
#ifdef CONFIG_SYS_DV_NOR_BOOT_CFG
	.word	CONFIG_SYS_DV_NOR_BOOT_CFG
#endif
    # 跳转到不同架构文件夹中的 start.S 文件中的 reset
	b	reset
    # 下面是异常向量的地址
	ldr	pc, _undefined_instruction
	ldr	pc, _software_interrupt
	ldr	pc, _prefetch_abort
	ldr	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
	ldr	pc, _fiq
```

### 2. reset

#### **reset** : `arch/arm/armv7/start.S`

在上电或者重启后，处理器取得的第一次条指令（_start）就是： b	reset ，所以会直接跳转到 reset 函数处。reset 首先跳转到 save_boot_params 函数，保存一些启动参数，然后跳转到 cpu_init_crit 函数。

执行完 cpu_init_cp15 、cpu_init_crit ，最后跳转到 _main 。

```S
	.globl	reset
	.globl	save_boot_params_ret

reset:
	/* Allow the board to save important registers */
	b	save_boot_params
save_boot_params_ret:
	/*
	 * disable interrupts (FIQ and IRQ), also set the cpu to SVC32 mode,
	 * except if in HYP mode already
	 */
	mrs	r0, cpsr
	and	r1, r0, #0x1f		@ mask mode bits
	teq	r1, #0x1a		@ test for HYP mode
	bicne	r0, r0, #0x1f		@ clear all mode bits
	orrne	r0, r0, #0x13		@ set SVC mode
	orr	r0, r0, #0xc0		@ disable FIQ and IRQ
	msr	cpsr,r0
/*
 * Setup vector:
 * (OMAP4 spl TEXT_BASE is not 32 byte aligned.
 * Continue to use ROM code vector only in OMAP4 spl)
 */
#if !(defined(CONFIG_OMAP44XX) && defined(CONFIG_SPL_BUILD))
	/* Set V=0 in CP15 SCTLR register - for VBAR to point to vector */
	mrc	p15, 0, r0, c1, c0, 0	@ Read CP15 SCTLR Register
	bic	r0, #CR_V		@ V = 0
	mcr	p15, 0, r0, c1, c0, 0	@ Write CP15 SCTLR Register

	/* Set vector address in CP15 VBAR register */
	ldr	r0, =_start
	mcr	p15, 0, r0, c12, c0, 0	@Set VBAR
#endif

	/* the mask ROM code should have PLL and others stable */
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	bl	cpu_init_cp15
	bl	cpu_init_crit
#endif

	bl	_main
```

#### **cpu_init_cp15** : `arch/arm/armv7/start.S`

cp15 是协处理器，该函数是配置 cp15 协处理器相关寄存器来设置处理器的 MMU , cache 以及 TLBs 等。

```S
/*************************************************************************
 *
 * cpu_init_cp15
 *
 * Setup CP15 registers (cache, MMU, TLBs). The I-cache is turned on unless
 * CONFIG_SYS_ICACHE_OFF is defined.
 *
 *************************************************************************/
ENTRY(cpu_init_cp15)

...

ENDPROC(cpu_init_cp15)
```

#### **cpu_init_crit** : `arch/arm/armv7/start.S`

```S
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
/*************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************/
ENTRY(cpu_init_crit)
	/*
	 * Jump to board specific initialization...
	 * The Mask ROM will have already initialized
	 * basic memory. Go here to bump up clock rate and handle
	 * wake up conditions.
	 */
    # 跳转到 lowlevel_init 函数
	b	lowlevel_init		@ go setup pll,mux,memory
ENDPROC(cpu_init_crit)
#endif
```

#### **lowlevel_init** : `arch/arm/armv7/lowlevel_init.S`

lowlevel_init 函数是特定开发板相关的初始化函数，会做一些 pll 、 pinmux 、 memory 初始化，方便后续拷贝到 memory 中运行。

```S
NTRY(lowlevel_init)
...
    # 跳转到跟开发板相关的 s_init 函数，如 arch/arm/armv7/mx6/soc.c 中的 s_init
	bl	s_init
	pop	{ip, pc}
ENDPROC(lowlevel_init)
```

#### **s_init** : `arch/arm/armv7/mx6/cpu.c`

执行完 s_init 函数后会跳回到 start.S 并跳转到 _main 函数地址。

```c
void s_init(void)
{

}
```

### 3. _main

这个段汇编主要作用是：
- 初始化一个C语言能够运行的环境
- bl board_init_f
- 设置堆栈地址
- 设置全局变量 gd 结构体
- 中断向量表的重映射
- 未初始化段（bss）的清除
- 最后调用 ldr pc, =board_init_r 函数，跳转到 uboot 的第二阶段。

**_main**: `arch/arm/lib/crt0.S`
```S
ENTRY(_main)
    ...
    bl	board_init_f
    ...
    b	relocate_code
    ...
    b	board_init_r
    ...
ENDPROC(_main)
```

#### 3.1 **board_init_f**: `common/board_f.c`

调用 init_sequence_f[] 数组中的函数，完成一些前期的初始化工作，例如：
- 点亮一个 Debug 用的 LED 灯，表示 uboot 已经启动。
- 初始化 DRAM、DDR等。
- 初始化调试串口。
- 打印 CPU 信息等。

```c
/* 需要初始化的函数地址 */
static init_fnc_t init_sequence_f[] = {
#ifdef CONFIG_SANDBOX
	setup_ram_buf,
#endif
	setup_mon_len,
    ...
    board_early_init_f,
    ...
}

void board_init_f(ulong boot_flags)
{
#ifdef CONFIG_SYS_GENERIC_GLOBAL_DATA
	/*
	 * For some archtectures, global data is initialized and used before
	 * calling this function. The data should be preserved. For others,
	 * CONFIG_SYS_GENERIC_GLOBAL_DATA should be defined and use the stack
	 * here to host global data until relocation.
	 */
	gd_t data;

	gd = &data;

	/*
	 * Clear global data before it is accessed at debug print
	 * in initcall_run_list. Otherwise the debug print probably
	 * get the wrong vaule of gd->have_console.
	 */
	zero_global_data();
#endif

	gd->flags = boot_flags;
	gd->have_console = 0;

	if (initcall_run_list(init_sequence_f))
		hang();

#if !defined(CONFIG_ARM) && !defined(CONFIG_SANDBOX) && \
		!defined(CONFIG_EFI_APP)
	/* NOTREACHED - jump_to_copy() does not return */
	hang();
#endif
}
```

#### 3.1.1 **board_early_init_f**：`arch/arm/cpu/armv7/am33xx/board.c` 或 `board/freescale/mx6ullevk/mx6ullevk.c`

主要用来初始化功能模块的引脚，初始化完成返回 board_init_f ， board_init_f 函数完成返回到 _main 函数。

```c
/* 以下为 arch/arm/cpu/armv7/am33xx/board.c 中的该函数 */
/*
 * In the case of non-SPL based booting we'll want to call these
 * functions a tiny bit later as it will require gd to be set and cleared
 * and that's not true in s_init in this case so we cannot do it there.
 */
int board_early_init_f(void)
{
	int ret;
	prcm_init();

/* 开始行：以下这段代码为根据标准代码新增的 LED 灯初始化代码 */
	set_mux_conf_regs();

	/* LED_SOM_D2 is indicator for SPL to work on TL BOARD */
	ret = gpio_direction_output(GPIO_LED_SOM_D2, 1);
	if (ret < 0)
		printf("%s: gpio %d request failed %d\n", __func__,
							GPIO_LED_SOM_D2, ret);
/* 截至行 */

#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_RTC_ONLY_SUPPORT)
	update_rtc_magic();
#endif
	return 0;
}
```

#### 3.2 **relocate_code**: `arch/ram/lib/relocate.c`

代码重定位，无论从哪里启动， uboot 运行后将自身代码拷贝到 sdram 的另一个位置继续运行。旧版 uboot 会通过判断 _start 和 TEXT_BASE 是否相等来判断是否需要重定位。

```S
ENTRY(relocate_code)
    ...
ENDPROC(relocate_code)
```

执行完成该函数后，返回 _main 函数，继续执行跳转到 board_init_r 函数进入 stage2。

## stage2 

### **board_init_r**

调用 init_sequence 函数，完成第二阶段的初始化工作。包括 nand flash 的初始化，spi flash 等等设备初始化。其中 board_init 函数是特定开发板相关的初始化函数。

**board_init_r** : common/board_r.c  
**board_init** : board/ti/am335x/board.c

```c
/* common/board_r.c */
init_fnc_t init_sequence_r[] = {
	initr_trace,
	initr_reloc,
    ...,
    board_init,
    ...
    run_main_loop,
}

void board_init_r(gd_t *new_gd, ulong dest_addr)
{
#ifdef CONFIG_NEEDS_MANUAL_RELOC
	int i;
#endif

#ifdef CONFIG_AVR32
	mmu_init_r(dest_addr);
#endif

#if !defined(CONFIG_X86) && !defined(CONFIG_ARM) && !defined(CONFIG_ARM64)
	gd = new_gd;
#endif

#ifdef CONFIG_NEEDS_MANUAL_RELOC
	for (i = 0; i < ARRAY_SIZE(init_sequence_r); i++)
		init_sequence_r[i] += gd->reloc_off;
#endif

	if (initcall_run_list(init_sequence_r))
		hang();

	/* NOTREACHED - run_main_loop() does not return */
	hang();
}

/* board/ti/am335x/board.c */
int board_init(void)
{
#if defined(CONFIG_HW_WATCHDOG)
	hw_watchdog_init();
#endif

	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;
#if defined(CONFIG_NOR) || defined(CONFIG_NAND)
	gpmc_init();
#endif

#if !defined(CONFIG_SPL_BUILD) || \
	(defined(CONFIG_SPL_ETH_SUPPORT) && defined(CONFIG_SPL_BUILD))
	if (board_is_icev2()) {
		int rv;
		u32 reg;

        ...;

		reg = readl(GPIO0_IRQSTATUSRAW) & BIT(11);
		if (reg) {
			writel(reg, GPIO0_IRQSTATUS1); /* clear irq */
			/* RMII mode */
			printf("ETH0, CPSW\n");
			eth0_is_mii = false;
		} else {
			/* MII mode */
			printf("ETH0, PRU\n");
			cdce913_data.pdiv3 = 4;	/* 25MHz PHY clk */
		}

        ...
	}
#endif

	return 0;
}
```

### **run_main_loop**

**run_main_loop**: `common/board_r.c`

```c
/* common/main.c */
void main_loop(void)
{
	const char *s;

    /* 用来标记 uboot 运行状态 */
	bootstage_mark_name(BOOTSTAGE_ID_MAIN_LOOP, "main_loop");

#ifndef CONFIG_SYS_GENERIC_BOARD
	puts("Warning: Your board does not use generic board. Please read\n");
	puts("doc/README.generic-board and take action. Boards not\n");
	puts("upgraded by the late 2014 may break or be removed.\n");
#endif

#ifdef CONFIG_VERSION_VARIABLE
	setenv("ver", version_string);  /* set version variable */
#endif /* CONFIG_VERSION_VARIABLE */

	cli_init();

	run_preboot_environment_command();

#if defined(CONFIG_UPDATE_TFTP)
	update_tftp(0UL, NULL, NULL);
#endif /* CONFIG_UPDATE_TFTP */

    /* 把环境变量 bootcmd 获取出来，最后将 bootcmd 的内容返回上层到 s */
	s = bootdelay_process();
	if (cli_process_fdt(&s))
		cli_secure_boot_cmd(s);

    /* autoboot_command() -> abortboot() -> abortboot_nomal() -> run_command_list() -> parse_stream_outer() 自启模式 */
    /* 其中包含判断是否由按键按下，即是否需要切换到命令行模式，环境变量中的bootdelay关系到此函数的 cmd 打断延迟时间 */
	autoboot_command(s);

    /* cli_loop() -> parse_file_outer() -> parse_stream_outer(); UBOOT 的命令模式 */
	cli_loop();
	panic("No CLI available");
}

/* common/board_r.c */
static int run_main_loop(void)
{
#ifdef CONFIG_SANDBOX
	sandbox_main_loop_init();
#endif
	/* main_loop() can return to retry autoboot, if so just run it again */
	for (;;)
		main_loop();
	return 0;
}
```

main_loop 中的函数涉及的部分函数如下：
- common/cli_hush.c -> parse_stream_outer()
- common/cli_hush.c -> run_list()
- common/cli_hush.c -> run_list_real()
- common/cli_hush.c -> run_pipe_real()
- common/command.c -> cmd_process()
- common/command.c -> cmd_call()

### **cmd_call**

cmd_call() 通过一个 cmd_tbl_t 结构，并调用其中一个函数指针进行对实际命令的调用。 uboot 的命令位于根目录下的 cmd/ 中。

**旧版 uboot 命令源码在 common/ 中，每个命令都以 “cmd_” 开头的 c 文件形式存在。**


