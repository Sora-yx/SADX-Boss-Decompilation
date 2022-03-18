#include "pch.h"
#include "Chaos-common.h"
#include "Chaos0.h"

task* setChaos0()
{
    return CreateElementalTask(3u, 2, BossChaos0);
}

void RdChaos0Init(task* tp)
{
    taskwk* data; 
    int v2; 
    int v3; 
    int v4; 

    data = tp->twp;

    EvChaosInit();
    setChaos0();
    LoadEffectTexture();

}

void Rd_Chaos0(task* tp)
{   
    taskwk* data = tp->twp;

    SetCameraControlEnabled(0);

    if (data->mode)
    {
        if (data->mode == 2)
        {
            ADX_Close();
            ___njFogDisable();
        }
    }
    else
    {
        RdChaos0Init(tp);
    }
}

void init_Chaos0()
{
    WriteJump(Obj_Chaos0, Rd_Chaos0);
}