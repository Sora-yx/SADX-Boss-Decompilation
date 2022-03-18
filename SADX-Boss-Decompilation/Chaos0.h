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