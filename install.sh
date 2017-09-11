#!/bin/sh

#gcc -shared -fPIC -o build/arch/x86-64/procedure.so procedure.c
mkdir build
cd build 
mkdir arch
cd arch
mkdir x86-64
mkdir i386
cd ../../
mkdir thermal_grease
cd thermal_grease
mkdir seeds
mkdir with

cd ../

#gcc -shared -fPIC -o build/arch/x86-64/procedure.so procedure.c

gcc -shared -fPIC -o build/arch/x86-64/time.so time.c -ldl

#gcc -shared -fPIC -o build/arch/i386/procedure.so procedure.c -m32
gcc -shared -fPIC -o build/arch/i386/time.so time.c -m32 -ldl
