/*
 *  PPU Memory manager - The peTI-NESulator Project
 *  ppu.memory.c - Inspired from the memory manager of the Quick6502 Project.
 *
 *  Created by Manoël Trapier on 12/04/07.
 *  Copyright (c) 2002-2019 986-Studio.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <os_dependent.h>

#define __TINES_PPU_INTERNAL__

#include <ppu/ppu.h>
#include <ppu/ppu.memory.h>

#include <types.h>

/* Simple definition only for readability */
#define KByte * (1024)

/* Internal representation of the PPU memory */ 
uint8_t *ppu_memoryPages[0x40];

uint8_t ppu_memoryGhostLink[0x40];
 
/* Internal PPU Sprite Ram */
uint8_t ppu_SpriteRam[0x100];
 
/* 
 * Memory management functions 
 *
 * Yes that true, PPU memory & CPU memory work in a nearly same fashion despite
 * the fact that we actually didn't have any Read/Write hook and ReadWrite
 * protection. We even didn't need "attributes" for the page. One of the only
 * need is the "powerful" ghost system
 */

int ppu_initMemory()
{
    int page; 
    for(page = 0 ; page < 0x40 ; page++)
    {
        ppu_setPagePtr(page,NULL);
        ppu_memoryGhostLink[page] = 0xFF; /* ( >= 0x40 is not possible) */
    }
    return 0;
}

void ppu_updateGhost(uint8_t page)
{    
    uint8_t cur_ghost;

    cur_ghost = ppu_memoryGhostLink[page];
    if (cur_ghost < 0x40)
        ppu_memoryPages[cur_ghost] = ppu_memoryPages[page];
}

void ppu_setPagePtr  (uint8_t page, uint8_t *ptr)
{
    ppu_memoryPages[page] = ptr;
    ppu_updateGhost(page);
}

void ppu_setPagePtr1k(uint8_t page, uint8_t *ptr)
{   /* 1k = 4 * 256 */
    ppu_memoryPages[page + 0] = ptr;
    ppu_memoryPages[page + 1] = ptr +  0x100;
    ppu_memoryPages[page + 2] = ptr + (0x100 * 2);
    ppu_memoryPages[page + 3] = ptr + (0x100 * 3);
    
    ppu_updateGhost(page + 0);
    ppu_updateGhost(page + 1);
    ppu_updateGhost(page + 2);
    ppu_updateGhost(page + 3);
}

void ppu_setPagePtr2k(uint8_t page, uint8_t *ptr)
{
    ppu_memoryPages[page + 0] = ptr;
    ppu_memoryPages[page + 1] = ptr +  0x100;
    ppu_memoryPages[page + 2] = ptr + (0x100 * 2);
    ppu_memoryPages[page + 3] = ptr + (0x100 * 3);
    ppu_memoryPages[page + 4] = ptr + (0x100 * 4);
    ppu_memoryPages[page + 5] = ptr + (0x100 * 5);
    ppu_memoryPages[page + 6] = ptr + (0x100 * 6);
    ppu_memoryPages[page + 7] = ptr + (0x100 * 7);
    
    ppu_updateGhost(page + 0);
    ppu_updateGhost(page + 1);
    ppu_updateGhost(page + 2);
    ppu_updateGhost(page + 3);
    ppu_updateGhost(page + 4);
    ppu_updateGhost(page + 5);
    ppu_updateGhost(page + 6);
    ppu_updateGhost(page + 7);
}

void ppu_setPagePtr4k(uint8_t page, uint8_t *ptr)
{
    ppu_setPagePtr2k(page, ptr);
    ppu_setPagePtr2k(page+((4 KByte / 256) / 2), ptr + 2 KByte);
}

void ppu_setPagePtr8k(uint8_t page, uint8_t *ptr)
{
    ppu_setPagePtr4k(page, ptr);
    ppu_setPagePtr4k(page+((8 KByte / 256) / 2), ptr + 4 KByte);
}

void ppu_setPageGhost(uint8_t page, uint8_t value, uint8_t ghost)
{
    if (value == true)
    {  
        ppu_memoryPages[page] = ppu_memoryPages[ghost];        
        ppu_memoryGhostLink[ghost] = page;
        console_printf(Console_Default, "set ghost of 0x%02X to 0x%02X (ptr: %p)\n", ghost, page, &(ppu_memoryGhostLink[ghost]));
    }
}

void ppu_memoryDumpState(FILE *fp)
{
    int i;
    for (i = 0x00; i < 0x40; i++)
    {
        fprintf(fp,
                "Page 0x%02X : ptr:%p ghost:0x%02X\n",
                i,
                ppu_memoryPages[i],
                ppu_memoryGhostLink[i]
                );
    }
}

uint8_t ppu_readMemory(uint8_t page, uint8_t addr)
{
    uint8_t *ptr;
    if (page == 0x3F)
        return ( ppu_memoryPages[0x3F][addr&0x1F] & 0x3F );
        
    ptr = ppu_memoryPages[page & 0x3F];
    return ptr[addr];
}

void ppu_writeMemory(uint8_t page, uint8_t addr, uint8_t value)
{
    if (page == 0x3F)
    {
        /* Here we will cheat with the palette mirroring, since we didn't write
           as often as we read the palette, we will mirror here */
        //console_printf(Console_Default, "%s palette: color %02X new value : %02d (0x%02X%02X)\n", ((addr&0x10)< 0x10) ? "Bgnd" : "Sprt", addr&0x1F, value & 0x3F, page, addr);
        if ((addr & 0xEF) == 0x00)
        {
            ppu_memoryPages[0x3F][0x00] = value;
            ppu_memoryPages[0x3F][0x10] = value;
        }
        else
            ppu_memoryPages[0x3F][addr&0x1F] = value;
    }
    else
    {
        uint8_t *ptr;

        ptr = ppu_memoryPages[page & 0x3F];
        ptr[addr] = value;
    }
}
