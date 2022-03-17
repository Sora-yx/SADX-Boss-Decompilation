#include "pch.h"
#include "Chaos-common.h"
#include "Chaos0.h"

void evChaosInit()
{
    chaos_event_flag = 1;
    chaos_event_exit_flag = 0;
}

void RdChaos0Init(task* tp)
{
    taskwk* data; 
    int v2; 
    int v3; 
    int v4; 

    data = tp->twp;

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