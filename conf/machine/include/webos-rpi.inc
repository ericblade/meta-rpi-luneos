# Copyright (c) 2017-2024 LG Electronics, Inc.

# The MACHINE.conf for every MACHINE that has an Raspberry Pi BSP must require this
# file.

# All the MACHINE-s supported by this layer are real pieces of hardware.
WEBOS_TARGET_MACHINE_IMPL = "hardware"

MACHINE_FEATURES += "armnn auto-acceleration edgetpu gpu-delegate gl-backend"

# On Raspberry Pi 3B, at least 160MB gpu_mem setting is required for VKB to
# reliably function at 1920x1080.  At 1280x720 or lower, setting it as low
# as the minimum, 16, seems to work.  Override in your local.conf if you do
# not intend to use 1080 resolution.  At 1080, all other video features seem
# to work, except for VKB, with the lower settings.
GPU_MEM ??= "160"

PREFERRED_PROVIDER_aval-impl = "avoutput-adaptation-layer-rpi"
VIRTUAL-RUNTIME_aval-impl = "avoutput-adaptation-layer-rpi"
VIRTUAL-RUNTIME_alsa-state = "avoutput-adaptation-layer-rpi"
SKIP_RECIPE[avoutput-adaptation-layer-mock] ?= "avoutput-adaptation-layer-rpi is preferred"

PREFERRED_PROVIDER_val-impl = "videooutput-adaptation-layer-rpi"
VIRTUAL-RUNTIME_val-impl = "videooutput-adaptation-layer-rpi"
SKIP_RECIPE[videooutput-adaptation-layer-mock] ?= "videooutput-adaptation-layer-rpi is preferred"

SKIP_RECIPE[omxplayer] ?= "not compatible with webOS Open components"
SKIP_RECIPE[packagegroup-rpi-test] ?= "rdepends on omxplayer"
SKIP_RECIPE[rpi-test-image] ?= "rdepends on packagegroup-rpi-test"

MACHINE_EXTRA_RRECOMMENDS:remove = "kernel-modules"
MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS:remove = "kernel-modules"
MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS:append = " ${RPI_KERNEL_MODULES}"
RPI_KERNEL_MODULES = " \
    kernel-module-bcm2835-gpiomem \
    kernel-module-bcm2835-wdt \
    kernel-module-bluetooth \
    kernel-module-brcmfmac \
    kernel-module-bridge \
    kernel-module-btbcm \
    kernel-module-btusb \
    kernel-module-configs \
    kernel-module-evdev \
    kernel-module-hci-uart \
    kernel-module-hid-multitouch \
    kernel-module-hid-sony \
    kernel-module-i2c-bcm2708 \
    kernel-module-media \
    kernel-module-rfcomm \
    kernel-module-snd-bcm2835 \
    kernel-module-snd-usb-audio \
    kernel-module-uinput \
    kernel-module-uvcvideo \
    kernel-module-vc4 \
    kernel-module-videodev \
    kernel-module-xpad \
"
# Few more modules which are automatically loaded on
# raspberrypi4 when all kernel-modules are installed
RPI_KERNEL_MODULES:append:raspberrypi4 = " \
    kernel-module-8021q \
    kernel-module-bcm2835-codec \
    kernel-module-bcm2835-v4l2 \
    kernel-module-bnep \
    kernel-module-cdc-ether \
    kernel-module-cifs \
    kernel-module-cmac \
    kernel-module-fixed \
    kernel-module-joydev \
    kernel-module-libarc4 \
    kernel-module-md4 \
    kernel-module-raspberrypi-hwmon \
    kernel-module-rpivid-mem \
    kernel-module-sch-fq-codel \
    kernel-module-snd-soc-ac108 \
    kernel-module-snd-soc-bcm2835-i2s \
    kernel-module-uio-pdrv-genirq \
    kernel-module-v3d \
"

KERNEL_MODULE_AUTOLOAD:append = " uinput bridge vc4"

# Always enable u-boot
RPI_USE_U_BOOT = "1"

# Always deploy the VFAT partition
SDIMG_VFAT_DEPLOY = "1"

ENABLE_UART = "1"

# Otherwise there are black bars around the screen and touchscreen calibration then doesn't match with the rendered screen in some setups
DISABLE_OVERSCAN = "1"

# Configure all Bluetooth service classes we want to support
WEBOS_BLUETOOTH_ENABLED_SERVICE_CLASSES = "SPP GATT FTP OPP A2DP"

# Use ext4 as a uSD rootfs type and don't build ext3
SDIMG_ROOTFS_TYPE = "ext4"
IMAGE_FSTYPES:remove = "ext3"