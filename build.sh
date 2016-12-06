#!/bin/bash
sudo rmmod proc1;
sudo rmmod proc2;
sudo rmmod nf2
cd proc;
sudo dmesg -c
make;
sudo insmod proc1.ko;
sudo insmod proc2.ko;
echo "172.0.1.1" >/proc/IP;
echo "4" >/proc/Function ;
cd ..;
cd netfilter;
make
sudo insmod nf2.ko
