/*
 * REV Challenge 1
 * running strings
 *
 * Flag: FLAG{rev_1_down!_dfh02hrne}
 * Password: m4r10_k4r+
 *
 * Build: gcc -o challenge1 challenge1.c -s
 */

#include <stdio.h>
#include <string.h>

// XOR key used to encrypt the flag
#define XOR_KEY 0x5A

// flag XOR'd beforehand
static const unsigned char encrypted_flag[] = {
    0x1c, 0x16, 0x1b, 0x1d, 0x21, 0x28, 0x3f, 0x2c,
    0x05, 0x6b, 0x05, 0x3e, 0x35, 0x2d, 0x34, 0x7b,
    0x05, 0x3e, 0x3c, 0x32, 0x6a, 0x68, 0x32, 0x28,
    0x34, 0x3f, 0x27, 0x00
};

// password should appear on "strings challenge1"
static const char *password = "m4r10_k4r+";

int main(void) {
    char input[64];

    printf("- REV 1 -\n");
    printf("Enter the password: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, password) == 0) {
        printf("\nAccess granted! Here is your flag:\n");

        // decrypt and print flag
        for (int i = 0; encrypted_flag[i] != 0x00; i++) {
            putchar(encrypted_flag[i] ^ XOR_KEY);
        }
        putchar('\n');
    } else {
        printf("\nWrong password. Try harder.\n");
        return 1;
    }

    return 0;
}

