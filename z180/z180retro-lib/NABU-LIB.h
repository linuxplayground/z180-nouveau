// ****************************************************************************************
// I HAVE STRIPPED OUT A LOT OF THIS LIBRARY THAT'S NOT NEEDED ON THE NOUVEAU.  I HAVE BEEN
// LESS DILLIGENT ABOUT REMOVING DJ SURES COMMENTS
// ****************************************************************************************
//
// ****************************************************************************************
// NABU-LIB C Library - MAKE SOMETHING
// DJ Sures (c) 2023
// https://nabu.ca
// 
// Last updated on March 22, 2023 (v2023.03.22.00)
// 
// Get latest copy and examples from: https://github.com/DJSures/NABU-LIB
// 
// This is a z88dk C library for the NABU Personal Computer. This is a large library
// with many functions for the VDP, Sound, HCCA, and Keyboard. The functions are split
// into sections based on the peripheral.  
// 
// Read the summaries below for details of each function in this file.
//
// ----------------------------------------------------------------------------------------------
// GETTING STARTED
// There is a SKELETON project in my GitHub that I recommend you begin with. The skeleton project
// contains the framework that you can start with by following one of my online tutorials in
// YouTube.
// ----------------------------------------------------------------------------------------------
//
// Make something,
// DJ Sures
// 
// **********************************************************************************************

// No touch
// -----------------------
#ifndef NABU_H
#define NABU_H
#define BIN_HOMEBREW 100
#define BIN_CPM 200
#define byte uint8_t


// **************************************************************************
// 
// BINARY TYPE
// ===========
// It is important to define what kind of binary we are going to be creating.
// Add one of these two options to the top of your main.c before the #include
// statements.
//
// HOMEBREW
// --------
// This binary is executable as a standalone application from the NABU
// Internet Adapter or as a NABU Channel. Compiling for HOMEBREW uses
// the following example commandline:
//
//    zcc +nabu -vn --list -m -create-app -compiler=sdcc -O3 --opt-code-speed main.c -o "000001.nabu"
//
//
// Cloud CP/M
// ----------
// A binary that produces a .COM executable which will be run on the
// Cloud CP/M Operating System. If you decide to create a HOMEBREW program,
// but also want the same code to work in CPM, you can set this to HOMEBREW
// and not use any CPM specific calls (i.e. printf). You would also need to
// use the NABULIB keyboard & vdp. Compiling for CPM uses teh example
// commandline:
//
//     zcc +cpm -vn --list -m -create-app -compiler=sdcc -O3 --opt-code-speed main.c -o "APPNAME"
//
// In addition to the commandline for CPM binaries, the z88dk allows you to fine-tune
// what features are enabled. You can add each #pragma option to the top of your main.c
// to disable that feature and save filesize and RAM.
//
//    Disable stdio. Useful if not using DISABLE_VDP, and therefore you're using only the CPM built-in functions.
//    #pragma output nostreams
//
//    No FILEIO. This disables all ability to read/write CPM files
//    #pragma output nofileio
//
//    Strip the MS-DOS protection header (recommended because ain't nobody got time for that)
//    #pragma output noprotectmsdos
//
//    Do not insert the file redirection option while parsing the command line arguments (useless if “nostreams” is set)
//    #pragma output noredir
//
//    No global variables for graphics (recommended because you'll be using NABULIB for graphics)
//    #pragma output nogfxglobals
//
// **************************************************************************
// #define BIN_TYPE BIN_HOMEBREW
// #define BIN_TYPE BIN_CPM


// **************************************************************************
// 
// CONFIGURE FONT or PATTERN TABLE
// ===============================
// 
// If you will be using the VDP, you will need either a default font or pattern table.
// Loading just a font is smaller than an entire pattern table, but both options are
// available to you. For just a textmode, that doesn't use CP/M's stdio, then you can
// use vdp_loadASCIIFont() and supply an existing pattern.h font, or your custom one.
//
// The diference between a FONT and a PATTERN is the size. A FONT is just the visible 
// written 127 ASCII characters, starting at ASCII Decimal 37 (space bar). The PATTERN
// is the entire pattern memory (256 characters) that include text and image patterns.
// Generaly, if you're just using text, then load the vdp_loadASCIIFont() which can be used in
// both G2 and Text mode. If you are using a pattern, check the VDP section for the 
// load pattern functions.
//
//
// USE ONE OF OUR FONTS
// --------------------
// 1) Include the "patterns.h" in your file #include "patterns.h"
//
// 2) Add one of these #define's into your main.c program.
// #define FONT_AMIGA
// #define FONT_SET1
// #define FONT_STANDARD
// #define FONT_LM80C
//
// 3) call vdp_loadASCIIFont(ASCII);
//
//
// USE YOUR CUSTOM FONT
// --------------------
// If you with to use your own font, specify the font as:
//
//    const uint8_t[768] ASCII = {} 
//
// Once your font has been created, add it with vdp_loadASCIIFont(ASCII);
//
// *Note: You do not need to include a font if DISABLE_VDP is set and you're
//        building a text-only cp/m program that uses stdio.
// **************************************************************************


// **************************************************************************
// 
// KEYBOARD INPUT TYPE
// ===================
// 
// This disables the NABULIB keyboard input commands (i.e. isKeyPressed(), getChar(), readLine()).
// When you disable the NABULIB keyboard input commands, you will have to use the CPM
// input commands through stdio.h or conio.h
//
// If you are using CPM stdio, such as gets(), stdio.h or conio.h, you will need to 
// disable the keyboard interupt in NABULIB. Add this #define above your 
// #include in the main.c
//
// **************************************************************************
// #define DISABLE_KEYBOARD_INT


// **************************************************************************
// 
// HCCA (SERIAL)
// =============
// 
// If your program is not using the file store or HCCA for retronet, you can
// disable the RX interrupt to save filesize.
//
//
// Add this #define above your #include in the main.c to disable the HCCA RX INT
// **************************************************************************
// #define DISABLE_HCCA_RX_INT


// **************************************************************************
// 
// VDP GRAPHICS
// ============
// 
// You can disable the vdp functions if you're just using the cpm built-in
// console stuff, like puts() or printf(), etc.
//
// Add this #define above your #include in the main.c to disable the VDP commands
// **************************************************************************
// #define DISABLE_VDP


// **************************************************************************
// 
// DEBUG VDP INT
// =============
// 
// You can enable a debug to see if your code takes too long before the vdp interrupt
// triggers. You see, you should only update the VDP before or after an interrupt.
// Ideally directly after. This ensures the VDP ram is all happy comfortable for the
// VDP to render it for display. If your code takes too long and an interrupt triggers,
// you can see if that happens by adding this #define above the #include in main.c.
// This will cause the ALERT LED to flash if the vdp int was triggered before calling
// vdp_waitVDPReadyInt().

// If you run into problems where the code is taking longer than a screen refresh vdp
// interrupt, you can skip the "missed" interrupt and wait for the next. This can be
// done by adding a vdpIsReady = false; before you call vdp_waitVDPReadyInt(void);

//
// *Note: You do not need this enabled when your program is released because it does
//        take a few instructions to run.
//
// Add this #define above your #include in the main.c to debug VDP Interrupt
// **************************************************************************
// #define DEBUG_VDP_INT


// **************************************************************************
//
// DISABLE CURSOR
// ==============
//
// You can disable the cursor by putting this line above the #include in your main.c
// This can only disable the VDP NABULIB cursor, not the CPM cursor.
// Meaning, it will disable the cursor for NABULIB key input commands, like getChar()
// **************************************************************************
// #define DISABLE_CURSOR


// **************************************************************************
// The cursor that will be displayed with getChar() and readLine()
// You can override this value by defining it before the #include in your main.c
//
// Note: This is only valid when using the nabulib vdp and keyboard interupts. It has
//       no effect on the CPM cursor, because that is handled by the BIOS.
// **************************************************************************
#ifndef CURSOR_CHAR
#define CURSOR_CHAR '_'
#endif


// **************************************************************************
//
//                READ BELOW FOR FUNCTION HELP BUT NO EDIT
//
// **************************************************************************

#ifndef BIN_TYPE
  #error A BIN_TYPE has not been specified. Look at the NABU-LIB.h to configure your application.
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


// **************************************************************************
// Special Function Registers
// --------------------------
// 
// These are special function register definitions where you can read and write
// values to the ports. using these compiles to one line of assembly, OUT or IN,
// which generates effecient assembly.
// 
// *Note: For example, to send a value to PORTA
// 
// IO_AYLATCH = IOPORTA;
// IO_AYDATA = 0x04;
// 
// *Note: For example to retrieve a value from PORTB
// 
// IO_LATCH = IOPORTB;
// return IO_AYDATA;
// 
// **************************************************************************

__sfr __at 0x80 IO_VDPDATA;
__sfr __at 0x81 IO_VDPLATCH;

// Used for getting the r register from the z80 to seed srand()
volatile uint8_t _randomSeed = 0;

/*
* DL: 2023-03-24
* The assumption here is that games for the NABU will not disable the keyboard as they want Joystick Events.
* So we piggy back off this same condition to define the Z80 Retro Joystick port if target is set to Z80_RETRO
*/

volatile uint8_t _kbdBuffer[256];
volatile uint8_t _kbdBufferReadPos = 0;
volatile uint8_t _kbdBufferWritePos = 0;
volatile uint8_t _lastKeyboardIntVal = 0;
volatile uint8_t _joyStatus[4] = {0};

typedef enum JOYSTICKENUM {
  Joy_Left   = 0b00000100,
  Joy_Down   = 0b01000000,
  Joy_Right  = 0b00100000,
  Joy_Up     = 0b10000000,
  Joy_Button = 0b00000001,
};

volatile __sfr __at 0xA8 IO_JOY0;
volatile __sfr __at 0xA9 IO_JOY1;

// **************************************************************************
// VDP Variables
// -------------
// 
// These are variables and definitions for the VDP functions, such as
// cursor location, screen width/height for text calculations, and 
// the text buffer.
// 
// **************************************************************************

#define VDP_MODE 11
#define VDP_CSW 10
#define VDP_CSR 9
#define VDP_RESET 8
#define VDP_R1_IE 0x20
#define VDP_R1_M1 0x10
#define VDP_R1_M2 0x08
#define VDP_R1_SIZE 0x02
#define VDP_R1_MAG 0x01

// **************************************************************************
// Double buffer for text mode scrolling.
// This is because reading and writing the VDP vram is very slow
// and it is quicker to keep 960 bytes in RAM to double buffer
// the text mode.
// **************************************************************************
#define TEXT_BUFFER_SIZE 768
volatile uint8_t _vdp_textBuffer[TEXT_BUFFER_SIZE]; // row * col = 960 bytes


// **************************************************************************
// The current position of the cursor used by textmode
// functions. Such as vdp_write() and vdp_print() and
// vdp_newLine().
// **************************************************************************
struct {
  uint8_t x;
  uint8_t y;
} vdp_cursor = { 0, 0 };


// **************************************************************************
// The original value of the VDP Register 1 (i.e. graphic mode, memory, and interrupt status).
// This is used for enabling/disabling interrupts progrmatically because we can't re-read
// resgister 1 because they are write-only.
// **************************************************************************
volatile uint8_t _vdpReg1Val = 0;

// The sprite attribute table starting addres
uint16_t _vdpSpriteAttributeTableAddr;

// The sprite generator table starting address
uint16_t _vdpSpriteGeneratorTableAddr;

// Is the sprite size normal sized (false = 8x8) or double sized (true = 16x16)
bool _vdpSpriteSizeSelected;

// The tile pattern name table starting address
uint16_t _vdpPatternNameTableAddr;

// The tile color table starting address
uint16_t _vdpColorTableAddr;

// The tiles generator table starting address
uint16_t _vdpPatternGeneratorTableAddr;

// The max horizontal cursor position (i.e. 39 for text mode or 31 for graphics modes)
uint8_t _vdpCursorMaxX;

// The max horizontal cursor count (i.e. 40 for text mode or 32 for graphics modes)
uint8_t _vdpCursorMaxXFull;

// The max vertical line position (always 23)
const uint8_t _vdpCursorMaxY = 23;

// The max vertical line count (always 24)
const uint8_t _vdpCursorMaxYFull = 24;

// The size of the double buffer (_vdp_textBuffer) size that's used (i.e. 768 for graphic modes, 960 for text mode)
uint16_t _vdpTextBufferSize;

// The current VDP mode (text or graphic)
uint8_t _vdpMode;

// Is auto scroll enabled? Will auto scroll when using vdp_write() or vdp_print() or vdp_newline()
bool _autoScroll;

// Are the vdp interrupts enabled?
bool _vdpInterruptEnabled = false;


// **************************************************************************
// Colors for the VDP fgColor or bgColor settings
// **************************************************************************
enum VDP_COLORS {
  VDP_TRANSPARENT = 0,
  VDP_BLACK = 1,
  VDP_MED_GREEN = 2,
  VDP_LIGHT_GREEN = 3,
  VDP_DARK_BLUE = 4,
  VDP_LIGHT_BLUE = 5,
  VDP_DARK_RED = 6,
  VDP_CYAN = 7,
  VDP_MED_RED = 8,
  VDP_LIGHT_RED = 9,
  VDP_DARK_YELLOW = 10,
  VDP_LIGHT_YELLOW = 11,
  VDP_DARK_GREEN = 12,
  VDP_MAGENTA = 13,
  VDP_GRAY = 14,
  VDP_WHITE = 15
};


// **************************************************************************
// Available graphic/text modes for the VDP
// **************************************************************************
enum VDP_MODES {
  VDP_MODE_G1 = 1,
};


// **************************************************************************
// The direction to move the cursor that some VDP functions will accept.
// **************************************************************************
enum VDP_CURSOR_DIR {
  VDP_CURSOR_UP = 0,
  VDP_CURSOR_DOWN = 1,
  VDP_CURSOR_LEFT = 2,
  VDP_CURSOR_RIGHT = 3
};

// Collision flag for vdp
#define VDP_FLAG_COLLISION 0b00100000

// 5th sprite flag, set when more than 4 sprite per line 
#define VDP_FLAG_S5 0b01000000


// **************************************************************************
// Generics
// --------
//
// Here are some helper functions that are useful when 
//
// **************************************************************************

#define Max(x,y) (((x) >= (y)) ? (x) : (y))

#define Min(x,y) (((x) <= (y)) ? (x) : (y))


// **************************************************************************
// System
// ------
// 
// NABU helper functions.
// **************************************************************************

// **************************************************************************
// Initialize the NABU-LIB. This should be the very first thing in your program.
// Based on your configuration, this will initialize what you have not "#define DISABLE_X"
// This will enable the audio, HCCA RX & keyboard Interupts, seed random generator, and disable the ROM
// **************************************************************************
void initNABULib(void);

// **************************************************************************
// Disable interrupts on the nabu
// **************************************************************************
inline void NABU_DisableInterrupts(void);

// **************************************************************************
// Enable interrupts on the nabu
// **************************************************************************
inline void NABU_EnableInterrupts(void);

// **************************************************************************
// Perform one NOP
// **************************************************************************
inline void nop(void);


// **************************************************************************
// Keyboard
// --------
// 
// Get keys from the keyboard, which is also the joysticks.
// 
// **************************************************************************

// **************************************************************************
// Returns false if no key has been pressed, otherwise it returns the key value
// **************************************************************************
uint8_t isKeyPressed(void);

// **************************************************************************
// Blocks and waits for a key, returns that key value
// **************************************************************************
uint8_t getChar(void);

// **************************************************************************
// Read a line of text inputed by the keyboard. This does not null terminate the
// user input. If you need the input null terminated, make the maxInputLen one byte
// less than the buffer size, and manually set the 0x00 yourself after the return.
// 
// - buffer is the pointer to store the text input
// - maxInputLen is the max length of data you want to retrieve (no larger than the buffer!)
// 
// Returns the length of data entered by the user. 
// **************************************************************************
uint8_t readLine(uint8_t* buffer, uint8_t maxInputLen);


// **************************************************************************
// VDP
// ---
// 
// Start by calling one of the graphic modes that you wish to initialize.
// 
// *Note: Read about the function in this file to see if it's compatible 
// with your graphic mode. Some text functions, such as scroll up, are only
// available in text mode.
// **************************************************************************

// **************************************************************************
// For directly writing and reading from IO_VDPDATA and writing registers
// **************************************************************************
inline void vdp_setRegister(uint8_t registerIndex, uint8_t value);
inline void vdp_setWriteAddress(uint16_t address) __z88dk_fastcall;
inline void vdp_setReadAddress(uint16_t address) __z88dk_fastcall;

// **************************************************************************
// at a constant and acceptable speed. You can call the vdp_waitVDPReadyInt() to synchronize
// the program with the VDP interrupt speed. This is also necessary when drawing to the vdp
// in any graphic modes. Text mode does not require the vdp interrupt, but graphic modes do.
// This is because the grahic modes use multiple memory addresses for colors, patterns,
// and sprites which must be synchronized.
//
// *NOTE: to verify that your main code is not exceeding the available time between vdp interrupts,
//        you can temporarily enable the #define DEBUG_VDP_INT at the top of your main.c before #includes.
//        Scroll the top of this header file to read about DEBUG_VDP_INT and how to use it.
//
// If you run into problems where the code is taking longer than a screen refresh vdp
// interrupt, you can skip the "missed" interrupt and wait for the next. This can be
// done by adding a vdpIsReady = false; before you call vdp_waitVDPReadyInt(void);
//
// The following variables will be set from an interrupt.
//
// 1) uint8_t  vdpStatusRegVal - contains the value of the VDP Status Register (Check TMS9918a manual for collision bit)
// 2) bool     vdpIsReady      - TRUE if the VDP has just completed a vsync. But you will normally not
//                                use this because you'll be calling vdp_waitVDPReadyInt()
//
// Here is an example of how to use this...
//
// void main() {
//
//   // init the nabu lib library
//   initNABULib(void);
//
//   // switch to the graphic mode 
//   vdp_initG2Mode(0, true, false, false, false);
//
//   // enable the VDP sync
//   vdp_enableVDPReadyInt(void);
//
//   while (!isKeyPressed()) {
//
//     // do a bunch of expensive processing here
//     // i.e. calculate where the characters are gonna be
//     //      check for collisions and stuff
//
//     if (vdpStatusRegVal & VDP_FLAG_COLLISION) 
//       doCollisionThings(void);
//
//     // wait for the vsync
//     vdp_waitVDPReadyInt(void);
//
//     // update the sprites and other screen stuff
//   }
//
//   // remove the vdp sync
//   vdp_disableVDPReadyInt(void);
// }
//
//
// **************************************************************************
inline void vdp_waitVDPReadyInt(void);

void vdp_init(uint8_t mode, uint8_t fgColor, uint8_t bgColor, bool big_sprites, bool magnify, bool autoScroll, bool splitThirds);

// **************************************************************************
// Clear all VRAM set to 0's
// **************************************************************************
void vdp_clearVRAM(void);

// **************************************************************************
// Clears the screen
// **************************************************************************
void vdp_clearScreen(void);

// **************************************************************************
// Fills the screen with the character
// **************************************************************************
void vdp_fillScreen(uint8_t c) __z88dk_fastcall;

// **************************************************************************
// Clear the rows with 0x20 between topRow and bottomRow
// **************************************************************************
void vdp_clearRows(uint8_t topRow, uint8_t bottomRow);

// **************************************************************************
// This will update the vram to the specified font.
//
// A few fonts have been included in the pattern.h. You can include and define one of them to activate.
// After it has been defined, you will need to call this function and pass the ASCII value.
//
// For example...
// #define FONT_AMIGA
// vdp_loadASCIIFont(ASCII);
//
// Here are the included fonts if you include pattern.h
// ----------------------------------------------------
// #define FONT_AMIGA
// #define FONT_SET1
// #define FONT_STANDARD
// #define FONT_LM80C
//
// If you with to use your own font, specify the font as a const uint8_t[768] ASCII = {} in your code
// and pass it to this function.
//
// *Note: You must call this function if you're using text mode because it requires 
//        a font to be set
// **************************************************************************
void vdp_loadASCIIFont(uint8_t* font) __z88dk_fastcall;


// **************************************************************************
// Initialize vdp with the pattern table with an array of data. 
// A pattern table can also contain the font data if needed. If it includes
// a font, it must start at location 0x100, just like vdp_loadASCIIFont()
//
// *Note: your first pattern should be completely blank because it will be the
//        default pattern that is displayed on a clear screen (id 0)
// **************************************************************************
void vdp_loadPatternTable(uint8_t *patternTable, uint16_t len);


// **************************************************************************
// Initialize the vdp with the color table. 
// 
// *Note: The color of the first pattern should be black or what ever color you
//        want the screen background to be. Because the clear screen would have
//        a pattern value of 0, which will use its matching color pattern
// **************************************************************************
void vdp_loadColorTable(uint8_t *colorTable, uint16_t len);

// **************************************************************************
// Set foreground and background color of the pattern at the specified location
// 
// *Note: Only available in Graphic mode 2
//
// - x coordinate
// - y coordinate
// - fgcolor Foreground color
// - bgcolor Background color
// **************************************************************************
void vdp_colorizePattern(uint8_t patternId, uint8_t fg, uint8_t bg);

// **************************************************************************
// Place a pattern by the ID on X and Y in G2 mode. Also saves the pattern into
// the double buffer for screen scrolling.
//
// x:         x coordinate
// y:         y coordinate
// patternId: the # (id) of the pattern from the pattern generator table
// **************************************************************************
void vdp_putPattern(uint8_t x, uint8_t y, uint8_t patternId);

// **************************************************************************
// Print null terminated string at the current cursor position.
//
// - text Text to print
// **************************************************************************
void vdp_print(uint8_t* text) __z88dk_fastcall;

// **************************************************************************
// Print null terminated string at the current cursor position and change the
// color table for each character. 
//
// *Note: This only works on graphic mode G2 and will change the color of
// each character - so be careful how you use this!
// **************************************************************************
void vdp_printColorized(uint8_t* text, uint8_t fgColor, uint8_t bgColor);

// **************************************************************************
// Print the specified portion of the string at the current cursor position
// **************************************************************************
void vdp_printPart(uint16_t offset, uint16_t textLength, uint8_t* text);
  
// **************************************************************************
// Set backdrop border color
// **************************************************************************
inline void vdp_setBackDropColor(uint8_t) __z88dk_fastcall;

// **************************************************************************
//  Position the cursor at the specified position
//
// - col column
// - row row
// **************************************************************************
void vdp_setCursor2(uint8_t col, uint8_t row);

// **************************************************************************
//  Move the cursor along the specified direction
//
// - direction {VDP_CURSOR_UP|VDP_CURSOR_DOWN|VDP_CURSOR_LEFT|VDP_CURSOR_RIGHT}
// </summary
void vdp_setCursor(uint8_t direction) __z88dk_fastcall;

// **************************************************************************
//  set foreground and background color of the characters printed after this function has been called.
// In Text Mode and Graphics Mode 1, all characters are changed. In Graphics Mode 2, the escape sequence \\033[<fg>;<bg>m can be used instead.
// See vdp_print()
//
// - fg Foreground color
// - bg Background color
// **************************************************************************
void vdp_setTextColor(uint8_t fgcolor, uint8_t bgcolor);

// **************************************************************************
//  Write ASCII character at current cursor position and advances forward
//
// - chr Pattern at the respective location of the  pattern memory. Graphic Mode 1 and Text Mode: Ascii code of character
// **************************************************************************
void vdp_write(uint8_t chr) __z88dk_fastcall;

// **************************************************************************
// Add a new line (move down and to line start)
// **************************************************************************
void vdp_newLine(void);

// **************************************************************************
// Get the character in text mode at the specified location directly from VRAM, which is slow.
// You should use vdp_getCharAtLocationVRAM(), which will get the character from the double
// buffer without accessing VRAM.
// **************************************************************************
inline uint8_t vdp_getCharAtLocationVRAM(uint8_t x, uint8_t y);

// **************************************************************************
// In text mode, there is a buffer copy of the screen
// **************************************************************************
inline uint8_t vdp_getCharAtLocationBuf(uint8_t x, uint8_t y);

// **************************************************************************
// Set the character in memory buffer at location. This does not update the screen!
// It is used by the text scroll methods
// </summary
void vdp_setCharAtLocationBuf(uint8_t x, uint8_t y, uint8_t c);

// **************************************************************************
// Scroll all lines up between topRow and bottomRow
// **************************************************************************
void vdp_scrollTextUp(uint8_t topRow, uint8_t bottomRow);

// **************************************************************************
// Scroll all lines down between topRow and bottomRow
// **************************************************************************
  void vdp_scrollTextDown(uint8_t topRow, uint8_t bottomRow);

// **************************************************************************
// Write a character at the specified location
// **************************************************************************
void vdp_writeCharAtLocation(uint8_t x, uint8_t y, uint8_t c);

// **************************************************************************
// Display the binary value of the variable
// **************************************************************************
void vdp_writeUInt8ToBinary(uint8_t v) __z88dk_fastcall;

// **************************************************************************
// Display the binary value of the variable
// **************************************************************************
void vdp_writeUInt16ToBinary(uint16_t v) __z88dk_fastcall;

// **************************************************************************
// Display the binary value of the variable
// **************************************************************************
void vdp_writeUInt32ToBinary(uint32_t v) __z88dk_fastcall;

//Z80 Retro function to slow things down a bit
void vdp_put(uint8_t c) __z88dk_fastcall;


#include "NABU-LIB.c"
#endif
