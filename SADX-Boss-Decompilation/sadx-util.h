#pragma once

FunctionPointer(int, sadxRand, (), 0x6443BF);

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

FunctionPointer(void, effectWaterMove, (taskwk* a1, chaoswk* a2, NJS_OBJECT* a3), 0x7AEDA0);
FunctionPointer(float, Shadow, (taskwk* a1, float a2), 0x49EE30);

FunctionPointer(task*, SetCircleLimit_, (NJS_POINT3* pos, NJS_POINT3* center, float radius), 0x7AF3E0); // Creates an object that limits a position into a circle
FunctionPointer(void, RoundBGM_Play, (int a1), 0x00425800);