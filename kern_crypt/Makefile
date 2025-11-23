TARGET = kern_crypt

KERNEL = $(shell uname -r)
KCC=$(shell grep CONFIG_CC_VERSION /boot/config-$(KERNEL) | cut -d '"' -f2 | awk '{print$$1}')
KDIR = /lib/modules/$(KERNEL)/build
PWD = $(shell pwd)

SOURCES :=
SOURCES += $(wildcard module/*.c)
SOURCES += $(wildcard crypto/*.c)
EXTRA_CFLAGS += -I$(PWD)/include
OBJS = $(SOURCES:.c=.o)

obj-m += $(TARGET).o
$(TARGET)-objs := $(OBJS)

all:
	$(MAKE) CC=$(KCC) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

.PHONY: all clean
