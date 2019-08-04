#pragma once

#pragma warning(push)
#pragma warning(disable: 4267 4838)

#include "SADXModLoader.h"
HMODULE chr_handle = GetModuleHandle(L"CHRMODELS_orig");

NJS_MATERIAL* materials_00200D48[] = {
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200D48)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200D5C)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200D70)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200D84)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200D98)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200DAC)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200DC0)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200DD4)), //Blue light on head Material
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200DE8)),
};

NJS_MATERIAL* materials_001FD8E8[] = {
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x001FD8E8)), //Lamp Material
};

NJS_MATERIAL* materials_002009C0[] = {
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x002009C0)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x002009D4)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x002009E8)), //Eye Material
};

NJS_MATERIAL* materials_0020052C[] = {
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x0020052C)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200540)), //Glowing Arrows
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00200554)), //Eye Material
};

NJS_MATERIAL* materials_00204EC8[] = {
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00204EC8)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00204EDC)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00204EF0)), //Foot Light
};

NJS_MATERIAL* materials_002062D8[] = {
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x002062D8)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x002062EC)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00206300)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x00206314)), //Foot Light
};

NJS_MATERIAL* materials_0020B9B8[] = {
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x0020B9B8)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x0020B9CC)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x0020B9E0)),
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x0020B9F4)), //Secondary Arrows
	(NJS_MATERIAL*)(((size_t)chr_handle + 0x0020BA08)),
};

#pragma warning(pop)