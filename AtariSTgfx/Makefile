# Makefile for olcPixelGameEngineST

LIBCMINI=/opt/libcmini
CXX = m68k-atari-mint-g++-8
CXXFLAGS =  -Wall -O2 -std=c++17 -nostdlib -fomit-frame-pointer -fno-exceptions -D__WITH_GEMDOS__ \
            -D__WITH_LIBCMINI__ -D_DEBUG_ -D__ATARI_ST__ -I$(LIBCMINI)/include
src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = -L.. -L$(LIBCMINI)/lib -lstdc++ -lcmini -lgcc -lgem -lpng -lz

c2p_test.prg: $(obj)
        $(CXX) $(CXXFLAGS) -o $@ $(LIBCMINI)/startup.o $^ $(LDFLAGS)

.PHONY: clean
clean:
        rm -f $(obj) c2p_test.prg
