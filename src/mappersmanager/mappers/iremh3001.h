/*
 *  IREMH3001 Mapper - The peTI-NESulator Project
 *  iremh3001.h
 *
 *  Created by Manoël TRAPIER.
 *  Copyright (c) 2003-2018 986-Studio. All rights reserved.
 *
 */

#define __TINES_MAPPERS__

#include <mappers/manager.h>

int iremh3001_InitMapper(NesCart *cart);
void iremh3001_MapperDump(FILE *fp);
int iremh3001_MapperIRQ(int cycledone);