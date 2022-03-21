#pragma once

FunctionPointer(void, initialChaos, (taskwk* twp, chaoswk* chaos, int id), 0x7AF450);
FunctionPointer(task*, SetChaosCoreDisplay, (task* chaos_tp, float size, void* pos, void* offset), 0x7ADCE0);
FunctionPointer(void, SetChaosShakeBrain, (NJS_OBJECT* a1), 0x7AD340);
FunctionPointer(MORPHWK*, morph_water_set, (NJS_OBJECT* a1), 0x7AEAF0);
FunctionPointer(void, ChaosSurfacePatternChange, (chaoswk* chaos_wp), 0x7AF250);

VoidFunc(CreateBubble, 0x7AE2C0);
VoidFunc(ChaosUnderLightInit, 0x7AD250);

DataPointer(char, chaos_event_flag, 0x03C5A7F0);
DataPointer(char, chaos_event_exit_flag, 0x3C5A7F1);
DataPointer(char, chaos_nextmode, 0x3C5A7EC);
DataPointer(char, chaos_reqmode, 0x3C5A7ED);
DataPointer(char, chaos_oldmode, 0x3C5A7E1);

DataPointer(float, eff_scale_a, 0x03D0D734);
DataPointer(float, eff_scale_b, 0x3D0D738);
DataPointer(float, flt_3D0D710, 0x3D0D710);
DataPointer(float, eff_c_lp_posadd, 0x03D0D58C);

DataPointer(char, core_disp_flag, 0x3D0DB84);

DataPointer(chaoswk*, chaosbwp, 0x3C5A7E4);

void LoadEffectTexture();
void EvChaosInit();

struct BUBBLE_LIST
{
	__int16 id;
	char num;
	NJS_POINT3* pos;
};

struct BUBBLE_TABLE
{
	unsigned __int16 objnum;
	NJS_POINT3 pos;
	int ang[3];
};

struct BUBBLE_DATA
{
	char object_num;
	char spline_num;
	BUBBLE_LIST* list;
	BUBBLE_TABLE* tbl;
	float scl;
};

struct CHAOS_PARAM
{
	char hitpoint;
	float height;
	float leg_len;
	float walk_spd;
	int turn_spd;
	NJS_POINT3 c_initpos;
	float alpha_obj;
	float morph_xsp;
	float morph_ysp;
	float limit_r;
	float limit_r_sprate;
	float arm_strtch_spd;
	__int16 atc_tame_time;
	__int16 model_alpha;
	float puncheff_scl;
	float arm_len;
	NJS_POINT3 field_center_pos;
	float sphere_scale;
	__int16 attack_time_base;
	__int16 attack_time_ofs;
	float chaoseme_radius;
	float chaoseme_yofs;
};

struct CHAOS_OBJPVTBL
{
	char objno;
	char vecno;
	NJS_POINT3 ofs_pos;
};

FunctionPointer(void, setChaosBubble, (taskwk* twp, chaoswk* cwp, BUBBLE_DATA* tbl), 0x7AE4E0);
FunctionPointer(void, CalcChaosObjectPos, (taskwk* twp, CHAOS_OBJPVTBL* table, float yoffset), 0x7AF060);

DataPointer(CHAOS_PARAM*, chaosparam, 0x3C5A7E8);
FunctionPointer(void, SetCameraChaosStdParam, (NJS_POINT3* a1, NJS_POINT3* a2), 0x469240);

DataPointer(char, byte_3D0DBC3, 0x3D0DBC3);
DataPointer(char, byte_3D0DBC4, 0x3D0DBC4);
DataPointer(char, byte_3D0DBC5, 0x3D0DBC5);

DataPointer(float, walk_dist, 0x3C5A7F4);

TaskFunc(dispEffectChaosTracks, 0x7AD050);