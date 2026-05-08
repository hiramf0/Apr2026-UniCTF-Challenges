/*
 * REV 2
 * Difficulty: Easy
 *
 * Flag:     FLAG{rev_2_down!_xaji0y6d}
 * Password: slipstream   (wordlist[0x00A3])
 *
 * Build: gcc -o challenge2 challenge2.c -s -O2
 *
 * intended solution:
 *   1. `strings ./challenge2` -> wall of Mario Kart words, no strcmp target
 *   2. ltrace/strace -> no strcmp(), no memcmp() libc calls
 *   3. Open in Ghidra/IDA -> spot the index calc: idx = 0x00A3 (163)
 *   4. Map index 163 in the array -> "slipstream"
 *   5. Enter password -> flag decrypts
 */

#include <stdio.h>
#include <string.h>

// -- XOR-encrypted flag (key = 0x37) --
static const unsigned char encrypted_flag[] = {
    0x71, 0x7b, 0x76, 0x70, 0x4c, 0x45, 0x52, 0x41,
    0x68, 0x05, 0x68, 0x53, 0x58, 0x40, 0x59, 0x16,
    0x68, 0x4f, 0x56, 0x5d, 0x5e, 0x07, 0x4e, 0x01,
    0x53, 0x4a, 0x00
};

// wordlist (len = 200)
static const char *words[200] = {
    "checkered",       /* 0   */
    "bulletbill",      /* 1   */
    "threelights",     /* 2   */
    "grapplinghook",   /* 3   */
    "champcar",        /* 4   */
    "f1n15hl1n3",      /* 5   */
    "personalrecord",  /* 6   */
    "l4p2",            /* 7   */
    "diddykong",       /* 8   */
    "podium",          /* 9   */
    "jungl3",          /* 10  */
    "worldranking",    /* 11  */
    "sky",             /* 12  */
    "gotime",          /* 13  */
    "100cc",           /* 14  */
    "singleplayer",    /* 15  */
    "w4lu1g1574d1um",  /* 16  */
    "p4r4gl1d3r",      /* 17  */
    "50cc",            /* 18  */
    "tripleshell",     /* 19  */
    "l4unch",          /* 20  */
    "boost",           /* 21  */
    "nitrocourse",     /* 22  */
    "powerup",         /* 23  */
    "finishline",      /* 24  */
    "jungle",          /* 25  */
    "ninetyeight",     /* 26  */
    "grind",           /* 27  */
    "canyon",          /* 28  */
    "koopa",           /* 29  */
    "shellcup",        /* 30  */
    "c4ny0n",          /* 31  */
    "y05h1",           /* 32  */
    "waluigistadium",  /* 33  */
    "wario",           /* 34  */
    "ramp",            /* 35  */
    "continental",     /* 36  */
    "blooper",         /* 37  */
    "m4r10",           /* 38  */
    "beach",           /* 39  */
    "fl4g",            /* 40  */
    "starpower",       /* 41  */
    "donkeykong",      /* 42  */
    "invincible",      /* 43  */
    "minitubo",        /* 44  */
    "staffghost",      /* 45  */
    "spin",            /* 46  */
    "redshellhome",    /* 47  */
    "drybones",        /* 48  */
    "paraglider",      /* 49  */
    "glider",          /* 50  */
    "online",          /* 51  */
    "lastplace",       /* 52  */
    "lap3",            /* 53  */
    "5p4c3",           /* 54  */
    "friends",         /* 55  */
    "rainbow",         /* 56  */
    "daisy",           /* 57  */
    "m4r10c1rcu17",    /* 58  */
    "flag",            /* 59  */
    "gr33n5h3ll",      /* 60  */
    "ratingpoints",    /* 61  */
    "gold",            /* 62  */
    "rankdown",        /* 63  */
    "spinjump",        /* 64  */
    "iceland",         /* 65  */
    "turbo",           /* 66  */
    "200cc",           /* 67  */
    "brake",           /* 68  */
    "m374ll1c",        /* 69  */
    "yoshicircuit",    /* 70  */
    "drift",           /* 71  */
    "wheelie",         /* 72  */
    "grandprix",       /* 73  */
    "5ky",             /* 74  */
    "rivals",          /* 75  */
    "peach",           /* 76  */
    "stadium",         /* 77  */
    "toad",            /* 78  */
    "volcano",         /* 79  */
    "574d1um",         /* 80  */
    "p2",              /* 81  */
    "vs_race",         /* 82  */
    "bowser",          /* 83  */
    "supertubo",       /* 84  */
    "drybowser",       /* 85  */
    "galaxy",          /* 86  */
    "f1n4l57r37ch",    /* 87  */
    "blueshell",       /* 88  */
    "rail",            /* 89  */
    "gr1nd",           /* 90  */
    "7r1pl35h3ll",     /* 91  */
    "accelerate",      /* 92  */
    "specialcup",      /* 93  */
    "launch",          /* 94  */
    "trophycup",       /* 95  */
    "timeattack",      /* 96  */
    "c0m37",           /* 97  */
    "shortcut",        /* 98  */
    "boo",             /* 99  */
    "teamrace",        /* 100 */
    "redshell",        /* 101 */
    "shyguy",          /* 102 */
    "gr4ndpr1x",       /* 103 */
    "toadharbor",      /* 104 */
    "waluigi",         /* 105 */
    "offroad",         /* 106 */
    "offline",         /* 107 */
    "balloonbattle",   /* 108 */
    "p3",              /* 109 */
    "countdown",       /* 110 */
    "0ffr04d",         /* 111 */
    "150cc",           /* 112 */
    "boomerang",       /* 113 */
    "b4bym4r10",       /* 114 */
    "7r1ck",           /* 115 */
    "c0un7d0wn",       /* 116 */
    "bull37b1ll",      /* 117 */
    "und3rw473r",      /* 118 */
    "sunshine",        /* 119 */
    "5p1njump",        /* 120 */
    "trick",           /* 121 */
    "banana",          /* 122 */
    "metallic",        /* 123 */
    "boostpad",        /* 124 */
    "1nv1nc1bl3",      /* 125 */
    "worldwide",       /* 126 */
    "5h0r7cu7",        /* 127 */
    "circuit",         /* 128 */
    "5l1d3",           /* 129 */
    "slide",           /* 130 */
    "k00p4",           /* 131 */
    "bowsercastle",    /* 132 */
    "jump",            /* 133 */
    "mirror",          /* 134 */
    "snowland",        /* 135 */
    "b4byd415y",       /* 136 */
    "goldenleaf",      /* 137 */
    "piranhaplant",    /* 138 */
    "space",           /* 139 */
    "retrocourse",     /* 140 */
    "l4p3",            /* 141 */
    "raceway",         /* 142 */
    "rainbowroad",     /* 143 */
    "local",           /* 144 */
    "shine",           /* 145 */
    "lightningbolt",   /* 146 */
    "mushroompeak",    /* 147 */
    "l1gh7n1ngcup",    /* 148 */
    "p4",              /* 149 */
    "b4bylu1g1",       /* 150 */
    "kart",            /* 151 */
    "winner",          /* 152 */
    "silver",          /* 153 */
    "flowercup",       /* 154 */
    "funky",           /* 155 */
    "startinggrid",    /* 156 */
    "thirdplace",      /* 157 */
    "babymario",       /* 158 */
    "drifting",        /* 159 */
    "leafcup",         /* 160 */
    "onelight",        /* 161 */
    "finalstretch",    /* 162 */
    "slipstream",      /* 163 = 0x00A3  <-- correct index */
    "lap2",            /* 164 */
    "multiplayer",     /* 165 */
    "rosalina",        /* 166 */
    "mu5hr00mp07",     /* 167 */
    "superhorn",       /* 168 */
    "starman",         /* 169 */
    "retro",           /* 170 */
    "gh057d474",       /* 171 */
    "7h1rdpl4c3",      /* 172 */
    "bananacup",       /* 173 */
    "battlemode",      /* 174 */
    "superstar",       /* 175 */
    "trophy",          /* 176 */
    "dr1f71ng",        /* 177 */
    "coinrunners",     /* 178 */
    "secondplace",     /* 179 */
    "coinitem",        /* 180 */
    "mu5hr00mp34k",    /* 181 */
    "r471ngp01n75",    /* 182 */
    "wh33l13",         /* 183 */
    "dkjungle",        /* 184 */
    "lightningcup",    /* 185 */
    "babypeach",       /* 186 */
    "toadsturnpike",   /* 187 */
    "r4mp",            /* 188 */
    "nitro",           /* 189 */
    "luigi",           /* 190 */
    "mario",           /* 191 */
    "coin",            /* 192 */
    "bronze",          /* 193 */
    "bananapeel",      /* 194 */
    "road",            /* 195 */
    "koopacape",       /* 196 */
    "supermushroom",   /* 197 */
    "cloud",           /* 198 */
    "babydaisy",       /* 199 */
};

 // no strcmp() or memcmp(). char-by-char XOR check.
static int check_password(const char *input, const char *target) {
    int i = 0;
    while (target[i] != '\0') {
        if ((input[i] ^ target[i]) != 0)
            return 1;   // MISMATCH
        i++;
    }

    // also ensure input isn't longer than target
    return (input[i] != '\0');
}

int main(void) {
    char input[64];

    // index of the correct password in the wordlist (0xa3 = 163)
    const int correct_idx = 0x00A3;

    printf("=== Kart Strings ===\n");
    printf("Enter the password: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
        return 1;
    input[strcspn(input, "\n")] = '\0';

    if (check_password(input, words[correct_idx]) == 0) {
        printf("\nPassword OK! Here's your flag:\n");

        // XOR decrypt and print flag (key = 0x37)
        for (int i = 0; encrypted_flag[i] != 0x00; i++)
            putchar(encrypted_flag[i] ^ 0x37);
        putchar('\n');
    } else {
        printf("\nWrong password.\n");
        return 1;
    }

    return 0;
}
