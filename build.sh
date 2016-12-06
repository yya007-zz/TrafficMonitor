#!/bin/bash
rmmod proc1;
rmmod proc2;
rmmod nf2
cd proc;
dmesg -c
make;
insmod proc1.ko;
insmod proc2.ko;
echo "172.0.1.1" >/proc/IP;
echo "1" >/proc/Function ;
cd ..;
cd netfilter;
make
insmod nf2.ko