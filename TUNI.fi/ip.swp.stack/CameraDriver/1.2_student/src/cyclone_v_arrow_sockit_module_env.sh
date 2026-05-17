# create a convenience variable to reference the soc-fpga linux include path
SOC_FPGA_LINUX_SRC_TREE_PATH="/opt/linux-arrow/yocto2.7/build/tmp/work/arrow_sockit-poky-linux-gnueabi/linux-altera-ltsi/4.14.130-ltsi+gitAUTOINC+cae6295550-r0/linux-arrow_sockit-standard-build"

CROSS_COMPILE=arm-linux-gnueabihf-
ARCH=arm

export SOC_FPGA_LINUX_SRC_TREE_PATH
export CROSS_COMPILE
export ARCH

echo ""
echo "Cyclone V Arrow SoCkit convenience variables:"
echo "SOC_FPGA_LINUX_SRC_TREE_PATH=${SOC_FPGA_LINUX_SRC_TREE_PATH}"
echo "CROSS_COMPILE=${CROSS_COMPILE}"
echo "ARCH=${ARCH}"
echo ""
