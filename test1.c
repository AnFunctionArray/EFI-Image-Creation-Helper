#include "main.h"
#include "./Helper/main.h"
#include <stdio.h>

int (main)(int n, char **p)
{
	if(n <= 1) return 1;

    	FILE *pFile = fopen(p[1], "rb");

    	fseek(pFile, 0, SEEK_END);

	uint8_t ImageSection[ftell(pFile)];

	rewind(pFile);

	fread(ImageSection, sizeof(ImageSection), 1, pFile), fclose(pFile);
	
	return WriteFile(&"./test.o", //EFI image name
	1, //n sectors
	0, //n directories
	
	&(SectorDesc[1]){ { sizeof(ImageSection), &ImageSection, //pass the file content as single section
	
	*(__typeof__(M_abstr(SectorDesc).sName) *)p[1], //use first 8 characters of the file name/path as section name
	
	sizeof(ImageSection), 0, IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ} }, //simple sector descriptors (single in the case)
	
	NULL, //pointer to image data directories - non in the case
	
	sizeof(ImageSection) //virtual image size
	);
}
