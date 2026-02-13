<div align="center">
  
  ![STM32](https://img.shields.io/badge/STM32-F407ZGT6-blue?logo=stmicroelectronics)
  ![AI](https://img.shields.io/badge/AI-CMSIS--NN-green?logo=tensorflow)
  ![OpenCV](https://img.shields.io/badge/OpenCV-1.0-red?logo=opencv)
  ![License](https://img.shields.io/badge/License-MIT-yellow.svg)
  ![Platform](https://img.shields.io/badge/Platform-ARM%20Cortex--M4-orange)

  # 🚀 STM32 Deploy AI
  
  ### Deploy AI Models & OpenCV on STM32 Microcontrollers
  
  **[中文文档](#中文文档) | [English](#english-documentation)**
  
  <img src="https://img.shields.io/badge/status-active-success?style=for-the-badge" alt="Status">
  <img src="https://img.shields.io/badge/maintained-yes-blue?style=for-the-badge" alt="Maintained">
  
</div>

---

## 中文文档 {#中文文档}

> **💡 这是一个基于 ARM CMSIS-NN 库的开源项目，提供了在 STM32 微控制器上部署 AI 模型和 OpenCV 的完整解决方案。**

### ✨ 核心特性

| 特性 | 描述 |
|:---:|:---|
| 🧠 **AI 模型部署** | 在微控制器上部署量化后的 MXNet 模型 |
| 📊 **仿真平台** | 运行时数据分析、精度评估、RAM/ROM 使用估算 |
| 🎨 **OpenCV 集成** | 图像缩放、灰度转换、边缘检测、霍夫变换、腐蚀膨胀 |
| 👁️ **可视化工具** | 神经网络逐层输出可视化 |
| 🔧 **多架构支持** | VGG、ResNet、NiN、GoogLeNet、MobileNet（开发中） |
| 📝 **完整示例** | 提供 STM32 和 Arduino 完整代码示例 |

---

### 🎯 硬件要求

| 组件 | 推荐配置 |
|:---|:---|
| **开发板** | STM32F407ZGT6 |
| **显示屏** | TFT 屏幕 |
| **编程器** | ARM 模拟器/调试器 |

> 💡 **推荐**: [STM32F4 Discovery](https://www.st.com/en/evaluation-tools/stm32f4discovery.html) 开发板（包含屏幕）

---

### 📦 Python 依赖

```bash
# 安装所需依赖
pip install mxnet-cu100==1.5.0
pip install d2lzh==1.0.0
pip install opencv-python==4.5.4.60
pip install Pillow==8.4.0
```

---

### 🚀 快速开始

```bash
# 克隆仓库
git clone https://github.com/11223uhh/Stm32_Deploy_AI.git
cd Stm32_Deploy_AI

# 查看详细文档
cat get_start.md
```

#### 示例目录

```
Stm32_Deploy_AI/
├── 📁 python/          # 模型量化和仿真代码
├── 📁 Example/         # STM32 和 Arduino 示例
│   ├── Example1/       # MNIST 数字识别
│   ├── Example2/       # TensorFlow Lite 正弦波拟合
│   └── Example3/       # UART 图像识别
├── 📁 opencv/          # OpenCV 功能实现
└── 📄 get_start.md     # 详细使用指南
```

---

### 🌟 功能演示

#### AI 模型部署
```c
// MNIST 数字识别示例
#include "arm_nnfunctions.h"
// 使用 ARM CMSIS-NN 优化的神经网络函数
```

#### OpenCV 图像处理
```c
// 边缘检测示例
cvCanny(src, dst, threshold1, threshold2);
// 霍夫变换
cvHoughCircles(...)
```

---

### 🤝 贡献指南

欢迎任何形式的贡献！

- 🐛 报告 Bug
- 💡 提出新功能建议
- 🔧 提交 Pull Request
- 📖 改进文档

---

### 📊 项目状态

<details>
<summary>开发路线图</summary>

- [x] CMSIS-NN 基础集成
- [x] OpenCV 1.0 基础功能
- [x] MNIST 数字识别示例
- [x] 仿真平台
- [ ] ResNet 支持
- [ ] MobileNet 支持
- [ ] 更多 OpenCV 功能
- [ ] 性能优化

</details>

---

### 📄 许可证

本项目采用 [MIT License](LICENSE) 开源协议。

---

### 🙏 致谢

- [ARM CMSIS-NN](https://github.com/ARM-software/CMSIS-NN) 团队
- [OpenCV](https://opencv.org/) 社区
- 所有贡献者

---

## English Documentation {#english-documentation}

> **💡 An open-source project based on ARM CMSIS-NN library, providing a complete solution for deploying AI models and OpenCV on STM32 microcontrollers.**

### ✨ Key Features

| Feature | Description |
|:---:|:---|
| 🧠 **AI Deployment** | Deploy quantized MXNet models on microcontrollers |
| 📊 **Simulation Platform** | Runtime analysis, accuracy evaluation, RAM/ROM estimation |
| 🎨 **OpenCV Integration** | Image scaling, grayscale conversion, edge detection, Hough transform, erosion, dilation |
| 👁️ **Visualization** | Neural network layer-by-layer output visualization |
| 🔧 **Multi-Architecture** | VGG, ResNet, NiN, GoogLeNet, MobileNet (WIP) |
| 📝 **Complete Examples** | Full code examples for STM32 and Arduino |

---

### 🎯 Hardware Requirements

| Component | Recommendation |
|:---|:---|
| **Board** | STM32F407ZGT6 |
| **Display** | TFT Screen |
| **Programmer** | ARM Emulator/Debugger |

> 💡 **Recommended**: [STM32F4 Discovery](https://www.st.com/en/evaluation-tools/stm32f4discovery.html) board (includes screen)

---

### 📦 Python Dependencies

```bash
# Install required dependencies
pip install mxnet-cu100==1.5.0
pip install d2lzh==1.0.0
pip install opencv-python==4.5.4.60
pip install Pillow==8.4.0
```

---

### 🚀 Quick Start

```bash
# Clone repository
git clone https://github.com/11223uhh/Stm32_Deploy_AI.git
cd Stm32_Deploy_AI

# Read detailed documentation
cat get_start.md
```

#### Example Directory

```
Stm32_Deploy_AI/
├── 📁 python/          # Model quantization and simulation
├── 📁 Example/         # STM32 and Arduino examples
│   ├── Example1/       # MNIST digit recognition
│   ├── Example2/       # TensorFlow Lite sine wave fitting
│   └── Example3/       # UART image recognition
├── 📁 opencv/          # OpenCV implementation
└── 📄 get_start.md     # Detailed usage guide
```

---

### 🌟 Feature Demos

#### AI Model Deployment
```c
// MNIST digit recognition example
#include "arm_nnfunctions.h"
// Use ARM CMSIS-NN optimized neural network functions
```

#### OpenCV Image Processing
```c
// Edge detection example
cvCanny(src, dst, threshold1, threshold2);
// Hough transform
cvHoughCircles(...)
```

---

### 🤝 Contributing

Contributions are welcome in any form!

- 🐛 Report bugs
- 💡 Suggest new features
- 🔧 Submit pull requests
- 📖 Improve documentation

---

### 📊 Project Status

<details>
<summary>Development Roadmap</summary>

- [x] CMSIS-NN basic integration
- [x] OpenCV 1.0 basic features
- [x] MNIST digit recognition example
- [x] Simulation platform
- [ ] ResNet support
- [ ] MobileNet support
- [ ] More OpenCV features
- [ ] Performance optimization

</details>

---

### 📄 License

This project is licensed under the [MIT License](LICENSE).

---

### 🙏 Acknowledgments

- [ARM CMSIS-NN](https://github.com/ARM-software/CMSIS-NN) team
- [OpenCV](https://opencv.org/) community
- All contributors

---

<div align="center">
  
  **⭐ Star this repo if it helped you!**
  
  <img src="https://img.shields.io/badge/Made%20with-❤️-red.svg" alt="Made with love">
  
  [![GitHub stars](https://img.shields.io/github/stars/11223uhh/Stm32_Deploy_AI?style=social)](https://github.com/11223uhh/Stm32_Deploy_AI/stargazers)
  [![GitHub forks](https://img.shields.io/github/forks/11223uhh/Stm32_Deploy_AI?style=social)](https://github.com/11223uhh/Stm32_Deploy_AI/network/members)
  
</div>

---

<div align="center">

  **镜像 / Mirror**: [Gitee](https://gitee.com/k11223uhh/stm32_-deploy_-ai) 🇨🇳

</div>
