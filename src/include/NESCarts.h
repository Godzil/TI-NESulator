/*
 *  Cart manager - The peTI-NESulator Project
 *  NESCart.h
 *
 *  Created by Manoël TRAPIER.
 *  Copyright (c) 2003-2018 986-Studio. All rights reserved.
 */

#ifndef NESCARTS_H
#define NESCARTS_H

#include <stdint.h>
#include <types.h>

#define iNES_MIRROR  0x01
#define iNES_BATTERY 0x02
#define iNES_TRAINER 0x04
#define iNES_4SCREEN 0x08

typedef struct NesCart_
{
    uint32_t PROMSize,  /* Size of PROM */
            VROMSize;  /* Size of VROM */
    char MapperID;  /* Mapper Type */
    uint8_t Flags;
    char *FileName;
    uint8_t *File;      /* Pointer on the file in memory */
    uint8_t *PROMBanks; /* Pointer on the first PROM */
    uint8_t *VROMBanks; /* Pointer on the first VROM */
} NesCart;

void DumpCartProperties(FILE *out, NesCart *cart);
int LoadCart(const char *filename, NesCart *cart);

#endif
