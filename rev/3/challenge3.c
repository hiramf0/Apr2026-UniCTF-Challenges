/*
 * REV 3
 * Difficulty: Easy
 * Flag: FLAG{rev_3_down!_fh5v2d86}
 *
 * Build:
 *   gcc -o challenge3 challenge3.c -s -O0
 *   upx challenge3
 */

#include <stdio.h>
#include <string.h>

// XOR key - should appear in .data
static const unsigned char xor_key[] = { 0x4B, 0x41, 0x52, 0x54 }; /* "KART" */

/* encrypted flag here
 * xor_key[i % 4] - never decrypted at runtime */
static const unsigned char encrypted_flag[] = {
    0x0d, 0x0d, 0x13, 0x13, 0x30, 0x33, 0x37, 0x22,
    0x14, 0x72, 0x0d, 0x30, 0x24, 0x36, 0x3c, 0x75,
    0x14, 0x27, 0x3a, 0x61, 0x3d, 0x73, 0x36, 0x6c,
    0x7d, 0x3c, 0x00
};

// used to force the compiler to load the flag into memory
// does nothing
static unsigned int compute_checksum(void) {
    unsigned int sum = 0;
    for (int i = 0; encrypted_flag[i] != 0x00; i++) {
        sum += (unsigned int)(encrypted_flag[i] ^ xor_key[i % 4]);
    }
    return sum;
}

int main(void) {
    char input[64];

    printf("=== Packed Kart ===\n");
    printf("What's your favorite Mario Kart character? ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    // does nothing. makes flag appear on Ghidra
    unsigned int cs = compute_checksum();
    (void)cs;

    printf("\nThat's awesome! Mine's Funky Kong.\n");
    return 0;
}
