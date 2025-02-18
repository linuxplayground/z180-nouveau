// ****************************************************************************************
// NABU-LIB C Library
// DJ Sures (c) 2023
// https://nabu.ca
// https://github.com/DJSures/NABU-LIB
// 
// Read the NABU-LIB.h file for details of each function in this file.
//
// **********************************************************************************************



// **************************************************************************
// System
// ------
// **************************************************************************

#define CNTLA0 0x00
#define CNTLB0 0x02
#define RDR0   0x08
#define ASEXT0 0x12
#define STAT0  0x04
#define TDR0   0x06


void initNABULib(void) {

  __asm
    push af;
    ld a, r;
    ld (__randomSeed), a;
        LD      A,01100100B    //; rcv enable, xmit enable, no parity
        OUT0    (CNTLA0),A    //; set cntla
        LD      A,00000000B    //; div 10, div 16, div 2 18432000/1/1/10/16/1 = 115200
        OUT0    (CNTLB0),A    // ; set cntlb
        LD      A,01100110B    //; no cts, no dcd, no break detect
        OUT0    (ASEXT0),A    // ; set ASCI0 EXTENSION CONTROL (Z8S180 only)
        LD      A,0
        OUT0    (STAT0),A //     ; ASCI Status Reg Ch 0
    pop af
  __endasm;

  srand(_randomSeed);

}

void nop(void) {
  __asm
    NOP
  __endasm;
}

void NABU_DisableInterrupts(void) {

  __asm
    di
  __endasm;
}

void NABU_EnableInterrupts(void) {

  __asm
    ei
  __endasm;
}

#if BIN_TYPE == BIN_CPM
  bool isCloudCPM(void) {
    return false;
  }
#endif

// **************************************************************************
// Keyboard
// --------
// **************************************************************************
uint8_t isKeyPressed(void)__naked {
    __asm
      //; hack to clear any overrun errors (See Errata about ASCI seizures)
      LD      A,0
      IN0     A,(CNTLA0)
      AND     ~0x08
      OUT0    (CNTLA0),A
      LD      A,0 
      IN0     A,(STAT0)
      AND     0b10000000
      LD      L,A
      RET
    __endasm;
}

uint8_t getChar(void) __naked {
    __asm
      LD      A,0
      IN0     A,(RDR0)
      LD      L,A
      RET
    __endasm;
  }

uint8_t getJoyStatus(void) {
    return ~IO_JOY0;
}

// **************************************************************************
// VDP 
// ---
// **************************************************************************


void vdp_setRegister(uint8_t registerIndex, uint8_t value) {

  IO_VDPLATCH = value;

  IO_VDPLATCH = 0x80 | registerIndex;
}

void vdp_setWriteAddress(uint16_t address) __z88dk_fastcall {

  IO_VDPLATCH = address & 0xff;

  IO_VDPLATCH = 0x40 | ((address >> 8) & 0x3f);
}

void vdp_setReadAddress(uint16_t address) __z88dk_fastcall {

  IO_VDPLATCH = address & 0xff;

  IO_VDPLATCH = (address >> 8) & 0x3f;
}

void vdp_waitVDPReadyInt(void) {
  // Just spin loop until we get a proper way to read vertical blank signal
    while ((IO_VDPLATCH & 0x80) == 0)
      ;
    vdpStatusRegVal = IO_VDPLATCH;
}

void vdp_enableVDPReadyInt(void) {
  vdp_setRegister(1, _vdpReg1Val | 0b00100000 );  
}
void vdp_disableVDPReadyInt(void) {
  vdp_setRegister(1, _vdpReg1Val);
}

// ONLY G1 Mode is supported
void vdp_init(uint8_t mode, uint8_t fgColor, uint8_t bgColor, bool big_sprites, bool magnify, bool autoScroll, bool splitThirds) {

  _vdpMode = mode;

  (void)splitThirds;
  (void)magnify;

  _vdpSpriteSizeSelected = big_sprites;

  _autoScroll = autoScroll;

  _vdpInterruptEnabled = true;

  vdp_cursor.x = 0;
  vdp_cursor.y = 0;
  
  _vdpPatternGeneratorTableAddr = 0x800;
  _vdpPatternNameTableAddr = 0x1400;
  _vdpColorTableAddr = 0x2000;
  _vdpCursorMaxX = 31;
  _vdpCursorMaxXFull = 32;
  _vdpTextBufferSize = 768;
  
  vdp_setRegister(0, 0);
  vdp_setRegister(1, 0xE0);
  vdp_setRegister(2, 0x05);
  vdp_setRegister(3, 0x80);
  vdp_setRegister(4, 0x01);
  vdp_setRegister(5, 0x20);
  vdp_setRegister(6, 0x00);
  vdp_setRegister(7, (fgColor << 4) | (bgColor & 0x0f));

  vdp_clearScreen();
}

void vdp_clearVRAM(void) {

  vdp_setWriteAddress(0x00);

  for (uint16_t i = 0; i < 0x3800; i++)
    vdp_put(0);
}

void vdp_initG1Mode(uint8_t bgColor, bool bigSprites, bool scaleSprites, bool autoScroll, bool splitThirds) {

  vdp_init(VDP_MODE_G1, 0, bgColor, bigSprites, scaleSprites, autoScroll, splitThirds);
}


void vdp_clearScreen(void) {

  vdp_setWriteAddress(_vdpPatternNameTableAddr);

  uint8_t *start = _vdp_textBuffer;
  uint8_t *end = start + (_vdpCursorMaxXFull * 24);

  uint8_t cr = 0x00;

  do {

    vdp_put(cr);

    *start = 0x20;

    start++;
  } while (start != end);
}

void vdp_fillScreen(uint8_t c) __z88dk_fastcall {

  vdp_setWriteAddress(_vdpPatternNameTableAddr);
  uint8_t *start = _vdp_textBuffer;
  uint8_t *end = start + (_vdpCursorMaxXFull * 24);

  do {
    vdp_put(c);
    *start = c;
    start++;
  } while (start != end);
}

void vdp_clearRows(uint8_t topRow, uint8_t bottomRow) {
  
  uint16_t name_offset = topRow * _vdpCursorMaxXFull;

  vdp_setWriteAddress(_vdpPatternNameTableAddr + name_offset);

  uint8_t *start = _vdp_textBuffer + (topRow * _vdpCursorMaxXFull);
  uint8_t *end   = _vdp_textBuffer + (bottomRow * _vdpCursorMaxXFull);

  do {
    
    vdp_put(0x20);
    *start = 0x20;

    start++;
  } while (start != end);
}

void vdp_loadASCIIFont(uint8_t *font) __z88dk_fastcall {

  vdp_setWriteAddress(_vdpPatternGeneratorTableAddr + 0x100);

  uint8_t *start = font;
  uint8_t *end = start + 768;

  do {

    vdp_put(*start);
    start++;
  } while (start != end);
}

void vdp_putPattern(uint8_t x, uint8_t y, uint8_t patternId) {

  uint16_t name_offset = y * _vdpCursorMaxXFull + x;

  vdp_setWriteAddress(_vdpPatternNameTableAddr + name_offset);
  _vdp_textBuffer[name_offset] = patternId;
  
  // IO_VDPDATA = patternId;
  vdp_put(patternId);
}

void vdp_loadPatternTable(uint8_t *patternTable, uint16_t len) {

  uint8_t *start = patternTable;
  uint8_t *end = patternTable + len;

  vdp_setWriteAddress(_vdpPatternGeneratorTableAddr);
  do {

    vdp_put(*start);

    start++;
  } while (start != end);
}

void vdp_loadColorTable(uint8_t *colorTable, uint16_t len) {

  uint8_t *start = colorTable;
  uint8_t *end = colorTable + len;

  vdp_setWriteAddress(_vdpColorTableAddr);
  do {

    vdp_put(*start);
    start++;
  } while (start != end);
}

void vdp_colorizePattern(uint8_t patternId, uint8_t fg, uint8_t bg) {

  uint8_t c = (fg << 4) + bg;

  vdp_setWriteAddress(_vdpColorTableAddr + patternId);
  vdp_put(c);
}

void vdp_print(uint8_t *text) __z88dk_fastcall {

  uint8_t *start = text;

  while (*start != 0x00) {

    vdp_write(*start);

    start++;
  }
}

void vdp_printColorized(uint8_t *text, uint8_t fgColor, uint8_t bgColor) {

  uint8_t *start = text;

  while (*start != 0x00) {

    vdp_colorizePattern(*start, fgColor, bgColor);

    vdp_write(*start);

    start++;
  }
}

void vdp_printPart(uint16_t offset, uint16_t textLength, uint8_t *text) {

  uint8_t *start = text + offset;
  uint8_t *end   = start + textLength;

  while (start != end) {

    vdp_write(*start);

    start++;
  }
}

void vdp_newLine(void) {

  if (vdp_cursor.y == 23) {

    if (_autoScroll)
      vdp_scrollTextUp(0, 23);

    vdp_cursor.x = 0;
  } else {

    vdp_setCursor2(0, ++vdp_cursor.y);
  }
}

void vdp_setBackDropColor(uint8_t color) __z88dk_fastcall {

  vdp_setRegister(7, color);
}

void vdp_setCursor2(uint8_t col, uint8_t row) {

  if (col > _vdpCursorMaxX) {

    col = 0;
    row++;
  }

  if (row > _vdpCursorMaxY)
    row = 0;

  vdp_cursor.x = col;
  vdp_cursor.y = row;
}

void vdp_setCursor(uint8_t direction) __z88dk_fastcall {

  switch (direction) {
    case VDP_CURSOR_UP:
      vdp_setCursor2(vdp_cursor.x, vdp_cursor.y - 1);
      break;
    case VDP_CURSOR_DOWN:
      vdp_setCursor2(vdp_cursor.x, vdp_cursor.y + 1);
      break;
    case VDP_CURSOR_LEFT:
      vdp_setCursor2(vdp_cursor.x - 1, vdp_cursor.y);
      break;
    case VDP_CURSOR_RIGHT:
      vdp_setCursor2(vdp_cursor.x + 1, vdp_cursor.y);
      break;
  }
}

void vdp_setTextColor(uint8_t fg, uint8_t bg) {

  vdp_setRegister(7, (fg << 4) + bg);
}

void vdp_write(uint8_t chr) __z88dk_fastcall {

  uint16_t name_offset = vdp_cursor.y * _vdpCursorMaxXFull + vdp_cursor.x;

  vdp_setWriteAddress(_vdpPatternNameTableAddr + name_offset);

  vdp_put(chr);

  _vdp_textBuffer[name_offset] = chr;

  if (_autoScroll && vdp_cursor.x == _vdpCursorMaxX && vdp_cursor.y == 23) {

    vdp_scrollTextUp(0, 23);

    vdp_cursor.x = 0;
  }

  vdp_setCursor2(vdp_cursor.x + 1, vdp_cursor.y);
}

void vdp_writeCharAtLocation(uint8_t x, uint8_t y, uint8_t c) {

  uint16_t name_offset = y * _vdpCursorMaxXFull + x; 

  _vdp_textBuffer[name_offset] = c;
    
  vdp_setWriteAddress(_vdpPatternNameTableAddr + name_offset);

  vdp_put(c);
}

uint8_t vdp_getCharAtLocationVRAM(uint8_t x, uint8_t y) {

  uint16_t name_offset = y * _vdpCursorMaxXFull + x; 

  vdp_setReadAddress(_vdpPatternNameTableAddr + name_offset);

  return IO_VDPDATA;
}

uint8_t vdp_getCharAtLocationBuf(uint8_t x, uint8_t y) {

  return _vdp_textBuffer[y * _vdpCursorMaxXFull + x];
}

void vdp_setCharAtLocationBuf(uint8_t x, uint8_t y, uint8_t c) {

  _vdp_textBuffer[y * _vdpCursorMaxXFull + x] = c;
}

void vdp_refreshViewPort(void) {

  // vdp_setWriteAddress(_vdpPatternNameTableAddr);

  __asm
    ld hl, __vdp_textBuffer;
    ld de, (__vdpPatternNameTableAddr);
    ld bc, (__vdpTextBufferSize);
    ld  a,e;
    out (0x81),a;
    ld  a,d;
    or  0x40;
    out (0x81),a;

    ld  d,b
    ld  e,c;

    ld  c,0x80;
    ld  b,e;
    inc e;
    dec e;
    jr  z,vdp_write_loop;
    inc d;

  vdp_write_loop:
          outi;
          jp    nz,vdp_write_loop;
          dec   d;
          jp    nz,vdp_write_loop;
      in  a,(0x81);
  __endasm;
}

void vdp_scrollTextUp(uint8_t topRow, uint8_t bottomRow) {

  vdp_setWriteAddress(_vdpPatternNameTableAddr + (topRow * _vdpCursorMaxXFull));

  uint8_t *to   = _vdp_textBuffer + (topRow * _vdpCursorMaxXFull);
  uint8_t *from = to + _vdpCursorMaxXFull;
  uint8_t *end  = _vdp_textBuffer + ((bottomRow + 1) * _vdpCursorMaxXFull);

  do {

    *to = *from;

    vdp_put(*to);

    to++;
    from++;
  } while (from != end);
  
  do {

    *to = 0x20;
    vdp_put(0x20);
    

    to++;
  } while (to != end);
}

void vdp_scrollTextDown(uint8_t topRow, uint8_t bottomRow) {

  uint8_t *fromPtr = _vdp_textBuffer + (bottomRow * _vdpCursorMaxXFull) - 1;
  uint8_t *toPtr   = fromPtr + _vdpCursorMaxXFull;
  uint8_t *endPtr  = (_vdp_textBuffer - 1) + (topRow * _vdpCursorMaxXFull);

  do {

    *toPtr = *fromPtr;

    toPtr--;
    fromPtr--;
  } while (fromPtr != endPtr);
      
  do {

    *toPtr = 0x20;

    toPtr--;
  } while (toPtr != endPtr);

  vdp_setWriteAddress(_vdpPatternNameTableAddr + (topRow * _vdpCursorMaxXFull));
  uint8_t *v = _vdp_textBuffer + (topRow * _vdpCursorMaxXFull);
  uint8_t *e = _vdp_textBuffer + ((bottomRow + 1) * _vdpCursorMaxXFull);

  do {

    vdp_put(*v);

    v++;
  } while (v != e);
}

//https://github.com/jblang/TMS9918A/blob/111ce0ba7ff446ac3b2fbaa81d41a741074e431d/examples/tms.asm#L213
//Limits all ram out operations to at least 8uS.  We could be more efficient on the VDP Blank,
//but if the code overshoots the vsync timings, we would end up in trouble.  This approach while a bit
//slower, avoids that risk altogether.
void vdp_put(uint8_t c) __z88dk_fastcall {
  IO_VDPDATA = c;
  __asm
    // push    bc                      ; 11  | 11
    ld      b, 2                    ; 2 iteration
  TmsRamOutDelay:
    djnz    TmsRamOutDelay          ; 8   | 7  plus (13 | 9) * (iterations-1)
    // pop     bc                      ; 10  | 9
  __endasm;
}
