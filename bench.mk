# Arduino Timer HAL
PRODUCT_PACKAGES += vendor.alvenan.timer
PRODUCT_PACKAGES += vendor.alvenan.timer-service
PRODUCT_PACKAGES += vendor.alvenan.timermanager
DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE := \
    vendor/AOSPbenchmarktimer_hal/hardware/interfaces/vendor/alvenan/timer/compatibility_matrix.xml

# Bench test programs
PRODUCT_PACKAGES += NativeTestApp
PRODUCT_PACKAGES += JavaNativeTestApp
