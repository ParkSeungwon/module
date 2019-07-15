#!/bin/bash

if [ ! -c /dev/memory ]; then
	insmod memory.ko
	major=`cat /proc/devices | awk '$2 == "memory" {print $1}'`
	mknod /dev/memory c $major 0
else
	rmmod memory.ko
	rm /dev/memory
fi

