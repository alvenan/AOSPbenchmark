# Benchmarking of Android Native application and Android JNI application

### This project  has the focus in compare the performace between a native application and a java application that are accessing the same C++ lib of algorithms.

## Setup
### 1. Hardware
The objective of this project is to utilize a Raspberry Pi 4B as the primary platform, complemented by an Arduino as the timer, to accurately measure the processing time of each algorithm.

#### Diagram flux
<img src="/img/diagrama.drawio.pdf" width="500">

#### Hardware circuit
<img src="/img/circuito.pdf" width="500">

### 2. Software

#### Android 13
The Raspberry Pi 4B was flashed with the ARPI Project operating system. For instructions on setting up Android for Raspberry Pi, please refer to the link below:
https://github.com/snappautomotive/firmware-device_snappautomotive_rpi/tree/arpi-13

#### Timer firmware
The timer is constructed using an Arduino Nano, and its firmware can be found at the link below:
https://github.com/alvenan/ArduinoTimer

#### Benchmark project
1. Clone the project into the vendor folder within the AOSP tree.
2. Append the following code to the end of the device makefile located at device/arpi/rpi4/rpi4.mk.
```
$(call inherit-product, vendor/AOSPbenchmark/bench.mk)
```
## Executing tests
....
