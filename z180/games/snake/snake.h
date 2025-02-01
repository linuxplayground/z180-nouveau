// These patterns have been redefined in patterns.h
#define HEAD_UP    0x01
#define HEAD_DOWN  0x02
#define HEAD_LEFT  0x03
#define HEAD_RIGHT 0x04
#define APPLE      0x05

// Globals
int16_t buffer_head, buffer_tail;
uint16_t score;
char score_str[16];
uint16_t high_score;
char high_score_str[16];
uint16_t saved_high_score;

uint8_t more_segments=4;  //Number of segments to add
uint8_t segments;         //Variable contianing number of segments to add during current game tick

uint8_t ticks;
uint8_t game_speed;

uint8_t applechar = APPLE;

uint8_t level;
bool pause = true;
bool crashed = false;

struct {
    int8_t x;
    int8_t y;
    uint8_t dir;
    uint8_t pattern;
} head;

struct {
    int8_t x;
    int8_t y;
} apple;

uint8_t level1[4 + 1] = {
        4,      4,12,27,12
};

uint8_t level2[12 + 1] = {
        12,     4,12,27,12,
                8,3,8,12,
                23,12,23,20
};

uint8_t level3[24 + 1] = {
        24,     4,4,14,4,
                17,4,27,4,
                4,19,14,19,
                17,19,27,19,
                4,4,4,19,
                27,4,27,19
};

uint8_t level4[24 + 1] = {
        24,     3,4,24,4,
                3,4,3,19,
                6,19,27,19,
                27,19,27,4,
                21,4,21,16,
                9,7,9,19,
};


uint8_t *levels[4] = {level1, level2, level3, level4};

#define BUFFSIZE 0x600
int8_t circularBuffer[BUFFSIZE] = { 0 };
