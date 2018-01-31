/*
 *  UNROM Mapper - The peTI-NESulator Project
 *  unrom.h
 *
 *  Created by Manoel TRAPIER.
 *  Copyright (c) 2003-2018 986-Studio. All rights reserved.
 *
 *  $LastChangedDate$
 *  $Author$
 *  $HeadURL$
 *  $Revision$
 *
 */

#define __TINES_MAPPERS__
#include <mappers/manager.h>

int unrom_InitMapper(NesCart * cart); 
void unrom_MapperDump(FILE *fp);