#include "main.h"

#include <stdio.h>

//Helper Data

static COFFHead dCoffHeadTemplate = {.Machine = EFI_IMAGE_MACHINE_x64, .SizeOfOptionalHeader = 	sizeof(COFFOptionalHead), .Characteristics = IMAGE_FILE_EXECUTABLE_IMAGE };

static COFFOptionalHead dCoffOptionalHeadTempl = {.Magic = COFFMagic, .dWindowSpecific.FileAlignment = 1,

	.dWindowSpecific.SectionAlignment = 1, .dWindowSpecific.Subsystem = EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION};

static size_t const szMSDOStillPEPadding = 0x10;

static const size_t szBytesTillDataDirs = pCOFFHeadOffset + sizeof(uint32_t) + szMSDOStillPEPadding + sizeof(COFFsign) + sizeof(COFFHead) + sizeof(COFFOptionalHead);

static ImageSectionHeader dSectHeadTempl;


static inline void allign(size_t *pszWhat, const size_t szAlligment) //unused IRC
{
	const size_t tmp = *pszWhat % szAlligment;
	
	if(tmp) *pszWhat += szAlligment - tmp;
}

extern bool WriteFile(const char (*pFileName)[], /*null-terminated*/
				size_t szAmountSectors, size_t szAmountDataDirs,
				SectorDesc (*pSectorsToBeAdded)[szAmountSectors],
				ImageDataDir (*pDataDirs)[szAmountDataDirs],
				size_t szImage)
{
	FILE *pFile;
	
	if(!(pFile = fopen(*pFileName, "wb"))) return false;

	fwrite(MZDosSign, sizeof(MZDosSign), 1, pFile),
	
	fseek(pFile, pCOFFHeadOffset, SEEK_SET),
	
	//uint32_t tmp_0 = pCOFFHeadOffset + sizeof(uint32_t);
	
	fwrite((uint32_t[1]){pCOFFHeadOffset + sizeof(uint32_t) + szMSDOStillPEPadding}, sizeof(uint32_t), 1, pFile),

	fseek(pFile, szMSDOStillPEPadding, SEEK_CUR),
	
	fwrite(COFFsign, sizeof(COFFsign), 1, pFile),

	dCoffHeadTemplate.NumberOfSections = szAmountSectors,

	fwrite(&dCoffHeadTemplate, sizeof(COFFHead), 1, pFile),
	
	dCoffOptionalHeadTempl.dWindowSpecific.NumberOfRvaAndSizes = szAmountDataDirs,

	dCoffOptionalHeadTempl.dWindowSpecific.SizeOfHeaders = szBytesTillDataDirs + sizeof(*pDataDirs) + sizeof(ImageSectionHeader) * szAmountSectors,

	dCoffOptionalHeadTempl.dWindowSpecific.SizeOfImage = szImage,
	
	fwrite(&dCoffOptionalHeadTempl, sizeof(COFFOptionalHead), 1, pFile),

	fwrite(*pDataDirs, sizeof(*pDataDirs), 1, pFile);
	
	//Write Section Headers

	//const size_t szSectionHeads = sizeof(ImageSectionHeader) * szAmountSectors;

	//fseek(pFile, sizeof(COFFOptionalHead), SEEK_CUR);

	//size_t szInitSects = 0;

	ImageSectionHeader aImageSectHeads[szAmountSectors];

	fseek(pFile, sizeof(aImageSectHeads), SEEK_CUR);

	dSectHeadTempl.PointerToRawData = szBytesTillDataDirs + sizeof(*pDataDirs) + sizeof(aImageSectHeads);

	for(size_t i=0; i < szAmountSectors; ++i)
	{
		typedef struct { uint8_t _d[8]; } tmpType_0;

		*(tmpType_0*)&dSectHeadTempl.Name = *(tmpType_0*)&(*pSectorsToBeAdded)[i].Name,
		dSectHeadTempl.VirtualSize = (*pSectorsToBeAdded)[i].VirtualSize,
		dSectHeadTempl.VirtualAddress = (*pSectorsToBeAdded)[i].VirtualAddress,
		dSectHeadTempl.Characteristics = (*pSectorsToBeAdded)[i].Characteristics,
		dSectHeadTempl.SizeOfRawData = (*pSectorsToBeAdded)[i].szSector,
		

		aImageSectHeads[i] = dSectHeadTempl;
		
		//fwrite(&dSectHeadTempl, sizeof(ImageSectionHeader), 1, pFile)
		

		if(!(dSectHeadTempl.Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA))
		//{
			fwrite((*pSectorsToBeAdded)[i].pSectorData, dSectHeadTempl.SizeOfRawData, 1, pFile),

			dSectHeadTempl.PointerToRawData += dSectHeadTempl.SizeOfRawData;
		//}
	}

	return !(/*fflush(pFile),*/ fseek(pFile, szBytesTillDataDirs + sizeof(*pDataDirs), SEEK_SET),
		
	fwrite(aImageSectHeads, sizeof(aImageSectHeads), 1, pFile),

	fclose(pFile));
}

