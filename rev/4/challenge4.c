/*
 * REV 4 - checksum
 * Difficulty: Easy-Medium
 * Flag: FLAG{rev_4_down!_08cekfn1}
 *
 * Build:
 *   gcc -o challenge4 challenge4.c -s -O0
 *
 */

#include <stdio.h>
#include <string.h>

/* encrypted flag
 * XOR'd with 0x78 (= 1144 % 256)                */
static const unsigned char encrypted_flag[] = {
    0x3e, 0x34, 0x39, 0x3f, 0x03, 0x0a, 0x1d, 0x0e,
    0x27, 0x4c, 0x27, 0x1c, 0x17, 0x0f, 0x16, 0x59,
    0x27, 0x48, 0x40, 0x1b, 0x1d, 0x13, 0x1e, 0x16,
    0x49, 0x05, 0x00
};

static int compute_checksum(const char *s, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += (unsigned char)s[i];
    }
    return sum;
}

int main(void) {
    char input[64];

    printf("=== Checksum Kart ===\n");
    printf("Enter the secret code: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    int len = (int)strlen(input);
    
    if (strcmp(input, "debug") == 0) {
        printf("\n[debug] target checksum: %d\n", 1144);
        return 0;
    }


    if (len != 12) {
        printf("\n[-] Wrong length. Try again.\n");
        return 1;
    }

    int checksum = compute_checksum(input, len);

    /* XOR key is derived from the checksum itself.
     * only produces the real flag when checksum == 1144.
     * always attempts decryption so static analysis
     * of the encrypted_flag[] bytes alone is useless. */
    unsigned char key = (unsigned char)(checksum % 256);

    printf("\nAttempting decryption...\n");
    for (int i = 0; encrypted_flag[i] != 0x00; i++) {
        putchar((int)(encrypted_flag[i] ^ key));
    }
    putchar('\n');

    return 0;
}
