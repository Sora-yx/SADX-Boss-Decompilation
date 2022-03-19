#include "pch.h"
#include "Chaos-common.h"
#include "Chaos0.h"
#include "UsercallFunctionHandler.h"

auto execModeChaos0 = GenerateUsercallWrapper<void (*)(task* a1)>(noret, 0x547FB0, rEAX);

task* setChaos0()
{
    return CreateElementalTask(3u, 2, BossChaos0);
}

void DisplayRain(task* tp)
{
    taskwk* data = tp->twp;
    njPushMatrix(0);
    njTranslateV(0, &data->pos);
    njDrawLine3D(&rain_p3col, 1, 0);
    njPopMatrix(1);
    ResetMaterial();
}

void DisplayDrop(task* tp)
{
    taskwk* data = tp->twp;
    double scale = (float)(data->counter.f * (float)0.25);

    argb_10.a = data->counter.f;
    ___njSetConstantMaterial(&argb_10);
    njSetTexture(&texlist_chaos_effect);
    njColorBlendingMode(0, 8);
    njColorBlendingMode(1, 6);
    njPushMatrix(0);
    njTranslateV(0, &data->pos);
    njRotateX(0, 0x4000);
    njScale(0, scale, scale, scale);
    njDrawSprite3D(&sprite_c0_ato, 0, 0x22u);
    njPopMatrix(1);
    ResetMaterial();
    njColorBlendingMode(0, 8);
    njColorBlendingMode(1, 6);
}

void RainEffect(task* tp)
{  
    double posCheck;
    double scalePos;
    double sclY;
    double rng2;
    int rngCamRotY;
    double cosRes; 
    double sinRes;
    double camPosZ; 
    int rng; 
    double posZ;
    double posX; 
    int v15;
    double shadowPos;
    double sclValue; 

    taskwk* data = tp->twp;
    unsigned int  mode = (unsigned __int8)data->mode;

    if (data->mode)
    {
        if (mode != 1)
        {
            if (mode >= 3)
                return;

            posCheck = (float)(data->counter.f - (float)0.033333335);
            data->counter.f = data->counter.f - (float)0.033333335;
            if (posCheck >= 0.0)
            {
                DisplayDrop(tp);
                return;
            }
            DestroyTask(tp);
            return;
        }
        scalePos = (float)(data->scl.x + data->pos.y);
        sclY = data->scl.y;
        data->pos.y = data->scl.x + data->pos.y;

        if (scalePos >= sclY)
        {
            DisplayRain(tp);
        }
        else
        {
            if ((float)(chaostwp->pos.y - playertwp[0]->pos.y) > 60.0)
            {
                DestroyTask(tp);
                return;
            }
            data->pos.y = sclY;
            data->counter.f = 1.0;
            tp->disp = DisplayDrop;
            data->mode = 2;
        }
    }
    else
    {
        rng2 = (double)rand() * 0.000030517578 * 150.0;
        rngCamRotY = (unsigned __int64)((-30.0 - (double)rand() * 0.000030517578 * 120.0) * 65536.0 * 0.002777777777777778)
            - Camera_Data1->Rotation.y;
        cosRes = (float)((float)njCos(rngCamRotY) * (float)rng2);
        sinRes = njSin(rngCamRotY);
        data->pos.x = camera_twp->pos.x + (float)cosRes;
        camPosZ = (float)(camera_twp->pos.z + (float)((float)sinRes * (float)rng2));
        data->pos.y = 120.0;
        data->pos.z = camPosZ;
        rng = rand();
        posZ = data->pos.z;
        posX = data->pos.x;
        data->scl.x = -rng * (float)0.000030517578 * rain_param.spd_ofs + rain_param.spd_base;
        shadowPos = GetShadowPos(posX, 5.0, posZ, &data->ang) + 0.1;
        sclValue = 0.1;
        data->scl.y = (float)shadowPos + (float)0.1;
        if ((float)((float)shadowPos + (float)0.1) > 0.1)
            sclValue = (float)((float)shadowPos + (float)0.1);
        data->scl.y = sclValue;

        tp->disp = DisplayRain;
        data->mode = 1;
    }
}

void ctrlRainEffect(task* tp)
{
    for (int i = 0; i < rain_param.num; ++i)
        CreateElementalTask(2, 3, RainEffect);
}

void __cdecl setRainEffect()
{
    tp_raineff = CreateElementalTask(2u, 2, ctrlRainEffect);
}

void RdChaos0Init(task* tp)
{
    taskwk* data = tp->twp;

    EvChaosInit();
    setChaos0();
    LoadEffectTexture();
    //setRainEffect();
    Chaos0_Rain_Load();
    LoadChaos0_SkyBox(); //unsolved
    data->mode = 1;
    dsPlay_iloop(1026, -1, 8, 0);

    if (!GetCountKilledPlayer())
    {
        c0_message_flag[0] = 0;
        dword_3C63C04 = 0;
        dword_3C63C08 = 0;
    }
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