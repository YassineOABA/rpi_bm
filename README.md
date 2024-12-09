# rpi_bm
Bare metal programming for rpi
Based on these trainings : 
   - https://github.com/rockytriton/LLD
   - https://github.com/s-matyukevich/raspberry-pi-os

# processor
BCM2837B0

# How to build
1. run make make/make all to build the kernel
2. Run make clean to clean the project
3. Makefile will try to copy generated kernel8.img and config.txt to an SD card, consider updating
   the path to the right boot mount of your SD card or Makefile will fail. Nevertheless, it should create
   necessary output files.


