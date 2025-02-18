uint8_t block_count = 0;
uint8_t used_blocks[7] = {0,0,0,0,0,0,0};
uint16_t high_score;
/*
* TETRONIMOS
*/

typedef struct {
        uint8_t first;
        uint8_t count;
} Tet;

// This little array gives us the first block and last block in each
// item's animation plus how many animation frames there are.
Tet tets[7] = {
        {0,1},          // BLOCK 0
        {1,4},          // I     1
        {5,4},          // S     2
        {9,4},          // Z     3
        {13,4},         // L     4
        {17,4},         // J     5
        {21,4}          // T     6
};

// To load one of these bad boys up, we will first index into `tets` like this:
// Tetronimo current_tet = tets[5];
// 
// Then we can retreive it's first frame block data.
// uint8_t current_frame = current_tet.first
// TETRONIMOS[current_frame]
//
// The next frame, (rotating clockwise - reverse this to go anti clockwise)
// current_frame ++;
// if (current_frame > current_tet.last) {
//      current_frame = current_tet.first;        
//}
//

const char TETRONIMOS[25][16] = {
        {       //BLOCK 0x13
                0x20,0x98,0x98,0x20,
                0x20,0x98,0x98,0x20,
                0x20,0x20,0x20,0x20,
                0x20,0x20,0x20,0x20
        },
        {       //I'1 0x0c
                0x20,0x20,0x20,0x20,
                0x80,0x80,0x80,0x80,
                0x20,0x20,0x20,0x20,
                0x20,0x20,0x20,0x20
        },
        {       // I'2 0x0c
                0x20,0x20,0x80,0x20,
                0x20,0x20,0x80,0x20,
                0x20,0x20,0x80,0x20,
                0x20,0x20,0x80,0x20
        },
        {       // I'3
                0x20,0x20,0x20,0x20,
                0x20,0x20,0x20,0x20,
                0x80,0x80,0x80,0x80,
                0x20,0x20,0x20,0x20
        },
        {       // I'4
                0x20,0x80,0x20,0x20,
                0x20,0x80,0x20,0x20,
                0x20,0x80,0x20,0x20,
                0x20,0x80,0x20,0x20
        },
        {       //S'1 0x14
                0x20,0xa0,0xa0,0x20,
                0xa0,0xa0,0x20,0x20,
                0x20,0x20,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //S'2
                0x20,0xa0,0x20,0x20,
                0x20,0xa0,0xa0,0x20,
                0x20,0x20,0xa0,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //S'3
                0x20,0x20,0x20,0x20,
                0x20,0xa0,0xa0,0x20,
                0xa0,0xa0,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //S'4
                0xa0,0x20,0x20,0x20,
                0xa0,0xa0,0x20,0x20,
                0x20,0xa0,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //Z'1 0x15
                0xa8,0xa8,0x20,0x20,
                0x20,0xa8,0xa8,0x20,
                0x20,0x20,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //Z'2
                0x20,0x20,0xa8,0x20,
                0x20,0xa8,0xa8,0x20,
                0x20,0xa8,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //Z'3
                0x20,0x20,0x20,0x20,
                0xa8,0xa8,0x20,0x20,
                0x20,0xa8,0xa8,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //Z'4
                0x20,0xa8,0x20,0x20,
                0xa8,0xa8,0x20,0x20,
                0xa8,0x20,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //L'1 0x12
                0x20,0x20,0x90,0x20,
                0x90,0x90,0x90,0x20,
                0x20,0x20,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //L'2
                0x20,0x90,0x20,0x20,
                0x20,0x90,0x20,0x20,
                0x20,0x90,0x90,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //L'3
                0x20,0x20,0x20,0x20,
                0x90,0x90,0x90,0x20,
                0x90,0x20,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //L'4
                0x90,0x90,0x20,0x20,
                0x20,0x90,0x20,0x20,
                0x20,0x90,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //J'1 0x11
                0x88,0x20,0x20,0x20,
                0x88,0x88,0x88,0x20,
                0x20,0x20,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //J'2
                0x20,0x88,0x88,0x20,
                0x20,0x88,0x20,0x20,
                0x20,0x88,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //J'3
                0x20,0x20,0x20,0x20,
                0x88,0x88,0x88,0x20,
                0x20,0x20,0x88,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //J'4
                0x20,0x88,0x20,0x20,
                0x20,0x88,0x20,0x20,
                0x88,0x88,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //T'1 0x16
                0x20,0xb0,0x20,0x20,
                0xb0,0xb0,0xb0,0x20,
                0x20,0x20,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //T'2
                0x20,0xb0,0x20,0x20,
                0x20,0xb0,0xb0,0x20,
                0x20,0xb0,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //T'3
                0x20,0x20,0x20,0x20,
                0xb0,0xb0,0xb0,0x20,
                0x20,0xb0,0x20,0x20,
                0x20,0x20,0x20,0x20,
        },
        {       //T'4
                0x20,0xb0,0x20,0x20,
                0xb0,0xb0,0x20,0x20,
                0x20,0xb0,0x20,0x20,
                0x20,0x20,0x20,0x20,
        }
};



/*
*  TETRIS MAP centred on the screen.
*/
const char MAP[480] = { // 21 x 24
        // 7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26
        0x0d,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x06,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0e, //  0
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, //  1
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, //  2
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, //  3
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, //  4
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, //  5
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, //  6
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x09,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x08, //  7
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, //  8
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, //  9
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 10
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 11
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 12
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 13
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 14
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x09,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x08, // 15
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 16
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 17
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 18
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x09,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x08, // 19
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 20
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 21
        0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0b, // 22
        0x0f,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x07,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x10  // 23
};
