/**
 *   c2p.cpp - Chunky to bitplane (interleaved) conversion
 *
 *  Use libcmini for smaller binaries it's also possible to use cstdio or iostream (bloatwarning)
 *
 *  C++ standard: C++17
 *
 *  C standard: C99
 *
 *  Version: 0.5
 *
 *  Coded by: Johan Tibbelin
 *
 *  Last changed: 20200422 at 11:39:45
 */

// Macros...
// Defaults
#undef __WITH__IOSTREAM__
#define __WITH_GEMDOS__ 1
#define __WITH_LIBCMINI__ 1
#define _DEBUG_ 0
#undef _DEBUG_

// Use gemdos Cconws() to print
#if defined(__WITH_GEMDOS__)
#include <osbind.h>
#include <gem.h>
#endif

// Use iostream (*not recomended*)
#if defined(__WITH_IOSTREAM__)
#include <iostream>
#endif

// Use libcmini for print
// Can't be used with iostream.
#if defined(__WITH_LIBCMINI__)
#include <stdio.h>
#else
#include <cstdio>
#endif

#include <cstdint>

// Use libpng (optional)
#if defined(__WITH_LIBPNG__)
#include <png.h>
#endif

// Configure Debug
#if defined(_DEBUG_)
#define _DEBUG_ 1
#include <bitset>
#else
#define _DEBUG_ 0
#endif

// Global declarations (ugh)

struct lookup {
  uint8_t value;
  uint8_t bplane[4];
};
lookup c2p[256];

#if defined(__WITH_IOSTREAM__)
struct HexCharStruct
{
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
  return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
  return HexCharStruct(_c);
}
#endif // __WITH_IOSTREAM__

void print(const char * s)
{
#if defined(__WITH_GEMDOS__)
  Cconws(s);
#elif defined(__WITH_IOSTREAM__)
  std::cout << s;
#else
  printf(s);
#endif
}
// convert function 		   
void c2p_convert(void * sp,int l) {
  uint8_t *pSource,*pTarget;
  uint16_t bplane[4];
  uint8_t *fb,*tb;
  uint16_t bitplane[16*4];
  pSource = (uint8_t *)sp;
  pTarget = (uint8_t *)bitplane;
  int current_word=0;
  for (int i=0; i<l; i+=8)
  {
    // convert 16 pixels (one 16 bit word) to bitplanes
    for (int j=0;j<8;j++) {
      bitplane[current_word]   = (bitplane[current_word]   << 2) | c2p[*pSource].bplane[0];  
      bitplane[current_word+1] = (bitplane[current_word+1] << 2) | c2p[*pSource].bplane[1];  
      bitplane[current_word+2] = (bitplane[current_word+2] << 2) | c2p[*pSource].bplane[2];  
      bitplane[current_word+3] = (bitplane[current_word+3] << 2) | c2p[*pSource].bplane[3];
      pSource++;
    }
    current_word+=4;
  }


}
void genLookup();           


int main() 
{

  genLookup();
  uint32_t sprite[16] = {0xfedcaa64,0xffdd2345,0xed563412,0x674523e5,
			 0xfedcaa64,0xffdd2345,0xed563412,0x674523e5,
			 0xfedcaa64,0xffdd2345,0xed563412,0x674523e5,
			 0xfedcaa64,0xffdd2345,0xed563412,0x674523e5 };
  c2p_convert(sprite,32);
  return 0;
}
// genLookup:
// Generates lookup table used by c2p_convert function
void genLookup()
{
  if (_DEBUG_) { 
    print("Generating lookup table...");
  }
for (int i=0; i<256;i++)
  {
    c2p[i].value = i;
    c2p[i].bplane[0] = 0x01 & i;
    c2p[i].bplane[1] = 0x02 & i;
    c2p[i].bplane[2] = 0x04 & i;
    c2p[i].bplane[3] = 0x08 & i;
    c2p[i].bplane[0] = (c2p[i].bplane[0] << 1 ) | (0x10 & i) >> 1;
    c2p[i].bplane[1] = (c2p[i].bplane[1] << 1 ) | (0x20 & i) >> 1;
    c2p[i].bplane[2] = (c2p[i].bplane[2] << 1 ) | (0x30 & i) >> 1;
    c2p[i].bplane[3] = (c2p[i].bplane[3] << 1 ) | (0x40 & i) >> 1;
  
  }
 if (_DEBUG_) {
   print("done.\n");
 }
}

void * loadGfx(const char * f)
{
#if defined(__WITH_LIBPNG__)
  // PNG stuff goes here...
#else
  print("configure with -with=libpng to be able to load files.");
  return (void *)-1;
#endif
}
