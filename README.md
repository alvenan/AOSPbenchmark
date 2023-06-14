# Benchmarking of Android Native application and Android JNI application

### This project  has the focus in compare the performace between a native application and a java application that are accessing the same C++ lib of algorithms.

## Setup
### 1. Hardware
The target of this project in one Raspberry Pi 4B and it uses an arduino as the timer to count the process time of each test.

#### Diagram flux
<img src="/img/diagrama.png" width="500">

#### Hardware circuit
<img src="/img/circuit_test.png" width="500">

### 2. Software

#### Android 13
The OS flashed in the Raspiberry Pi 4B was the ARPI Project, the setup of this Android for Raspberry is in the link bellow:
https://github.com/snappautomotive/firmware-device_snappautomotive_rpi/tree/arpi-13

#### Timer firmware
The timer is made with an Arduino Nano and its firmwareis in the link bellow:
https://github.com/alvenan/ArduinoTimer

#### Benchmark project
1. In the AOSP tree clone the project in the vendor folder.
2. In the end of device makefile, located in device/arpi/rpi4/rpi4.mk, add the following code:
```
# Arduino Timer HAL
PRODUCT_PACKAGES += vendor.alvenan.timer
PRODUCT_PACKAGES += vendor.alvenan.timer-service
PRODUCT_PACKAGES += vendor.alvenan.timermanager
DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE := \
    vendor/AOSPbenchmark/timer_hal/hardware/interfaces/vendor/alvenan/timer/compatibility_matrix.xml

# Bench test programs
PRODUCT_PACKAGES += NativeTestApp
PRODUCT_PACKAGES += JavaNativeTestApp
```
## Executing tests
....
