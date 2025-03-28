#pragma once

#ifndef OFFSETS_H
#define OFFSETS_H
#include <cstddef>
 
#define PTRDIFF_ inline std::ptrdiff_t
namespace offsets
{
	PTRDIFF_ vgk_shadow = 0x819C8;     //0F B6 05 ? ? ? ? 4C 8B 05 ? ? ? ?	  > mov     r8, cs:qword_140083F08
	PTRDIFF_ qword_2	 = 0x81B50;		//48 8B 3D ?? ?? ?? ?? 49 33 D4		  > mov     rdi, cs:qword_140084090
	PTRDIFF_ byte_1	 = 0x81A90;		//0F B6 35 ?? ?? ?? ?? 41 BC E8 00 00 00 > movzx   esi, cs:byte_140083FD0
}

#endif
