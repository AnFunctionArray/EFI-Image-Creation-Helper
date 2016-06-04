#include "main.h"
#include <stdio.h>

int main()
{
	return WriteFile(&"./test.o", 1, 0, &(SectorDesc[1]){ { 0x400, &(uint8_t[0x400]){ 'S', 'E', 'B', 'G', 'I', 'N', }, "12345678", 0x400, 0, IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ} }, NULL, 0x400);
}
