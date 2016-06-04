#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h> 

static const uintptr_t pCOFFHeadOffset = 0x3C;

static const char MZDosSign[2] = "MZ", COFFsign[4] = "PE\0\0";

// PE32+ Subsystem type for EFI images
#define EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION 10
#define EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER 11
#define EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER 12
// PE32+ Machine type for EFI images
#define EFI_IMAGE_MACHINE_IA32 0x014c
#define EFI_IMAGE_MACHINE_IA64 0x0200
#define EFI_IMAGE_MACHINE_EBC 0x0EBC
#define EFI_IMAGE_MACHINE_x64 0x8664
#define EFI_IMAGE_MACHINE_ARMTHUMB_MIXED 0x01C2
#define EFI_IMAGE_MACHINE_AARCH64 0xAA64

//COFFHead Characteristics

#define IMAGE_FILE_RELOCS_STRIPPED 0x0001
#define IMAGE_FILE_EXECUTABLE_IMAGE 0x0002
#define IMAGE_FILE_LINE_NUMS_STRIPPED 0x0004
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED 0x0008
#define IMAGE_FILE_AGGRESIVE_WS_TRIM 0x0010
#define IMAGE_FILE_LARGE_ADDRESS_AWARE 0x0020
#define IMAGE_FILE_BYTES_REVERSED_LO 0x0080
#define IMAGE_FILE_32BIT_MACHINE 0x0100
#define IMAGE_FILE_DEBUG_STRIPPED 0x0200
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP 0x0400
#define IMAGE_FILE_NET_RUN_FROM_SWAP 0x0800
#define IMAGE_FILE_SYSTEM 0x1000
#define IMAGE_FILE_DLL 0x2000
#define IMAGE_FILE_UP_SYSTEM_ONLY 0x4000
#define IMAGE_FILE_BYTES_REVERSED_HI 0x8000

typedef struct 
{
	uint16_t Machine;
	uint16_t NumberOfSections;
	uint32_t TimeDateStamp;
	uint32_t PointerToSymbolTable;
	uint32_t NumberOfSymbols;
	uint16_t SizeOfOptionalHeader;
	uint16_t Characteristics;
} COFFHead;

static const uint16_t COFFMagic = 0x20B; //PE32+

typedef struct
{
	uint64_t ImageBase;
	uint32_t SectionAlignment;
	uint32_t FileAlignment;
	uint16_t MajorOperatingSystemVersion;
	uint16_t MinorOperatingSystemVersion;
	uint16_t MajorImageVersion;
	uint16_t MinorImageVersion;
	uint16_t MajorSubsystemVersion;
	uint16_t MinorSubsystemVersion;
	uint32_t Win32VersionValue;
	uint32_t SizeOfImage;
	uint32_t SizeOfHeaders;
	uint32_t CheckSum;
	uint16_t Subsystem;
	uint16_t DllCharacteristics;
	uint64_t SizeOfStackReserve;
	uint64_t SizeOfStackCommit;
	uint64_t SizeOfHeapReserve;
	uint64_t SizeOfHeapCommit;
	uint32_t LoaderFlags;
	uint32_t NumberOfRvaAndSizes; //0x10
} COFFOptionalWindowsSpecificFields;

typedef struct
{
	uint32_t rva;
	uint32_t size;
} ImageDataDir;

//#define iUsedImageDirs 16

typedef struct
{
	uint16_t Magic;
	uint8_t MajorLinkerVersion;
	uint8_t MinorLinkerVersion;
	uint32_t SizeOfCode;
	uint32_t SizeOfInitializedData;
	uint32_t SizeOfUninitializedData;
	uint32_t AddressOfEntryPoint;
	uint32_t BaseOfCode;
	
	COFFOptionalWindowsSpecificFields dWindowSpecific;
	
	ImageDataDir aImageDirs[];
} COFFOptionalHead;

//#define SectionAlignmentInFile 0x20 //correspondend to 'FileAlignment' of 'COFFOptionalWindowsSpecificFields'

//
// Section characteristics
//

#define IMAGE_SCN_TYPE_NO_PAD                0x00000008  // Reserved.

#define IMAGE_SCN_CNT_CODE                   0x00000020  // Section contains code.
#define IMAGE_SCN_CNT_INITIALIZED_DATA       0x00000040  // Section contains initialized data.
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA     0x00000080  // Section contains uninitialized data.

#define IMAGE_SCN_LNK_OTHER                  0x00000100  // Reserved.
#define IMAGE_SCN_LNK_INFO                   0x00000200  // Section contains comments or some other type of information.
#define IMAGE_SCN_LNK_REMOVE                 0x00000800  // Section contents will not become part of image.
#define IMAGE_SCN_LNK_COMDAT                 0x00001000  // Section contents comdat.
#define IMAGE_SCN_NO_DEFER_SPEC_EXC          0x00004000  // Reset speculative exceptions handling bits in the TLB entries for this section.
#define IMAGE_SCN_GPREL                      0x00008000  // Section content can be accessed relative to GP
#define IMAGE_SCN_MEM_FARDATA                0x00008000
#define IMAGE_SCN_MEM_PURGEABLE              0x00020000
#define IMAGE_SCN_MEM_16BIT                  0x00020000
#define IMAGE_SCN_MEM_LOCKED                 0x00040000
#define IMAGE_SCN_MEM_PRELOAD                0x00080000

#define IMAGE_SCN_ALIGN_1BYTES               0x00100000  //
#define IMAGE_SCN_ALIGN_2BYTES               0x00200000  //
#define IMAGE_SCN_ALIGN_4BYTES               0x00300000  //
#define IMAGE_SCN_ALIGN_8BYTES               0x00400000  //
#define IMAGE_SCN_ALIGN_16BYTES              0x00500000  // Default alignment if no others are specified.
#define IMAGE_SCN_ALIGN_32BYTES              0x00600000  //
#define IMAGE_SCN_ALIGN_64BYTES              0x00700000  //
#define IMAGE_SCN_ALIGN_128BYTES             0x00800000  //
#define IMAGE_SCN_ALIGN_256BYTES             0x00900000  //
#define IMAGE_SCN_ALIGN_512BYTES             0x00A00000  //
#define IMAGE_SCN_ALIGN_1024BYTES            0x00B00000  //
#define IMAGE_SCN_ALIGN_2048BYTES            0x00C00000  //
#define IMAGE_SCN_ALIGN_4096BYTES            0x00D00000  //
#define IMAGE_SCN_ALIGN_8192BYTES            0x00E00000  //

#define IMAGE_SCN_ALIGN_MASK                 0x00F00000

#define IMAGE_SCN_LNK_NRELOC_OVFL            0x01000000  // Section contains extended relocations.
#define IMAGE_SCN_MEM_DISCARDABLE            0x02000000  // Section can be discarded.
#define IMAGE_SCN_MEM_NOT_CACHED             0x04000000  // Section is not cachable.
#define IMAGE_SCN_MEM_NOT_PAGED              0x08000000  // Section is not pageable.
#define IMAGE_SCN_MEM_SHARED                 0x10000000  // Section is shareable.
#define IMAGE_SCN_MEM_EXECUTE                0x20000000  // Section is executable.
#define IMAGE_SCN_MEM_READ                   0x40000000  // Section is readable.
#define IMAGE_SCN_MEM_WRITE                  0x80000000  // Section is writeable.

typedef struct {
	uint8_t Name[8];
	uint32_t VirtualSize;
	uint32_t VirtualAddress;
	uint32_t SizeOfRawData;
	uint32_t PointerToRawData;
	uint32_t PointerToRelocations;
	uint32_t PointerToLinenumbers;
	uint16_t  NumberOfRelocations;
	uint16_t  NumberOfLinenumbers;
	uint32_t Characteristics;
} ImageSectionHeader;

//
// Based relocation types.
//

#define IMAGE_REL_BASED_ABSOLUTE              0 
#define IMAGE_REL_BASED_HIGH                  1 
#define IMAGE_REL_BASED_LOW                   2 
#define IMAGE_REL_BASED_HIGHLOW               3 
#define IMAGE_REL_BASED_HIGHADJ               4 
#define IMAGE_REL_BASED_MIPS_JMPADDR          5 
#define IMAGE_REL_BASED_SECTION               6 
#define IMAGE_REL_BASED_REL32                 7 
 
#define IMAGE_REL_BASED_MIPS_JMPADDR16        9 
#define IMAGE_REL_BASED_IA64_IMM64            9 
#define IMAGE_REL_BASED_DIR64                 10 
#define IMAGE_REL_BASED_HIGH3ADJ              11 

typedef struct
{
	uint8_t Type : 4;
	uint16_t RelOffset : 12; //relative to 'RellocationsBaseRVA'
} ImageRelocation;

#define Max_Relative_Addr 0xFFF

typedef struct
{
	uint32_t RellocationsBaseRVA;
	uint32_t szBlock;
	
	ImageRelocation relocs[];
} ImageRelocatioBlock; //32bit alligned

typedef struct
{
	size_t szSector;
	uint8_t (*pSectorData)[];
	
	uint8_t Name[8];
	uint32_t VirtualSize;
	
	uint32_t VirtualAddress;
	uint32_t Characteristics;
} SectorDesc;



//assume Base Address 0
extern bool WriteFile(const char (*pFileName)[], /*null-terminated*/
				size_t szAmountSectors, size_t szAmountDataDirs,
				SectorDesc (*pSectorsToBeAdded)[szAmountSectors],
				ImageDataDir (*pDataDirs)[szAmountDataDirs],
				size_t szImage);

