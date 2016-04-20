#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000;
// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;
const int gpio_pbtnl_offset = 0x16C; // Offset for left push button
const int gpio_pbtnr_offset = 0x170; // Offset for right push button
const int gpio_pbtnu_offset = 0x174; // Offset for up push button
const int gpio_pbtnd_offset = 0x178; // Offset for down push button
const int gpio_pbtnc_offset = 0x17C; // Offset for center push button

class Zedboard {

    char *ptr;
    int fd;

  public:
    Zedboard() {
        this->fd  = open( "/dev/mem", O_RDWR);
        this->ptr =  (char *) mmap(
                                NULL,
                                gpio_size,
                                PROT_READ | PROT_WRITE,
                                MAP_SHARED,
                                fd,
                                gpio_address);
    }

    ~Zedboard() {
        munmap(ptr, gpio_size);
        close(fd);
    }

    void RegisterWrite(int offset, int value) {
         * (int *) (ptr + offset) = value;
    }

    int RegisterRead(int offset) {
        return * (int *) (ptr + offset);
    }

    int PushButtonGet() {
        int pushed_button = 0;
        if(RegisterRead(gpio_pbtnu_offset)) {
            pushed_button = 1;
        }
        if(RegisterRead(gpio_pbtnd_offset)) {
            pushed_button = 2;
        }
        if(RegisterRead(gpio_pbtnr_offset)) {
            pushed_button = 3;
        }
        if(RegisterRead(gpio_pbtnl_offset)) {
            pushed_button = 4;
        }
        if(RegisterRead(gpio_pbtnc_offset)) {
            pushed_button = 5;
        }
        return pushed_button;
    }
  
};
