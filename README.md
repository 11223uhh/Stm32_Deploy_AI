# STM32 Deploy AI

[English](README_EN.md) | [中文](README_zh.md) | [日本語](README_ja.md) | [한국어](README_ko.md)

**本项目基于 ARM CMSIS-NN 库进行开发，提供了优化和扩展功能的实践实现。包含了精简版的 NN 库，并支持在微控制器上运行 OpenCV 1.0。欢迎提出问题和贡献代码！**

## ✨ 特性

* 🚀 在微控制器上部署量化后的 MXNet 模型
* 📊 提供仿真平台：
  * 运行时数据分析
  * 精度评估
  * RAM/ROM 使用估算
* 🎨 集成 OpenCV 1.0 基础功能：
  * 图像缩放
  * 灰度转换
  * 边缘检测
  * 霍夫变换
  * 图像腐蚀和膨胀
* 👁️ 神经网络逐层输出可视化
* 🔧 支持 VGG 架构（即将支持：ResNet、NiN、GoogLeNet、MobileNet）
* 📝 提供完整示例代码
* 🔄 使用 CMSIS-NN 基础函数，易于移植

## 🛠️ 环境要求

### Python 环境

```python
mxnet-cu100    == 1.5.0 
d2lzh          == 1.0.0
opencv-python  == 4.5.4.60
Pillow         == 8.4.0
```

> **注意**：以上版本经过测试可用。其他版本可能也兼容。如使用其他深度学习框架（如 Keras）可能需要额外配置。

### STM32 硬件要求

* 开发板：STM32F407ZGT6（其他型号可能需要适配）
* 显示：TFT 屏幕
* 编程器：ARM 模拟器/调试器（或兼容编程器）

> **推荐**：可以考虑购买 STM32F4mini Discovery 开发板（包含屏幕，使用 F407ZGT6 芯片）。项目同时提供 STM32 和 Arduino 示例（Arduino 不支持 OpenCV）。

## 📚 示例

### STM32 示例

1. Example1：使用 ARM CMSIS-NN 库的 MNIST 数字识别（内置图像）
2. Example2：使用 TensorFlow Lite 的正弦波拟合（带显示输出）
3. Example3：通过 Nucleo-STM32 UART 的图像识别（带计时）

### Arduino UNO R3 示例

* 使用 ARM CMISIS-NN 库的 MNIST 数字识别，带 UART 传输和计时功能

### OpenCV 示例

* 各种 OpenCV 功能演示和使用示例

## 📁 项目结构

* `python/`：模型量化和仿真代码
* `Example/`：各种示例实现
* `opencv/`：OpenCV 相关实现
* `get_start.md`：详细使用说明

## 🚀 快速开始

本项目主要关注使用 ARM CMISIS-NN 的模型部署和 OpenCV 移植。详细说明请参考 get_start.md。

## 🤝 贡献

欢迎贡献！您可以：

* 提交 bug 或功能请求
* 创建改进的 pull requests
* 分享您的使用经验和建议

## 📅 开发路线图

* 支持更多神经网络架构
* 针对资源受限设备的性能优化
* 更全面的文档和示例
* 扩展 OpenCV 功能支持

## 📄 许可证

MIT License

## 🙏 致谢

* ARM CMSIS-NN 库团队
* OpenCV 社区
* 所有项目贡献者

## 📬 联系方式

如有问题和支持需求，请：

1. 在本仓库创建 issue
2. 查看现有文档和 issues
3. 加入我们的开发社区

---

_注：这是一个活跃开发中的项目。功能和文档会定期更新。_