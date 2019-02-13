#include <stdio.h>
#include <stdint.h>

int main() {
    uint16_t TestNumber = 0xFF00;
    if(*((uint8_t *)&TestNumber) == 0x00) {
        printf("Little endian\n");
    }
    else {
        printf("Big endian\n");
    }
    return 0;
}
