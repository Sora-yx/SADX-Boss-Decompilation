#pragma once

DataPointer(char, chaos_event_flag, 0x03C5A7F0);
DataPointer(char, chaos_event_exit_flag, 0x3C5A7F1);

DataPointer(float, eff_scale_a, 0x03D0D734);
DataPointer(float, eff_scale_b, 0x3D0D738);
DataPointer(float, flt_3D0D710, 0x3D0D710);
DataPointer(float, eff_c_lp_posadd, 0x03D0D58C);

DataPointer(chaoswk*, chaosbwp, 0x3C5A7D8);

void LoadEffectTexture();
void EvChaosInit();

