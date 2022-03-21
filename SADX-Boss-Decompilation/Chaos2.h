#pragma once
#include "UsercallFunctionHandler.h"

//TaskFunc(BossChaos2, 0x54DB90);

auto ControlModeChaos2 = GenerateUsercallWrapper<void (*)(chaoswk* cwp, taskwk* twp)>(noret, 0x54CB00, rEAX, rEDI);
auto ExecModeChaos2 = GenerateUsercallWrapper<void (*)(task* chaos_object)>(noret, 0x54D510, rEAX);
auto StartBattle_0 = GenerateUsercallWrapper<void (*)(task* tp)>(noret, 0x54CCE0, rEAX);
auto setChaosColliParam = GenerateUsercallWrapper<void (*)(taskwk* twp)>(noret, 0x54B060, rEAX);

FunctionPointer(void, setChaos2ColliParam, (taskwk* twp, int mode), 0x54ACF0);
FunctionPointer(void, DisplayChaosBallShadow, (NJS_POINT3* pos, float size), 0x54ED60);

VoidFunc(SetChaos2Materials, 0x54C8A0);

TaskFunc(Chaos2Display, 0x54D840);
TaskFunc(DeleteChaos2, 0x54D790);

DataPointer(NJS_TEXLIST, texlist_chaos2, 0x117C2CC);
DataPointer(obj, object_chaos2_core0, 0x1122D6C);
DataPointer(obj, object_chaos2_head0, 0x1121EE4);
DataPointer(obj, object_chaos2_head1, 0x1125C60);

DataPointer(MORPHWK*, morph_tp_0, 0x3C63EB8);
DataPointer(BUBBLE_DATA, chaos2_bubble, 0x118EE58);
//DataPointer(CCL_INFO*, chaos2_colli_info, 0x11215B0);
DataPointer(task*, hintmes_tp, 0x3C63F0C);

DataPointer(NJS_MATRIX_PTR, ra0_matrix, 0x3C63EC0);

DataPointer(char, byte_3D0DBC2, 0x3D0DBC2);

DataArray(PL_JOIN_VERTEX, chaos2_jv_list, 0x1120830, 22);
DataArray(PL_ACTION, chaos2_action, 0x117C778, 13);
DataArray(int, c2_message_flag, 0x3C63E18, 3); // Chaos 2 Message Flags
DataArray(CHAOS_OBJPVTBL, objpos_objnum_tbl_0, 0x11218A8, 14);
DataArray(CCL_INFO, chaos2_colli_info, 0x11215B0, 14);


VoidFunc(LoadChaos2_SkyBox, 0x54A540);

/*enum Chaos2Actions
{

};*/