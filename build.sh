#!/bin/bash
cd xen
export CROSS_COMPILE=aarch64-linux-gnu-
export ARCH=arm64
export XEN_TARGET_ARCH=arm64
export XEN_CONFIG_EXPERT=y
make defconfig
make -j4
cp xen.efi ../../optee/xen/
