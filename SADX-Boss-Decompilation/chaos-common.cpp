#include "pch.h"
#include "Chaos-common.h"
#include "Chaos0.h"

//used to play delayed music on Chaos fights
void __cdecl Chaos_gdcontrol(task* tp)
{
    taskwk* data = tp->twp;
    __int16 timer;

    timer = data->wtimer--;

    if (timer < 0)
    {
        InitializeSoundManager();
        RoundBGM_Play(data->mode);
        DestroyTask(tp);
    }
}

//set Player and Chaos start positions
void InitialChaosPos(taskwk* twp)
{
    taskwk* p1 = playertwp[0];
    SetPlayerInitialPosition(playertwp[0]);
    CHAOS_PARAM* chaosparam_ = chaosparam;
    twp->pos.x = chaosparam->c_initpos.x;
    twp->pos.y = chaosparam_->c_initpos.y;
    twp->pos.z = chaosparam_->c_initpos.z;

    int angle = (int)(atan2((float)(twp->pos.z - p1->pos.z), (float)((float)twp->pos.x - p1->pos.x)) * 65536.0 * 0.1591549762031479);

    p1->ang.y = angle;
    twp->ang.y = -angle;
}

//load different chaos textures effects
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

//init flags
void EvChaosInit()
{
    chaos_event_flag = 1;
    chaos_event_exit_flag = 0;
}

void SetChaosLifeGauge(signed int xpos, signed int ypos, signed int max)
{
    float vertical_scale;
    taskwk* life_gauge = CreateElementalTask(2, 6, ChaosLifeGauge)->twp;

    if (xpos <= 0)
    {
        life_gauge->pos.x = HorizontalStretch * 600.0;
        vertical_scale = VerticalStretch * 48.0;
    }
    else
    {
        life_gauge->pos.x = xpos;
        vertical_scale = ypos;
    }

    life_gauge->pos.y = vertical_scale;
    life_max = max;
    boss_life = max;
    boss_life_f = max;
}