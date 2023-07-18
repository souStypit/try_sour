#include <stdio.h>

//address_code
#define BU_MAX_DATA 32

//decimal_to_binary
void print_binary(int num);
void to_binary(int num);

/////////////////////////////////////
int main() {
    //ADDRESS_CODE
    for (int i = 0; i < BU_MAX_DATA; i++) {
        int code = (1 << ((i >> 1) % 16)) ^ ((i & 1) ? 0 : ~0);
        printf("%d ", code);
        if (code > 0) {
            print_binary(code);
        }
    }
    printf("\n");

    //DECIMAL_TO_BINARY
    //int num = 5 * 2;
    //print_binary(num);
    return 0;
}
/////////////////////////////////////

//IMPLEMENTATION
//decimal_to_binary
void print_binary(int num) {
    to_binary(num);
    printf("\n");
}
void to_binary(int num) {
    if (num) {
        to_binary(num >> 1);
        printf("%d", num & 1);
    }
}

//address_code