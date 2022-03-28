#pragma once
#include "UsercallFunctionHandler.h"

//auto ControlModeChaos2 = GenerateUsercallWrapper<void (*)(chaoswk* cwp, taskwk* twp)>(noret, 0x54CB00, rEAX, rEDI);
auto ChaosCheckGuard = GenerateUsercallWrapper<int (*)(chaoswk* cwp, taskwk* twp)>(rEAX, 0x54C9C0, rECX, rESI);
auto ChaosCheckAttack = GenerateUsercallWrapper<int (*)(taskwk* twp, chaoswk* cwp)>(rEAX, 0x54CA90, rEAX, rESI);
auto StartBattle_0 = GenerateUsercallWrapper<void (*)(task* tp)>(noret, 0x54CCE0, rEAX);
auto setChaosColliParam = GenerateUsercallWrapper<void (*)(taskwk* twp)>(noret, 0x54B060, rEAX);

#pragma region Chaos2 Mode Functions
auto CheckDamageChaos2 = GenerateUsercallWrapper<void (*)(taskwk* chaos_entity)>(noret, 0x54C910, rESI);
auto Chaos2Damage = GenerateUsercallWrapper<void (*)(chaoswk* chaos_worker, task* tp)>(noret, 0x54BDC0, rESI, stack4);
//auto Chaos2Walk = GenerateUsercallWrapper<void (*)(taskwk* chaos_entity, chaoswk* chaos_worker, motionwk2* motion_worker)>(noret, 0x54B210, rEDI, rESI, stack4);
auto Chaos2MorphWater2Ball = GenerateUsercallWrapper<void (*)(chaoswk* cwp, taskwk* twp)>(noret, 0x54C400, rEDI, rESI);
auto Chaos2Jump = GenerateUsercallWrapper<void (*)(taskwk* twp, motionwk2* mwp, chaoswk* cwp)>(noret, 0x54C610, rESI, stack4, stack4);
auto Chaos2MorphO2W = GenerateUsercallWrapper<void (*)(chaoswk* cwp, taskwk* twp)>(noret, 0x54C070, rEDI, rESI);
auto Chaos2MorphW2O = GenerateUsercallWrapper<void (*)(chaoswk* cwp, taskwk* twp)>(noret, 0x54C230, rEDI, rESI);
FunctionPointer(void, Chaos2MorphBall, (taskwk* twp, chaoswk* cwp, chaoswk* cwp2), 0x54F190);
auto Chaos2Punch = GenerateUsercallWrapper<void (*)(taskwk* twp, chaoswk* cwp, chaoswk* cwp2)>(noret, 0x54B4A0, rEAX, rEDI, stack4);
auto Chaos2PunchS = GenerateUsercallWrapper<void (*)(chaoswk* cwp, taskwk* twp, chaoswk* cwp2)>(noret, 0x54BAD0, rEBX, rESI, stack4);
FunctionPointer(void, Chaos2BallAttack, (task* tp, motionwk2* mwp, chaoswk* cwp), 0x54E5D0);
auto Chaos2WaterAttack = GenerateUsercallWrapper<void (*)(chaoswk* cwp, task* tp)>(noret, 0x54D110, rEDI, stack4);
FunctionPointer(void, Chaos2SplitBallAttack, (task* tp, taskwk* twp, chaoswk* cwp), 0x54FC90);
auto Chaos2Guard = GenerateUsercallWrapper<void (*)(chaoswk* cwp, taskwk* pwp)>(noret, 0x54AE30, rEDI, rESI);
#pragma endregion



FunctionPointer(void, setChaos2ColliParam, (taskwk* twp, int mode), 0x54ACF0);
FunctionPointer(void, DisplayChaosBallShadow, (NJS_POINT3* pos, float size), 0x54ED60);
FunctionPointer(void, c2CheckTikalMessage, (task* tp), 0x54A740);

VoidFunc(SetChaos2Materials, 0x54C8A0);

TaskFunc(Chaos2Display, 0x54D840);
TaskFunc(DeleteChaos2, 0x54D790);
TaskFunc(Chaos2ColumnDisplay, 0x54AA30);
TaskFunc(Chaos2ColumnMain, 0x54AC70);

DataPointer(_OBJ_LANDTABLE, objLandTable1600, 0x112136C);
DataPointer(NJS_TEXLIST, texlist_chaos2, 0x117C2CC);
DataPointer(obj, object_chaos2_core0, 0x1122D6C);
DataPointer(obj, object_chaos2_head0, 0x1121EE4);
DataPointer(obj, object_chaos2_head1, 0x1125C60);

DataPointer(MORPHWK*, morph_tp_0, 0x3C63EB8);
DataPointer(BUBBLE_DATA, chaos2_bubble, 0x118EE58);
//DataPointer(CCL_INFO*, chaos2_colli_info, 0x11215B0);
DataPointer(task*, hintmes_tp, 0x3C63F0C);
DataPointer(NJS_POINT3, chaoscam_tgtpos_ofs, 0x3C4ACC4);
DataPointer(float, c2_camypos_max, 0x118E698);
DataPointer(float, c2_tgtposchg_ypos, 0x118E69C);
DataPointer(float, walk_dist_Chaos2, 0x3C5A7F4);
DataPointer(char, column_alpha_flag, 0x3C63E28);
DataPointer(int, sound_cnt_0, 0x3C63F2C);

DataPointer(D3DMATRIX, ra0_matrix, 0x3C63EC0);

DataPointer(char, byte_3D0DBC2, 0x3D0DBC2);

DataArray(PL_JOIN_VERTEX, chaos2_jv_list, 0x1120830, 22);
DataArray(PL_ACTION, chaos2_action, 0x117C778, 13);
DataArray(int, c2_message_flag, 0x3C63E18, 3); // Chaos 2 Message Flags
DataArray(CHAOS_OBJPVTBL, objpos_objnum_tbl_0, 0x11218A8, 14);
DataArray(CCL_INFO, chaos2_colli_info, 0x11215B0, 14);
DataArray(NJS_OBJECT*, column_tbl, 0x1121550, 16);
DataArray(float, column_alpha, 0x3C63E30, 16);
DataArray(_OBJ_LANDENTRY*, column_landtbl, 0x3C63E70, 16);


//VoidFunc(LoadChaos2_SkyBox, 0x54A540);

