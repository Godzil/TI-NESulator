/*
 *  MMC1 Mapper - The peTI-NESulator Project
 *  mmc1.h
 *
 *  Created by Manoël Trapier.
 *  Copyright (c) 2002-2019 986-Studio.
 *
 */

#define __TINES_MAPPERS__

#include <mappers/manager.h>

int mmc1_InitMapper(NesCart *cart);
int mmc1_MapperIRQ(int cycledone);
void mmc1_MapperDump(FILE *fp);