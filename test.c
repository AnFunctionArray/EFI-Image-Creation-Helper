#include "main.h"
#include <stdio.h>

int (main)()
{
	//Creates EFI image with name test.o
	//1 sector at VA 0 with size 0x400 beginning with "SEGBGIN"
	//0 image directories
	//virtual image size of 0x400 total
	
	return WriteFile(&"./test.o", //EFI image name
	1, //n sectors
	0, //n directories
	
	&(SectorDesc[1]){ { 0x400, &(uint8_t[0x400]){ 'S', 'E', 'B', 'G', 'I', 'N', }, 
	"12345678", 0x400, 0, IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ} }, //simple sector descriptors (single in the case)
	
	NULL, //pointer to image data directories - non in the case
	
	0x400 //virtual image size
	);
}
