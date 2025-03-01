// #define BIN_TYPE BIN_CPM <---- DEFINED IN MAKEFILE
#define DISABLE_HCCA_RX_INT
#define DISABLE_CURSOR

#include "NABU-LIB.h"
#include "nabu-games.h"
#include "tetris.h"

uint8_t block[8] = {0x7E,0xFF,0xC3,0xDB,0xDB,0xC3,0xFF,0x7E}; /*1  - 0x0c - tetris block   1 CYAN I*/
                    //   0     8    10    18    20    28   30     38    40    48    50    58    60    68   70    78     80    88    90    98    A0    A8    B0    B8    C0    C8    D0    D8    E0   E8    F0    F8
uint8_t colors[32] = {0x51, 0x51, 0x51, 0x51, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x51, 0x71, 0x41, 0x91, 0xB1, 0x31, 0x61, 0xD1, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 };
uint8_t tb[64];
uint8_t tb8[4];
uint8_t tb16[6];

void add_pattern(uint8_t * pat, uint8_t pat_num);

void initDisplay(void) {
    initNABULib();
    vdp_clearVRAM();
    vdp_initG1Mode(1, false, false, false, false); //uint8_t bgColor, bool bigSprites, bool scaleSprites, bool autoScroll, don't split thirds
    vdp_loadPatternTable(FAT,0x330);
    vdp_setBackDropColor(VDP_DARK_YELLOW);          //Set border color

    // place the block patterns for different colours in the gen table after 0x80
    add_pattern(block, 0x80);
    add_pattern(block, 0x88);
    add_pattern(block, 0x90);
    add_pattern(block, 0x98);
    add_pattern(block, 0xA0);
    add_pattern(block, 0xA8);
    add_pattern(block, 0xB0);

    vdp_loadColorTable(colors, 32);
}

void add_pattern(uint8_t* pat, uint8_t pat_num) {
    vdp_setWriteAddress(_vdpPatternGeneratorTableAddr + (pat_num * 8));
    for(uint8_t i=0; i<8; i++) {
        IO_VDPDATA = pat[i];
        nop();
        nop();
        nop();
    }
}

void setupMap(void) {
    //plot the map graphics
    uint8_t col = 7;
    uint8_t line = 0;
    for (int i = 0; i<480; i++) {

        // IO_VDPDATA = MAP[i];
        vdp_setCharAtLocationBuf(col, line, MAP[i]);

        col = col + 1;
        if (col > 26) {
            col = 7;
            line = line + 1;
        }
    }
    vdp_waitVDPReadyInt();
    vdp_refreshViewPort();

    //write the static words
    printAtLocationBuf(19,1,"NEXT");
    printAtLocationBuf(19,8,"SCORE");
    printAtLocationBuf(19,12,"H.SCORE");
    printAtLocationBuf(19,16,"LINES");
    printAtLocationBuf(19,20,"LEVEL");
    sprintf(tb16, "%d", high_score);
    printAtLocationBuf(20,14,tb16);
    vdp_waitVDPReadyInt();
    vdp_refreshViewPort();
}

void displayTet(uint8_t x, uint8_t y, uint8_t tet_index, uint8_t frame) {
    uint8_t idx = tets[tet_index].first + frame;
    for(uint8_t i = 0; i < 4; i ++) {
        for (uint8_t j = 0; j < 4; j ++) {
            if (TETRONIMOS[idx][i*4+j] != 0x20) {   //don't print spaces as they might delete existing stuff.
                vdp_setCharAtLocationBuf(x+j, y+i, TETRONIMOS[idx][i*4+j]);
            }
        }
    }
}

void clearTet(uint8_t x, uint8_t y, uint8_t tet_index, uint8_t frame) {
    uint8_t idx = tets[tet_index].first + frame;
    for(uint8_t i = 0; i < 4; i ++) {
        for (uint8_t j = 0; j < 4; j ++) {  // only delete when the block part is not a space.
            if (TETRONIMOS[idx][i*4+j] != 0x20) {
                vdp_setCharAtLocationBuf(x+j, y+i, 0x20);
            }
        }
    }
}

bool isSpaceFree(uint8_t x, uint8_t y, uint8_t tet_index, uint8_t frame) {
    uint8_t idx = tets[tet_index].first + frame;
    for(uint8_t i = 0; i < 4; i ++) {
        for (uint8_t j = 0; j < 4; j ++) {  // only check when block part is not a space.
            if (TETRONIMOS[idx][i*4+j] != 0x20) {
                if (vdp_getCharAtLocationBuf(x+j,y+i) != 0x20) {
                    return false;
                }
            }
        }
    }
    // if we get here, then there is space.
    return true;
}

void clearPlayArea(void) {
    for( uint8_t i = 1; i<23; i++) {
        for( uint8_t j = 8; j < 18; j ++ ) {
            vdp_setCharAtLocationBuf(j, i, 0x20);
        }
    }
}

void clearLinesAndDropDown(uint8_t line_num) __z88dk_fastcall {
    for( uint8_t j = 8; j < 18; j ++ ) {
        vdp_setCharAtLocationBuf(j, line_num, 0x20);
    }

    for ( uint8_t i = line_num; i > 1; i-- ) {
        for( uint8_t j = 8; j < 18; j ++ ) {
            vdp_setCharAtLocationBuf(j, i, vdp_getCharAtLocationBuf(j,i-1));
        }
    }
    for( uint8_t j = 8; j < 18; j ++ ) {
        vdp_setCharAtLocationBuf(1,j,0x20);
    }
}

uint8_t checkCompletedLines(uint8_t *lines) __z88dk_fastcall {
    uint8_t completed_lines = 0;
    bool complete;
    for( uint8_t i = 1; i<23; i++) {
        complete = true;
        for( uint8_t j = 8; j < 18; j ++ ) {
            if (vdp_getCharAtLocationBuf(j, i) == 0x20) {
                complete = false;
                break;
            }
        }
        if (complete) {
            lines[completed_lines] = i;     // store the completed line number in the lines array.
            completed_lines ++;
            if( completed_lines == 4 ) {      // We can't clear more than 4 lines at once.
                break;
            }
        }
    }
    return completed_lines;
}

int new_block(void) {
    //Reset used blocks if we hav
    if (block_count == 7) {
        for(uint8_t i=0; i<7; i++) {
            used_blocks[i] = 0;
        }
        block_count = 0;
    }
    uint8_t t;
    while(true) {
        t = rand()%7;   // choose first block
        if (!used_blocks[t])
            break;
    }
    block_count ++;
    used_blocks[t] = 1;
    return t;
}

void play(void) {
    uint8_t t = new_block();
    uint8_t n;
    int8_t f;
    bool running = true;
    uint16_t ticks = 0;
    uint16_t game_speed = 30;
    uint8_t lines[4];
    uint16_t score = 0;

    uint8_t level = 1;
    uint8_t cleared_lines = 0;
    uint8_t hard_drop_flag = 0;

    // Keep track of button and down so we can action down on release event
    // and not allow multiple rotate actions without a release between.
    uint8_t btn_state = 0;
    uint8_t dn_state = 0;

    sprintf(tb8, "%d", cleared_lines);
    printAtLocationBuf(20,18,tb8);

    sprintf(tb16, "%d", score);
    printAtLocationBuf(20,10,tb16);
    
    sprintf(tb16, "%d", high_score);
    printAtLocationBuf(20,14,tb16);

    sprintf(tb8, "%d", level);
    printAtLocationBuf(20,21,tb8);

    while (running) {
        n = new_block();
        f = 0;              // first frame.
        uint8_t x = 10;     // middle of play area
        uint8_t y = 1;      // top row of play area

        displayTet(21, 3, n, 0);
        displayTet(x,y,t,f);

        while (true) {
            vdp_waitVDPReadyInt();
            vdp_refreshViewPort();
            ticks ++;
#if 0
            if (ticks % 6 == 0) {  //only take joystick input every 6th tick (every 100ms)
                if (getJoyStatus() & Joy_Left) {
                    clearTet(x,y,t,f);
                    if(isSpaceFree(x-1,y,t,f)) {
                        x --;
                        displayTet(x,y,t,f);
                    } else {
                        displayTet(x,y,t,f);
                    }
                }
                if (getJoyStatus() & Joy_Right) {
                    clearTet(x,y,t,f);
                    if(isSpaceFree(x+1,y,t,f)) {
                        x ++;
                        displayTet(x,y,t,f);
                    } else {
                        displayTet(x,y,t,f);
                    }
                }
                if (getJoyStatus() & Joy_Down && dn_state == 0) {
                    game_speed = 1;     // cant be 0 because of modulus of game ticks.
                    dn_state = 1;
                    hard_drop_flag = 1; // add fallen lines to score during hard drop.
                    score = score + 1;  // the guidelines say, number of lines passed + 1
                }

                if (getJoyStatus() & Joy_Button && btn_state == 0) {
                    clearTet(x,y,t,f);
                    f ++;
                    if (f > tets[t].count-1) {
                        f = 0;
                    }

                    if (isSpaceFree(x,y,t,f)) {
                        displayTet(x,y,t,f);
                    } else {
                        f --;
                        if (f < 0) {
                            f = tets[t].count-1;
                        }
                        displayTet(x,y,t,f);
                    }
                    btn_state = 1;
                }
            } else {
                if (!(getJoyStatus() & Joy_Button)) {  // we try to know i the joystick is in nutral.
                    btn_state = 0;
                }
                if (!(getJoyStatus() & Joy_Down)) {
                    dn_state = 0;
                }
            }
#endif
            if (isKeyPressed()) {
                uint8_t key = getChar();
                if (key == ',') {
                    clearTet(x,y,t,f);
                    if(isSpaceFree(x-1,y,t,f)) {
                        x --;
                        displayTet(x,y,t,f);
                    } else {
                        displayTet(x,y,t,f);
                    }
                } else if (key == '.') {
                    clearTet(x,y,t,f);
                    if(isSpaceFree(x+1,y,t,f)) {
                        x ++;
                        displayTet(x,y,t,f);
                    } else {
                        displayTet(x,y,t,f);
                    }
                } else if (key == 'z') {
                    clearTet(x,y,t,f);
                    f --;
                    if (f < 0) {
                           f = tets[t].count-1;
                    }
                    if (isSpaceFree(x,y,t,f)) {
                        displayTet(x,y,t,f);
                    } else {
                        f ++;
                        if (f > tets[t].count-1) {
                            f = 0;
                        }
                        displayTet(x,y,t,f);
                    }
                } else if (key == 'x') {
                    clearTet(x,y,t,f);
                    f ++;
                    if (f > tets[t].count-1) {
                        f = 0;
                    }

                    if (isSpaceFree(x,y,t,f)) {
                        displayTet(x,y,t,f);
                    } else {
                        f --;
                        if (f < 0) {
                            f = tets[t].count-1;
                        }
                        displayTet(x,y,t,f);
                    }
                } else if (key == ' ') {
                    game_speed = 1;     // cant be 0 because of modulus of game ticks.
                    hard_drop_flag = 1; // guidelines state that score increases for each line passed in a hard drop
                    score = score + 1;  // guidelines state that score += 1 when hard dropping.
                } else if (key == 0x1b) {
                    running = false;
                    break;
                }
            }

            if (ticks % game_speed == 0) {  // game speed modifier
                clearTet(x,y,t,f);
                if (isSpaceFree(x, y + 1, t, f)) {
                    y++;
                    if(hard_drop_flag) {
                        score = score + 1;
                    }
                    displayTet(x, y, t, f);
                } else {
                    displayTet(x, y, t, f);
                    if(y==1) {
                        running = false;
                    }
                    break;
                }
            }
        }
        // Check for compelted lines
        uint8_t completed_lines = checkCompletedLines(lines);

        if(completed_lines > 0) {
            for(uint8_t i=0; i<completed_lines; i++) {
                clearLinesAndDropDown(lines[i]);
                cleared_lines ++;
                if (cleared_lines == 10) {
                    level = level + 1;
                    cleared_lines = 0;
                }
            }
            if (completed_lines == 1) {
                score = score + 40;
            } else if (completed_lines == 2) {
                score = score + 100;
            } else if (completed_lines == 3) {
                score = score + 300;
            } else if (completed_lines == 4) {
                score = score + 1200;
            }

            if(high_score < score) {
                high_score = score;
            }

            sprintf(tb16, "%d", score);
            printAtLocationBuf(20,10,tb16);

            sprintf(tb16, "%d", high_score);
            printAtLocationBuf(20,14,tb16);

            sprintf(tb8, "%d", cleared_lines);
            printAtLocationBuf(20,18,tb8);

            sprintf(tb8, "%d", level);
            printAtLocationBuf(20,21,tb8);
            vdp_waitVDPReadyInt();
            uint8_t tmp = IO_VDPLATCH; //Skip a frame. this clearing lines business is pretty slow.
        }
        clearTet(21, 3, n, 0);  //clear the next block ready for the new one.
        t = n;
        game_speed = 30-(3*level);
        hard_drop_flag = 0;          //always reset hard drop flag
        if (game_speed < 1)
            game_speed = 1;
    }

    // Running is false - lets pause a bit so the player can see their screen.
    // Show the final score.
    if(high_score < score) {
        high_score = score;
    }
    sprintf(tb16, "%d", score);
    printAtLocationBuf(20,10,tb16);

    sprintf(tb16, "%d", high_score);
    printAtLocationBuf(20,14,tb16);

    uint16_t timer = 0;
    while (timer < 180) { //3 seconds
        vdp_waitVDPReadyInt();
        timer ++;
    }
}

bool menu(void) {
    clearPlayArea();
    vdp_waitVDPReadyInt();
    vdp_refreshViewPort();

    printAtLocationBuf(8,3, "PRESS KEY");
    printAtLocationBuf(8,4,"TO START");
    printAtLocationBuf(8,7,",(<)  LEFT");
    printAtLocationBuf(8,8,".(>) RIGHT");
    printAtLocationBuf(8,9,"X & Z ROT");
    printAtLocationBuf(8,10,"SPACE DROP");
    printAtLocationBuf(13-(8/2),12,"JOYSTICK");
    printAtLocationBuf(13-(10/2),13,"BTN ROTATE");
    printAtLocationBuf(8,14,"DOWN DROP");
    printAtLocationBuf(8,17,"ESC QUIT");
    printAtLocationBuf(8,19,"PRODUCTION");
    printAtLocationBuf(8,20,"DAVE");
    printAtLocationBuf(8,21,"NOUVEAU");
    vdp_waitVDPReadyInt();
    vdp_refreshViewPort();

    while (true) {
#if 0
        if (getJoyStatus() & Joy_Button) {
            return true;
        }
#endif
        if (isKeyPressed()) {
            if (getChar() == 0x1b) {
                return false;
            } else {
                return true;
            }
        }
    }
}

void main(void) {
    initDisplay();
    setupMap();
    while(menu()) {
        setupMap();
        play();
    }
    #if BIN_TYPE == BIN_HOMEBREW
    __asm
        di
        rst 0x00
    __endasm;
    #else
    __asm
        jp 0
    __endasm;
    #endif
}
