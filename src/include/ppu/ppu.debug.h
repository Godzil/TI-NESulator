/*
 *  PPU debug utilities - The peTI-NESulator Project
 *  ppu.debug.h
 *
 *  Created by Manoël Trapier on 12/04/07.
 *  Copyright 2003-2008 986 Corp. All rights reserved.
 *
 */

#ifdef __TINES_PPU_INTERNAL__

void ppu_dumpPalette(int x, int y);
void ppu_dumpPattern(int xd, int yd);
void ppu_dumpNameTable(int xd, int yd);
void ppu_dumpAttributeTable(int xd, int yd);

#else
#error Must only be included inside the PPU code
#endif
