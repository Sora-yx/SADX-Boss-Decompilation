#include "pch.h"
#include "Chaos-common.h"
#include "Chaos2.h"

task* setChaos2()
{
    return CreateElementalTask(3u, 2, BossChaos2);
}

void LoadChaos2_SkyBOX() // Test and check if it's correct
{
    gFog = pFogTable_Chaos02[ssActNumber][ClipLevel];    // LevelFogData
    gClipSky = pClipSky_Chaos02[ssActNumber][ClipLevel]; // SkyboxDrawDistance
    gClipMap = pClipMap_Chaos02[ssActNumber][ClipLevel]; // LevelDrawDistance
    gClipSky.f32Far = gClipSky.f32Far - (float)1000.0;

    gSkyScale.x = gClipMap.f32Near;
    gSkyScale.z = gClipMap.f32Far;
}

void RdChaos2Init(task* tp)
{
    LoadChaos2_SkyBox(); // Placeholder in case my own rewrite is bad

    EvChaosInit();
    setChaos2();
    LoadEffectTexture();

    CreateElementalTask(2u, 1, Chaos2Column);

    tp->twp->mode = 1;
    if (!GetCountKilledPlayer())
    {
        c2_message_flag[0] = 0;
        c2_message_flag[1] = 0;
        c2_message_flag[2] = 0;
    }
}

void Rd_Chaos2(task* tp)
{
    taskwk* data;

    data = tp->twp;
    SetCameraControlEnabled(0);
    if (data->mode && data->mode == 2)
    {
        ADX_Close();
        ___njFogDisable();
    }
    else
    {
        RdChaos2Init(tp);
    }
}

void init_Chaos2()
{
    WriteJump(Obj_Chaos2, Rd_Chaos2);
}