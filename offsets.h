#pragma once

#ifndef OFFSETS_H
#define OFFSETS_H
#include <cstddef>
 
#define PTRDIFF_ inline std::ptrdiff_t
namespace offsets
{
 
//vgk 1.17.4.2
	PTRDIFF_ vgk_shadow = 0x82AC8;     //0F B6 05 ? ? ? ? 4C 8B 05 ? ? ? ?	  > mov     r8, cs:qword_140082AC8
	PTRDIFF_ qword_2	 = 0x82C50;		//48 8B 3D ?? ?? ?? ?? 49 33 D4		  > mov     rdi, cs:qword_140082C50
	PTRDIFF_ byte_1	 = 0x82B90;		//0F B6 35 ?? ?? ?? ?? 41 BC E8 00 00 00 > movzx   esi, cs:byte_140082B90
 
}

#endif

//usage

uintptr_t DecryptClonedCr3(uintptr_t VgkAddress, uintptr_t qword_1)
	{
		if (!VgkAddress) return NULL;
		if (!qword_1) return NULL;

		 
		auto qword_2 = Read<uintptr_t>(VgkAddress + offsets::qword_2);  
 		auto byte_1 = Read<uint8_t>(VgkAddress + offsets::byte_1);  

		uintptr_t v5 = (0x49B74B6480000000i64 * qword_1
			+ 0xC2D8B464B4418C6Cui64 * ~(unsigned __int64)(unsigned __int8)byte_1
			+ 0x66B8CDC1FFFFFFFFi64 * (unsigned __int8)byte_1
			+ 0x5C1FE6A2B4418C6Di64
			* ((unsigned __int8)(byte_1 & qword_1)
				- (qword_1 | ~(unsigned __int64)(unsigned __int8)byte_1)))
			* ((qword_1 ^ (unsigned __int8)byte_1)
				+ -2 * ((unsigned __int8)byte_1 ^ (qword_1 | (unsigned __int8)byte_1))
				+ 2
				* ((((unsigned __int8)byte_1 | 0xE8i64) ^ 0xFFFFFFFFFFFFFF17ui64)
					+ (~qword_1 | (unsigned __int8)byte_1 ^ 0xE8i64))
				- ((unsigned __int8)byte_1 ^ (unsigned __int64)~qword_1 ^ 0xE8)
				+ -3 * ~qword_1
				- 232);

		uintptr_t v6 = ((qword_1 ^ (qword_1 * (0x13D0F34E00000000i64 * qword_1 + 0x483C4F8900000000i64))) << 63)
			+ qword_1
			* (0x7D90DC33C620C593i64 * (0x13D0F34E00000000i64 * qword_1 + 0x483C4F8900000000i64)
				+ 0x8000000000000000ui64)
			+ (qword_1
				* (0x55494E5B80000000i64 * qword_2
					+ 0xC83B18136241A38Dui64 * ~qword_2
					+ 0xCE3CE5E180000000ui64 * ~qword_1
					+ 0x72F1C9B7E241A38Di64 * ((qword_2 | 0xE8) - (231i64 - ((unsigned __int8)qword_2 & 0xE8))))
				+ 0x71C31A1E80000000i64)
			* (0x99BF7D2380CF6EC3ui64 * qword_2
				+ 0x664082DC7F30913Ei64 * (qword_1 | (unsigned __int8)byte_1)
				+ 0x19BF7D2380CF6EC2i64 * ~qword_2
				+ 0xE64082DC7F30913Eui64 * (~qword_1 & ~(unsigned __int64)(unsigned __int8)byte_1)
				+ ((qword_1
					+ ((unsigned __int8)byte_1 & (qword_2 ^ qword_1))
					+ (qword_2 | (unsigned __int8)byte_1)) << 63));

		uintptr_t DecryptedCr3 = 0x137FEEF6AB38CFB4i64 * v5
			+ ((~v5 ^ ~((0x8000000000000001ui64 * qword_2
				+ 0x2FDBF65F8A4AC9C9i64 * qword_1
				+ ((qword_2 ^ qword_1) << 63)
				+ 0x502409A075B53637i64 * qword_1)
				* (0xFD90DC33C620C592ui64
					* ~(qword_1 * (0x13D0F34E00000000i64 * qword_1 + 0x483C4F8900000000i64))
					+ v6
					+ 0x2183995CC620C592i64))) << 63)
			+ 0x6C80110954C7304Di64 * ((v5 & qword_2) - (~qword_2 & ~v5) - qword_2)
			- 0x7FFFFFFFFFFFFFFFi64
			* (0x8000000000000001ui64 * qword_2
				+ 0x2FDBF65F8A4AC9C9i64 * qword_1
				+ ((qword_2 ^ qword_1) << 63)
				+ 0x502409A075B53637i64 * qword_1)
			* (0xFD90DC33C620C592ui64 * ~(qword_1 * (0x13D0F34E00000000i64 * qword_1 + 0x483C4F8900000000i64))
				+ v6
				+ 0x2183995CC620C592i64)
			- 0x4F167C5CD4C7304Ei64;


		return DecryptedCr3;
	}

ShadowRegionsDataStructure Data = Read<ShadowRegionsDataStructure>(VgkAddress + offsets::vgk_shadow); //Check if ShadowRegion Structure is Valid
uintptr_t DecryptedCr3 = DecryptClonedCr3(VgkAddress, Data.ClonedCr3); //Should Add Checks For VgkAddress

mem::custom_cr3 = DecryptedCr3; //Original Cr3
mem::plm4_base = Data.FreeIndex << 39; //0x27 //Pml4Base
