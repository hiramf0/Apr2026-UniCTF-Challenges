/*
 * REV 5
 * Difficulty: Easy-Medium
 * Flag: FLAG{rev_5_down!_d8f040km}
 *
 * Build:
 *   gcc -o challenge5 challenge5.c -s -O0
 * 
 * correct setup: Waluigi (14) + Pipe Frame (2) + Wario Wing (3)
 * 
 */

#include <stdio.h>
#include <string.h>

/* encrypted flag
 * build_key(14, 2, 3) = {0x1c, 0x05, 0x0d, 0x13} */
static const unsigned char encrypted_flag[] = {
    0x5a, 0x49, 0x4c, 0x54, 0x67, 0x77, 0x68, 0x65,
    0x43, 0x30, 0x52, 0x77, 0x73, 0x72, 0x63, 0x32,
    0x43, 0x61, 0x35, 0x75, 0x2c, 0x31, 0x3d, 0x78,
    0x71, 0x78, 0x00
};

/*
 *   key[0] = (char_c * body_c) % 256
 *   key[1] = (body_c + glider_c) % 256
 *   key[2] = (char_c ^ glider_c) % 256
 *   key[3] = (char_c + body_c + glider_c) % 256
 */
static void build_key(int char_c, int body_c, int glider_c, unsigned char key[4]) {
    key[0] = (unsigned char)((char_c * body_c) % 256);
    key[1] = (unsigned char)((body_c + glider_c) % 256);
    key[2] = (unsigned char)((char_c ^ glider_c) % 256);
    key[3] = (unsigned char)((char_c + body_c + glider_c) % 256);
}

int main(void) {
    int char_choice, body_choice, glider_choice;

    printf("=== Character Select ===\n");
    printf("Can you guess my favorite Mario Kart 8 DX setup?\n\n");

    // 1. character
    printf("Select a character:\n");
    printf("  1.  Baby Peach        2.  Baby Rosalina\n");
    printf("  3.  Baby Mario        4.  Toadette\n");
    printf("  5.  Koopa Troopa      6.  Toad\n");
    printf("  7.  Cat Peach         8.  Peach\n");
    printf("  9.  Tanooki Mario     10. Mario\n");
    printf("  11. Luigi             12. Rosalina\n");
    printf("  13. Metal Mario       14. Waluigi\n");
    printf("  15. Wario             16. Bowser\n");
    printf("\nYour choice: ");
    scanf("%d", &char_choice);

    if (char_choice < 1 || char_choice > 16) {
        printf("\n[-] Invalid character.\n");
        return 1;
    }

    // 2. body
    printf("\nSelect a body:\n");
    printf("  1.  Standard Kart     2.  Pipe Frame\n");
    printf("  3.  Mach 8            4.  Steel Driver\n");
    printf("  5.  Cat Cruiser       6.  Circuit Special\n");
    printf("  7.  Badwagon          8.  Prancer\n");
    printf("  9.  Biddybuggy        10. Landship\n");
    printf("  11. Sneeker           12. W 25 Silver Arrow\n");
    printf("  13. Blue Falcon       14. Tanooki Kart\n");
    printf("\nYour choice: ");
    scanf("%d", &body_choice);

    if (body_choice < 1 || body_choice > 14) {
        printf("\n[-] Invalid body.\n");
        return 1;
    }

    // 3. glider
    printf("\nSelect a glider:\n");
    printf("  1. Super Glider\n");
    printf("  2. Cloud Glider\n");
    printf("  3. Wario Wing\n");
    printf("  4. Peach Parasol\n");
    printf("\nYour choice: ");
    scanf("%d", &glider_choice);

    if (glider_choice < 1 || glider_choice > 4) {
        printf("\n[-] Invalid glider.\n");
        return 1;
    }

    // create key and attempt decryption
    unsigned char key[4];
    build_key(char_choice, body_choice, glider_choice, key);

    printf("\nLoading your setup");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
    }
    printf("\n\n");

    for (int i = 0; encrypted_flag[i] != 0x00; i++) {
        putchar((int)(encrypted_flag[i] ^ key[i % 4]));
    }
    putchar('\n');

    return 0;
}
