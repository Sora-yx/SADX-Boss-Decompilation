#pragma once

FunctionPointer(void, initSpriteSub, (NJS_SPRITE* a1, NJS_TEXLIST* a2, NJS_TEXANIM* a3), 0x439B20);
FunctionPointer(int, GetCountKilledPlayer, (), 0x4144F0);

FunctionPointer(bool, EV_CheckCancel, (), 0x42FB00);

DataPointer(char, boss_life, 0x3C58150);
DataPointer(float, boss_life_f, 0x3C58158);

struct MPOSANG
{
	int at_angle[2];
	NJS_POINT3 gpos;
};

struct MOBJ
{
	__int16 level;
	NJS_OBJECT* obj;
	NJS_POINT3* pm;
	MPOSANG* pos_ang;
	NJS_POINT3* points_ptr_org;
};

struct MORPHWK
{
	char mode;
	__int16 objNum;
	float t;
	MOBJ* objlist;
	float puru_a0;
	float puru_dec0;
	Rotation3 puru_ang0;
	Rotation3 puru_angadd0;
};
