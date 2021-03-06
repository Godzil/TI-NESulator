/*
 *  MMC4 Mapper - The peTI-NESulator Project
 *  mmc4.h
 *
 *  Created by Manoël Trapier.
 *  Copyright (c) 2002-2019 986-Studio.
 *
 */

#include "mmc4.h"

uint8_t mmc4_RegA;
uint8_t mmc4_RegB;
uint8_t mmc4_RegC;
uint8_t mmc4_RegD;
uint8_t mmc4_RegE;
uint8_t mmc4_RegF;

#ifdef DEBUG
#define LOG(s) printf s
#else
#define LOG(s) { }
#endif

/* MAPPER WARNING: This mapper need to attach to the PPU memory... Need more work on this parts.. */

void mmc4_MapperWriteRegA(register uint8_t Addr, register uint8_t Value)
{
    LOG(("%s(%02X, %02X)\n", __func__, Addr, Value));
    mmc4_RegA = Value;

    set_prom_bank_16k(0x8000, Value & 0x0F);

}

void mmc4_MapperWriteRegB(register uint8_t Addr, register uint8_t Value)
{
    LOG(("%s(%02X, %02X)\n", __func__, Addr, Value));
    mmc4_RegB = Value;

    set_vrom_bank_4k(0x0000, Value & 0x1F);
}

void mmc4_MapperWriteRegC(register uint8_t Addr, register uint8_t Value)
{
    LOG(("%s(%02X, %02X)\n", __func__, Addr, Value));
    mmc4_RegC = Value;
    set_vrom_bank_4k(0x0000, Value & 0x1F);
}

void mmc4_MapperWriteRegD(register uint8_t Addr, register uint8_t Value)
{
    LOG(("%s(%02X, %02X)\n", __func__, Addr, Value));
    mmc4_RegD = Value;
    set_vrom_bank_4k(0x1000, Value & 0x1F);
}

void mmc4_MapperWriteRegE(register uint8_t Addr, register uint8_t Value)
{
    LOG(("%s(%02X, %02X)\n", __func__, Addr, Value));
    mmc4_RegE = Value;
    set_vrom_bank_4k(0x1000, Value & 0x1F);
}

void mmc4_MapperWriteRegF(register uint8_t Addr, register uint8_t Value)
{
    LOG(("%s(%02X, %02X)\n", __func__, Addr, Value));
    mmc4_RegF = Value;
    if (Value & 0x01)
    {
        ppu_setMirroring(PPU_MIRROR_HORIZTAL);
    }
    else
    {
        ppu_setMirroring(PPU_MIRROR_VERTICAL);
    }
}


void mmc4_MapperDump(FILE *fp)
{

}

int mmc4_InitMapper(NesCart *cart)
{
    int i;

    set_prom_bank_16k(0x8000, 0);
    set_prom_bank_16k(0xC000, GETLAST16KBANK(cart));

    if (cart->VROMSize > 0)
    {
        set_vrom_bank_8k(0x0000, 0);
    }

    /* Mapper should register itself for write hook */
    for (i = 0xA0 ; i < 0xB0 ; i++)
    {
        set_page_wr_hook(i, mmc4_MapperWriteRegA);
        set_page_writeable(i, true);
    }
    for (i = 0xB0 ; i < 0xC0 ; i++)
    {
        set_page_wr_hook(i, mmc4_MapperWriteRegB);
        set_page_writeable(i, true);
    }
    for (i = 0xC0 ; i < 0xD0 ; i++)
    {
        set_page_wr_hook(i, mmc4_MapperWriteRegC);
        set_page_writeable(i, true);
    }
    for (i = 0xD0 ; i < 0xE0 ; i++)
    {
        set_page_wr_hook(i, mmc4_MapperWriteRegD);
        set_page_writeable(i, true);
    }
    for (i = 0xE0 ; i < 0xF0 ; i++)
    {
        set_page_wr_hook(i, mmc4_MapperWriteRegE);
        set_page_writeable(i, true);
    }
    for (i = 0xF0 ; i < 0x100 ; i++)
    {
        set_page_wr_hook(i, mmc4_MapperWriteRegF);
        set_page_writeable(i, true);
    }

    for (i = 0x60 ; i < 0x80 ; i++)
    {
        set_page_writeable(i, true);
        set_page_readable(i, true);
    }

    //ppu_setScreenMode(PPU_SCMODE_NORMAL);
    //ppu_setMirroring(PPU_MIRROR_HORIZTAL);

    return 0;

}

