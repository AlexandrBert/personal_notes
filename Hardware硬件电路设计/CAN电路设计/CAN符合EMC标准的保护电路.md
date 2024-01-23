# EMC 标准的 CAN 电路
参考文档：
- ADI ：
    - [电路笔记 CN-0313 - EMC COMPLIANT RS-485收发器保护电路](https://www.analog.com/media/cn/reference-design-documentation/reference-designs/CN0313_cn.pdf)
    - [AN-1161 应用笔记 - EMC兼容RS-485通信网络](https://www.analog.com/media/cn/technical-documentation/application-notes/AN-1161_cn.pdf)

## 1. CAN 标准
见 [CAN典型电路设计.md](./CAN典型电路设计.md#1-can-标准)

## 2. 电磁兼容性
见 [EMC设计简介.md](../EMC设计/EMC设计简介.md)

## 3. EMC 电路设计示例
EMC瞬变事件在时间上会有变化，因此保护元件必须具有动态性能，而且其动态特性需要与受保护器件的输入/输出极相匹配，这样才能实现成功的EMC设计。元件数据手册通常只包含直流数据，由于动态击穿和I/V特性可能与直流值存在很大差异，因此这些数据没有太多价值。必须进行精心设计并确定特性，了解受保护器件的输入/输出级的动态性能，并且使用保护元件，才能确保电路达到EMC标准。

CAN 总线电路的 EMC 设计方案可以参照 RS485：
[RS485符合EMC标准的保护电路.md #3-emc-电路设计示例](../RS485电路设计/RS485符合EMC标准的保护电路.md#3-emc-电路设计示例)
