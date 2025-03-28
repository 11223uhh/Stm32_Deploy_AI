# STM32 部署 AI

[English](README.md) | [中文](README_zh.md) | [日本語](README_ja.md) | [한국어](README_ko.md)

**本项目基于 ARM CMSIS-NN 库开发，是 CMSIS-NN 的一个实践应用。项目对 NN 库进行了裁剪、扩充和优化，同时支持在单片机上运行 OpenCV 1.0。如有问题欢迎在 Issues 中提出。更多详细信息请参考 ARM CMSIS-NN 库文档。**

## 项目特点

- 支持将 MXNet 训练的模型量化后部署到单片机
- 提供仿真平台，可模拟实际运行数据、精确度、RAM和ROM占用
- 集成 OpenCV 1.0 基础功能：
  - 图片缩放
  - 灰度化处理
  - 边缘检测
  - 霍夫变换
  - 图像腐蚀和膨胀
- 支持查看神经网络每一层的输出
- 当前支持 VGG 网络结构（暂不支持 ResNet、NiN、GoogLeNet、MobileNet）
- 提供丰富的示例代码
- 使用 CMSIS-NN 基础函数，便于移植（未使用加速函数）

## 环境要求

### Python 环境
```
mxnet-cu100    == 1.5.0 
d2lzh          == 1.0.0
opencv-python  == 4.5.4.60
Pillow         == 8.4.0
```
> **注意**：以上版本在测试环境中运行正常，其他版本也可能支持。如需使用其他深度学习框架（如 Keras），需要额外配置。

### STM32 硬件要求
- 开发板：STM32F407ZGT6（其他型号可能需要适配）
- 显示屏：TFT屏幕
- 下载器：ARM 仿真下载器（或其他兼容下载器）

> **推荐**：可以直接购买 STM32F4mini 探索版开发板（带屏幕，使用F407ZGT6芯片）。项目同时提供 STM32 和 Arduino（不支持 OpenCV）的示例程序。

## 示例程序

### STM32 示例
1. Example1：使用 ARM CMSIS-NN 库识别预置的 MNIST 手写数字图片
2. Example2：基于 TensorFlow Lite 实现正弦曲线拟合并显示
3. Example3：通过 Nucleo-STM32 串口传输图片进行识别并计时

### Arduino UNO R3 示例
- 基于 ARM CMISIS-NN 库实现 MNIST 图片识别，支持串口传输和计时功能

### OpenCV 示例
- 包含多个 OpenCV 函数使用示例

## 项目结构

- `python/`：模型量化和仿真相关代码
- `Example/`：各类示例程序
- `opencv/`：OpenCV 相关实现
- `get_start.md`：详细使用说明

## 使用指南

本项目主要介绍基于 ARM CMISIS-NN 的模型部署和 OpenCV 移植方法，详细使用说明请参考 [get_start.md](get_start.md)。

## 贡献指南

欢迎提交贡献！您可以：
- 提交 Issue 报告问题或建议新功能
- 创建 Pull Request 提交改进
- 分享您的使用经验和建议

## 开发计划

- [ ] 支持更多神经网络架构
- [ ] 针对资源受限设备的性能优化
- [ ] 完善文档和示例
- [ ] 扩展 OpenCV 功能支持

## 许可证

[许可证信息待补充]

## 致谢

- ARM CMSIS-NN 库团队
- OpenCV 社区
- 所有项目贡献者

## 联系方式

如需帮助或支持，请：
1. 在本仓库创建 Issue
2. 查看现有文档和问题
3. 加入我们的开发社区

---
*注：本项目正在积极开发中，功能和文档会定期更新。*