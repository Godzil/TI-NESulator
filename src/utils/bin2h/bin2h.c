/*
 *  bin to header - Part of The peTI-NESulator Project
 *  bin2h.c: Convert a binary file to a table of byte in a C header file.
 *
 *  Created by Manoel Trapier.
 *  Copyright 2003-2008 986 Corp. All rights reserved.
 *
 *  $LastChangedDate$
 *  $Author$
 *  $HeadURL$
 *  $Revision$
 *
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int i;
	char *infile;
	FILE *fpin = stdin;
	FILE *fpout = stdout;
	short c;
	infile = "stdin";
	if (argc > 1)
	{
	
		for(i = 1; argv[i] && argv[i][0] == '-'; i++)
		{
			if (i < argc)
			{
				switch(argv[i][1])
				{
				case 'i':
					fpin = fopen(argv[i+1], "rb");
					infile = argv[i+1];
					if (fpin == NULL)
					{
						fprintf (stderr, "Error: cannot open in file '%s'\n", argv[i+1]);
						exit(-1);
					}
					i++;
					break;
					
				case 'o':
				
					fpout = fopen(argv[i+1], "wb");
					if (fpout == NULL)
					{
						fprintf (stderr, "Error: cannot open out file '%s'\n", argv[i+1]);
						exit(-1);
					}
					i++;
					break;
					
				default:
					fprintf (stderr, "Error: unknown argument: %s\n", argv[i]);
					exit(-1);
				}
			}
		}
	}

	fprintf(fpout, "/* Generated data file from file '%s' */\n\n\n", infile);
	
	fprintf(fpout, "unsigned char data[] = {\n");
	i = 0;
	while((c = fgetc(fpin)) >= 0)
	{
		if (i == 0)
			fprintf(fpout, "\t\t0x%02X", (unsigned char)c);
		else
			fprintf(fpout, ", 0x%02X", (unsigned char)c);
			
		i++;
		if (i > 10)
		{
			fprintf(fpout,", \\\n");
			i = 0;
		}
	
	
	}
	fprintf(fpout, "\n\t\t};\n");

	return 0;
}
