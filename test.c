#include <Linker/main.h>
#include <ImprovedC/main.h>
#include <stdio.h>

//extern void func();

int main()
{
	//func();

	CompileSingleFile(&"?+a"

	return WriteFile(&"./test.o", 1, 0, &(SectorDesc[1]){ { 0x400, &(uint8_t[0x400]){ 'S', 'E', 'B', 'G', 'I', 'N', }, "12345678", 0x400, 0, IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ} }, NULL, 0x400);
}

/*extern void func()
{
	volatile int var=2;
	while(true)
		if(var++==90) break;

	printf("%d", var);
}*/

/*FILE *pFile;
    	
    	if(!(pFile = fopen("file.test", "wb"))) return false;
    
    	const char BinToWrite[] = "text";
    
    	fseek(pFile, sizeof(BinToWrite), SEEK_SET),
    
    	fwrite(BinToWrite, sizeof(BinToWrite), 1, pFile),

	fseek(pFile, sizeof(BinToWrite), SEEK_CUR),
    
    	fwrite(BinToWrite, sizeof(BinToWrite), 1, pFile),
    
    	fseek(pFile, 0, SEEK_SET),
    
    	fwrite(BinToWrite, sizeof(BinToWrite), 1, pFile),
    
    	fclose(pFile);*/
