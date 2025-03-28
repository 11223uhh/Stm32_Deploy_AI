# STM32 Deploy AI

[English](README.md) | [中文](README_zh.md) | [日本語](README_ja.md) | [한국어](README_ko.md)

**This project is based on the ARM CMSIS-NN library, serving as a practical implementation with optimized and extended features. It includes a streamlined version of the NN library and supports running OpenCV 1.0 on microcontrollers. For more details, please refer to the ARM CMSIS-NN library documentation. Issues and contributions are welcome!**

## Features

- Deploy quantized MXNet models on microcontrollers
- Simulation platform for:
  - Runtime data analysis
  - Accuracy evaluation
  - RAM/ROM usage estimation
- Integrated OpenCV 1.0 basic functions:
  - Image resizing
  - Grayscale conversion
  - Edge detection
  - Hough transform
  - Image erosion and dilation
- Neural network layer-by-layer output visualization
- VGG architecture support (ResNet, NiN, GoogLeNet, MobileNet support coming soon)
- Comprehensive example code
- Easy portability using CMSIS-NN basic functions (without acceleration functions)

## Requirements

### Python Environment
```
mxnet-cu100    == 1.5.0 
d2lzh          == 1.0.0
opencv-python  == 4.5.4.60
Pillow         == 8.4.0
```
> **Note**: These versions are tested and working. Other versions may also be compatible. Additional configuration may be needed for other deep learning frameworks (e.g., Keras).

### STM32 Hardware Requirements
- Development Board: STM32F407ZGT6 (other models may need adaptation)
- Display: TFT screen
- Programmer: ARM simulator/debugger (or compatible programmers)

> **Recommendation**: Consider purchasing the STM32F4mini Discovery Board (includes screen, uses F407ZGT6 chip). The project provides examples for both STM32 and Arduino (OpenCV not supported on Arduino).

## Examples

### STM32 Examples
1. Example1: MNIST digit recognition using ARM CMSIS-NN library (with embedded image)
2. Example2: Sine wave fitting using TensorFlow Lite with display output
3. Example3: Image recognition via Nucleo-STM32 UART with timing measurements

### Arduino UNO R3 Example
- MNIST digit recognition using ARM CMISIS-NN library with UART transmission and timing functionality

### OpenCV Examples
- Various OpenCV function demonstrations and usage examples

## Project Structure

- `python/`: Model quantization and simulation code
- `Example/`: Various example implementations
- `opencv/`: OpenCV-related implementations
- `get_start.md`: Detailed usage instructions

## Getting Started

This project focuses on model deployment using ARM CMISIS-NN and OpenCV porting. For detailed instructions, please refer to [get_start.md](get_start.md).

## Contributing

We welcome contributions! Feel free to:
- Submit issues for bugs or feature requests
- Create pull requests for improvements
- Share your experience and suggestions

## Development Roadmap

- [ ] Support for additional neural network architectures
- [ ] Performance optimization for resource-constrained devices
- [ ] More comprehensive documentation and examples
- [ ] Extended OpenCV functionality support

## License

[License information to be added]

## Acknowledgments

- ARM CMSIS-NN library team
- OpenCV community
- All contributors to this project

## Contact

For questions and support, please:
1. Create an issue in this repository
2. Check existing documentation and issues
3. Join our development community

---
*Note: This is an active project under development. Features and documentation are regularly updated.*