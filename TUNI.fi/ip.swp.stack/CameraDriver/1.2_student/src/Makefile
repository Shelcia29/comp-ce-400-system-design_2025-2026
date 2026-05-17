obj-m += camera_driver.o
FLAGS = -O2
ifdef DEBUG
FLAGS += -DDEBUG
endif
ifdef TIMEOUT_ON
FLAGS += -DTIMEOUT_ON
endif

CFLAGS_cameraMap.o := $(FLAGS)
KDIR ?= $(SOC_FPGA_LINUX_SRC_TREE_PATH)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
