#include "pch.h"
#include "Chaos-common.h"
#include "Chaos0.h"

void LoadEffectTexture()
{
    initSpriteSub(&sprite_c0_attack_a, &texlist_chaos_effect, anim_c0_attack_a);
    initSpriteSub(&stru_3D0D714, &texlist_chaos_effect, anim_c0_attack_b);
    initSpriteSub(&sprite_c0_attack_c, &texlist_chaos_effect, &anim_c0_attack_c);
    initSpriteSub(&sprite_c0_drop, &texlist_chaos_effect, &anim_c0_drop);
    initSpriteSub(&sprite_c0_ato, &texlist_chaos_effect, &anim_c0_ato);
    BigEntityArrayBLength = 0;
    BigEntityArrayLength = 0;
    eff_scale_a = 1.3;
    eff_scale_b = 1.3;
    flt_3D0D710 = 1.0;
    eff_c_lp_posadd = 0.2;
}

void EvChaosInit()
{
    chaos_event_flag = 1;
    chaos_event_exit_flag = 0;
}