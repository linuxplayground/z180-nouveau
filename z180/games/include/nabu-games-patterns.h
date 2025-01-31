const uint8_t  FAT[0x400] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*  - 0x00 - ALWAYS BLANK    */
0x18,0x3C,0x3C,0x7E,0x7E,0x7E,0x3C,0x3C, /*  - 0x01 - snake head up   */
0x3C,0x3C,0x7E,0x7E,0x7E,0x3C,0x3C,0x18, /*  - 0x02 - snake head down */
0x00,0x1C,0x7F,0xFF,0xFF,0x7F,0x1C,0x00, /*  - 0x03 - snake head left */
0x00,0x38,0xFE,0xFF,0xFF,0xFE,0x38,0x00, /*  - 0x04 - snake head right*/
0x04,0x68,0x37,0x7F,0x7F,0x7F,0x7F,0x3E, /*  - 0x05 - apple           */
0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x3C,0x3C, /*  - 0x06 - top T           */
0x3C,0x3C,0xFF,0xFF,0xFF,0xFF,0x00,0x00, /*  - 0x07 - bottom T        */
0x3C,0x3C,0xFC,0xFC,0xFC,0xFC,0x3C,0x3C, /*  - 0x08 - right T         */
0x3C,0x3C,0x3F,0x3F,0x3F,0x3F,0x3C,0x3C, /*  - 0x09 - left T          */
0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00, /*  - 0x0a - horizontal      */
0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C, /*  - 0x0b - vertical        */
0x7E,0xFF,0xC3,0xDB,0xDB,0xC3,0xFF,0x7E, /*  - 0x0c - tetris block   1 CYAN I*/
0x00,0x00,0x3F,0x3F,0x3F,0x3F,0x3C,0x3C, /*  - 0x0d - top left cnr    */
0x00,0x00,0xFC,0xFC,0xFC,0xFC,0x3C,0x3C, /*  - 0x0e - top right cnr   */
0x3C,0x3C,0x3F,0x3F,0x3F,0x3F,0x00,0x00, /*  - 0x0f - bottom left cnr */
0x3C,0x3C,0xFC,0xFC,0xFC,0xFC,0x00,0x00, /*  - 0x10 - bottom right cnr*/
0x7E,0xFF,0xC3,0xDB,0xDB,0xC3,0xFF,0x7E, /*  - 0x11 - tetris block    2 DARK BLUE J*/
0x7E,0xFF,0xC3,0xDB,0xDB,0xC3,0xFF,0x7E, /*  - 0x12 - tetris block    3 ORANGE L*/
0x7E,0xFF,0xC3,0xDB,0xDB,0xC3,0xFF,0x7E, /*  - 0x13 - tetris block    4 YELLOW O*/
0x7E,0xFF,0xC3,0xDB,0xDB,0xC3,0xFF,0x7E, /*  - 0x14 - tetris block    5 GREEN S*/
0x7E,0xFF,0xC3,0xDB,0xDB,0xC3,0xFF,0x7E, /*  - 0x15 - tetris block    6 RED Z*/
0x7E,0xFF,0xC3,0xDB,0xDB,0xC3,0xFF,0x7E, /*  - 0x16 - tetris block    7 MAGENTA T*/
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F, /*  DB 017H, */
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F, /*  DB 018H, */
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F, /*  DB 019H, */
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F, /*  DB 01AH, */
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F, /*  DB 01BH, */
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F, /*  DB 01CH, */
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F, /*  DB 01DH, */
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F, /*  DB 01EH, */
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F, /*  DB 01FH, */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*  DB 020H, */
0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x00, /*  DB 021H, */
0x6C,0x6C,0x00,0x00,0x00,0x00,0x00,0x00, /*  DB 022H, */
0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00, /*  DB 023H, */
0x7C,0xD6,0xD0,0x7C,0x16,0xD6,0x7C,0x00, /*  DB 024H, */
0xC6,0xCE,0x1C,0x38,0x70,0xE6,0xC6,0x00, /*  DB 025H, */
0x38,0x6C,0x6C,0x30,0xDA,0xCC,0x76,0x00, /*  DB 026H, */
0x38,0x38,0x18,0x70,0x00,0x00,0x00,0x00, /*  DB 027H, */
0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x00, /*  DB 028H, */
0x60,0x30,0x18,0x18,0x18,0x30,0x60,0x00, /*  DB 029H, */
0x92,0x54,0x38,0xFE,0x38,0x54,0x92,0x00, /*  DB 02AH, */
0x00,0x18,0x18,0x7E,0x7E,0x18,0x18,0x00, /*  DB 02BH, */
0x00,0x00,0x00,0x00,0x38,0x38,0x18,0x70, /*  DB 02CH, */
0x00,0x00,0x00,0x3C,0x3C,0x00,0x00,0x00, /*  DB 02DH, */
0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x00, /*  DB 02EH, */
0x06,0x0E,0x1C,0x38,0x70,0xE0,0xC0,0x00, /*  DB 02FH, */
0x7C,0xC6,0xCE,0xFE,0xF6,0xC6,0x7C,0x00, /*  DB 030H, */
0x18,0x38,0x18,0x18,0x18,0x18,0x3C,0x00, /*  DB 031H, */
0x7C,0xCE,0xCE,0x1C,0x38,0x70,0xFE,0x00, /*  DB 032H, */
0x7C,0xC6,0x06,0x1C,0x06,0xC6,0x7C,0x00, /*  DB 033H, */
0x0C,0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x00, /*  DB 034H, */
0xFE,0xC0,0xFC,0xC6,0x06,0xC6,0x7C,0x00, /*  DB 035H, */
0x7C,0xC6,0xC0,0xFC,0xC6,0xC6,0x7C,0x00, /*  DB 036H, */
0xFE,0xCE,0x0C,0x18,0x38,0x38,0x38,0x00, /*  DB 037H, */
0x7C,0xC6,0xC6,0x7C,0xC6,0xC6,0x7C,0x00, /*  DB 038H, */
0x7C,0xC6,0xC6,0x7E,0x06,0xC6,0x7C,0x00, /*  DB 039H, */
0x38,0x38,0x38,0x00,0x38,0x38,0x38,0x00, /*  DB 03AH, */
0x38,0x38,0x38,0x00,0x38,0x18,0x18,0x00, /*  DB 03BH, */
0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00, /*  DB 03CH, */
0x00,0x7C,0x7C,0x00,0x7C,0x7C,0x00,0x00, /*  DB 03DH, */
0x60,0x30,0x18,0x0C,0x18,0x30,0x60,0x00, /*  DB 03EH, */
0x7C,0xC6,0xCC,0x18,0x18,0x00,0x18,0x00, /*  DB 03FH, */
0x7C,0x82,0xBA,0x8A,0xBA,0xAA,0x94,0x00, /*  DB 040H, */
0x38,0x6C,0xC6,0xC6,0xFE,0xC6,0xC6,0x00, /*  DB 041H, */
0xFC,0xC6,0xC6,0xFC,0xC6,0xC6,0xFC,0x00, /*  DB 042H, */
0x7C,0xC6,0xC0,0xC0,0xC0,0xC6,0x7C,0x00, /*  DB 043H, */
0xF8,0xCC,0xC6,0xC6,0xC6,0xCC,0xF8,0x00, /*  DB 044H, */
0xFE,0xC0,0xC0,0xF8,0xC0,0xC0,0xFE,0x00, /*  DB 045H, */
0xFE,0xC0,0xC0,0xF8,0xC0,0xC0,0xC0,0x00, /*  DB 046H, */
0x7C,0xC6,0xC0,0xC0,0xCE,0xC6,0x7E,0x00, /*  DB 047H, */
0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00, /*  DB 048H, */
0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00, /*  DB 049H, */
0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00, /*  DB 04AH, */
0xC6,0xCC,0xD8,0xF0,0xD8,0xCC,0xC6,0x00, /*  DB 04BH, */
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFE,0x00, /*  DB 04CH, */
0xC6,0xFE,0xFE,0xD6,0xC6,0xC6,0xC6,0x00, /*  DB 04DH, */
0xE6,0xE6,0xF6,0xD6,0xDE,0xCE,0xCE,0x00, /*  DB 04EH, */
0x7C,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00, /*  DB 04FH, */
0xFC,0xC6,0xC6,0xFC,0xC0,0xC0,0xC0,0x00, /*  DB 050H, */
0x7C,0xC6,0xC6,0xC6,0xDE,0xCC,0x7E,0x00, /*  DB 051H, */
0xFC,0xC6,0xC6,0xFC,0xD8,0xCC,0xC6,0x00, /*  DB 052H, */
0x7C,0xC6,0xC0,0x7C,0x06,0xC6,0x7C,0x00, /*  DB 053H, */
0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x00, /*  DB 054H, */
0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00, /*  DB 055H, */
0xC6,0xC6,0xC6,0x6C,0x6C,0x38,0x38,0x00, /*  DB 056H, */
0xC6,0xC6,0xC6,0xD6,0xD6,0xFE,0x6C,0x00, /*  DB 057H, */
0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00, /*  DB 058H, */
0x66,0x66,0x66,0x3C,0x18,0x18,0x18,0x00, /*  DB 059H, */
0xFE,0x0E,0x1C,0x38,0x70,0xE0,0xFE,0x00, /*  DB 05AH, */
0x78,0x60,0x60,0x60,0x60,0x60,0x78,0x00, /*  DB 05BH, */
0x3C,0x42,0x99,0xA1,0xA1,0x99,0x42,0x3C, /*  DB 05CH, */
0x78,0x18,0x18,0x18,0x18,0x18,0x78,0x00, /*  DB 05DH, */
0x38,0x6C,0xC6,0x00,0x00,0x00,0x00,0x00, /*  DB 05EH, */
0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x7E, /*  DB 05FH, */
0x15,0x35,0x75,0xF5,0x75,0x35,0x15,0x00, /*  DB 060H, */
0x00,0x00,0x3C,0x06,0x3E,0x66,0x3E,0x00, /*  DB 061H, */
0x60,0x60,0x7C,0x66,0x66,0x66,0x7C,0x00, /*  DB 062H, */
0x00,0x00,0x3C,0x66,0x60,0x66,0x3C,0x00, /*  DB 063H, */
0x06,0x06,0x3E,0x66,0x66,0x66,0x3E,0x00, /*  DB 064H, */
0x00,0x00,0x3C,0x66,0x7E,0x60,0x3E,0x00, /*  DB 065H, */
0x1C,0x36,0x30,0x78,0x30,0x30,0x30,0x00, /*  DB 066H, */
0x00,0x00,0x3E,0x66,0x3E,0x06,0x66,0x3C, /*  DB 067H, */
0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0x00, /*  DB 068H, */
0x18,0x00,0x18,0x18,0x18,0x18,0x18,0x00, /*  DB 069H, */
0x06,0x00,0x06,0x06,0x06,0x06,0x66,0x3C, /*  DB 06AH, */
0x60,0x60,0x66,0x6C,0x78,0x6C,0x66,0x00, /*  DB 06BH, */
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00, /*  DB 06CH, */
0x00,0x00,0x6C,0xFE,0xD6,0xD6,0xD6,0x00, /*  DB 06DH, */
0x00,0x00,0x5C,0x7E,0x66,0x66,0x66,0x00, /*  DB 06EH, */
0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7C,0x00, /*  DB 06FH, */
0x00,0x00,0x7C,0x66,0x66,0x7C,0x60,0x60, /*  DB 070H, */
0x00,0x00,0x7C,0xCC,0xCC,0x7C,0x0C,0x0E, /*  DB 071H, */
0x00,0x00,0x6C,0x76,0x60,0x60,0x60,0x00, /*  DB 072H, */
0x00,0x00,0x3C,0x60,0x38,0x0C,0x78,0x00, /*  DB 073H, */
0x18,0x18,0x3C,0x18,0x18,0x18,0x18,0x00, /*  DB 074H, */
0x00,0x00,0x66,0x66,0x66,0x66,0x3C,0x00, /*  DB 075H, */
0x00,0x00,0x66,0x66,0x66,0x3C,0x18,0x00, /*  DB 076H, */
0x00,0x00,0xC6,0xC6,0xD6,0xFE,0x6C,0x00, /*  DB 077H, */
0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00, /*  DB 078H, */
0x00,0x00,0x66,0x66,0x66,0x3C,0x18,0x70, /*  DB 079H, */
0x00,0x00,0x7E,0x0C,0x18,0x30,0x7E,0x00, /*  DB 07AH, */
0x18,0x30,0x30,0x70,0x30,0x30,0x18,0x00, /*  DB 07BH, */
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00, /*  DB 07CH, */
0x60,0x30,0x30,0x38,0x30,0x30,0x60,0x00, /*  DB 07DH, */
0xA8,0xAC,0xAE,0xAF,0xAE,0xAC,0xA8,0x00, /*  DB 07EH, */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00  /*  DB 07FH  */
};
