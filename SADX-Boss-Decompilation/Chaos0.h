#pragma once

DataPointer(NJS_TEXLIST, texlist_chaos_effect, 0x038E1E94);
DataPointer(NJS_SPRITE, sprite_c0_attack_a, 0x3D0D56C);
DataPointer(NJS_SPRITE, stru_3D0D714, 0x3D0D714); //symbol didn't have the name for some reason
DataPointer(NJS_SPRITE, sprite_c0_attack_c, 0x3D0D73C); 
DataPointer(NJS_SPRITE, sprite_c0_drop, 0x3D0D75C);
DataPointer(NJS_SPRITE, sprite_c0_ato, 0x3D0D594);

DataArray(NJS_TEXANIM, anim_c0_attack_a, 0x038D8EE8, 15);
DataArray(NJS_TEXANIM, anim_c0_attack_b, 0x038D9018, 10);
DataPointer(NJS_TEXANIM, anim_c0_attack_c, 0x38D90E0);
DataPointer(NJS_TEXANIM, anim_c0_drop, 0x038D90F4);
DataPointer(NJS_TEXANIM, anim_c0_ato, 0x38D9108);

DataPointer(task*, tp_raineff, 0x3C63C0C);

struct RAINEFF
{
	int num;
	float len_base;
	float len_ofs;
	float spd_base;
	float spd_ofs;
	float ang_base[3];
	float ang_ofs[3];
};

DataPointer(RAINEFF, rain_param, 0x0112026C);
DataPointer(NJS_ARGB, argb_10, 0x01120310);
DataPointer(NJS_POINT3COL, rain_p3col, 0x01120300);

DataArray(___stcClip, pClipSky_Chaos00, 0x111F764, 1);
DataPointer(___stcClip, pClipMap_Chaos00, 0x111F768);


VoidFunc(LoadChaos0_SkyBox, 0x545CE0);
DataArray(int, c0_message_flag, 0x3C63C00, 3);
DataPointer(int, dword_3C63C04, 0x3C63C04);
DataPointer(int, dword_3C63C08, 0x3C63C08);


DataArray(CCL_INFO, chaos0_colli_info, 0x1120320, 5);
DataPointer(char, camera_change_flag, 0x3C63C20);

FastcallFunctionPointer(void, SetChaos0LandFlags, (int flag), 0x5485E0);

DataPointer(NJS_POINT3, campos_pole_ofs, 0x112041C);
DataArray(CHAOS_OBJPVTBL, objpos_objnum_tbl, 0x1120428, 2);

TaskFunc(Chaos0Display, 0x548360);
VoidFunc(sub_546340, 0x546340);

//not sure if this is correct
DataArray(PL_JOIN_VERTEX, chaos0_jv_list, 0x3C63930, 33);
DataArray(PL_ACTION, chaos0_action, 0x3C63AE0, 16);

DataPointer(task*, ShakeChaos0_Task, 0x03C63C14);

TaskFunc(ShakeChaos0Head, 0x549C00);
VoidFunc(sub_547350, 0x547350);

DataPointer(BUBBLE_DATA, chaos0_bubble, 0x0112014C);
VoidFunc(setMaterialChaos0, 0x547D50);
DataPointer(MORPHWK*, morph_tp, 0x03C63C10);

DataPointer(char, byte_3D0DBCF, 0x3D0DBCF);
DataPointer(char, byte_3D0DBC6, 0x3D0DBC6);
DataPointer(char, byte_3D0DBC7, 0x3D0DBC7);
DataPointer(char, byte_3D0DBC8, 0x3D0DBC8);
DataPointer(char, byte_3D0DBD2, 0x3D0DBD2);


DataPointer(NJS_POINT3, c00_corepos_ofs, 0x03C5A358);
DataPointer(task*, climit_tp, 0x3C63C38);
DataPointer(NJS_VECTOR, limpos, 0x1120448);
DataPointer(char, poleact_flag, 0x03C63E00);
DataPointer(int, chaos_attack_tmr, 0x03C5A7DC);