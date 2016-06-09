#!/bin/bash

#PATH=/opt/padlinux/otns/1.6.2.4/sysroots/x86_64-padlinuxsdk-linux/usr/bin/i586-padtec-linux:$PATH
TOOLCHAIN=padtec.fw.rsc.toolchain.gnu.x86_64.1
#CROSS_X86=i586-padtec-linux-
PROJECT_ID=notice.x86.sdk

# SPVL
#${CROSS_X86}g++ recv.cc -I /home/crossi/workspace/foc.sdk/repos/trd.lib.boost/boost/ -L /home/crossi/workspace/foc.sdk/build/${TOOLCHAIN}/trd.lib.boost/custom/1.55.0/0.1.4/#/release/lib -lboost_system -lboost_thread -pthread -o recv_x86_spvl

# AMP45U
#PATH=/opt/padlinux/amp/1.6.1.0/sysroots/x86_64-padlinuxsdk-linux/usr/bin/arm-padtec-linux-gnueabi:$PATH
#TOOLCHAIN=padtec.fw.rsc.toolchain.padlinux.arm.a5.1
#CROSS=arm-padtec-linux-gnueabi-

${CROSS}g++ recv.cc -I /home/crossi/workspace/${PROJECT_ID}/repos/trd.lib.boost/boost/ -L /home/crossi/workspace/${PROJECT_ID}/build/${TOOLCHAIN}/trd.lib.boost/custom/1.55.0/0.1.4/#/release/lib -lboost_system -lboost_thread -pthread -o recv_x86
