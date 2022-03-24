#include "pch.h"
#include "Chaos-common.h"
#include "Chaos0.h"
#include "UsercallFunctionHandler.h"

auto execModeChaos0 = GenerateUsercallWrapper<void (*)(task* a1)>(noret, 0x547FB0, rEAX);

int Chaos0_CheckAttack(chaoswk* chwp, taskwk* twp, taskwk* player, float range)
{
    double calcPosY;
    double calcPosX;
    double calcPosZ;
    double resultPos;
    int result;
    int resultCopy;

    resultCopy = 0;
    ++chaos_attack_tmr;

    if ((chwp->etcflag & 1) == 0)
        return resultCopy;

    calcPosY = (float)(twp->pos.y - playertwp[0]->pos.y);
    calcPosX = (float)(twp->pos.x - playertwp[0]->pos.x);
    calcPosZ = (float)(twp->pos.z - playertwp[0]->pos.z);

    resultPos = squareroot((float)((float)((float)calcPosZ * (float)calcPosZ)
        + (float)((float)((float)calcPosX * (float)calcPosX)
            + (float)((float)calcPosY * (float)calcPosY))));

    if (resultPos < 30.0)
        resultCopy = 1;

    if (resultPos < range && chaos_attack_tmr > 180)
    {
        resultCopy = 1;
        chaos_attack_tmr = 0;
        goto LABEL_8;
    }

    if (!resultCopy)
        return resultCopy;

LABEL_8:
    result = resultCopy;
    if (twp->mode != 6)
    {
        chaos_reqmode = 6;
        chaos_oldmode = twp->mode;
        chaos_nextmode = chaos_oldmode;
    }

    return result;
}

void ctrlActionChaos0(taskwk* twp, motionwk2* mwp, chaoswk* bwp)
{
    int mode; 
    int nextMove;

    float calcPosY; 
    float calcPosX; 
    float calcPosZ; 
    float result;

    float calcposY2;
    float calcposX2;
    float calcposZ2;
    float result2;

    int chaosHP = (int)bwp->HitPoint;

    if (chaosHP != 1)
    {
        if (chaosHP != 2)
        {
            if (chaosHP == 3 && twp->mode == 2)
            {
                if (Chaos0_CheckAttack(bwp, twp, playertwp[0], 80.0))
                    chaos_punch_num = 2;
            }
            return;
        }

        mode = (unsigned __int8)twp->mode;

        if (mode != 2)
        {
            if (mode == MD_CHAOS_ROLLATTACK && (unsigned __int8)twp->smode == 255)
            {
                calcposY2 = (twp->pos.y - playertwp[0]->pos.y);
                calcposX2 = (twp->pos.x - playertwp[0]->pos.x);
                calcposZ2 = (twp->pos.z - playertwp[0]->pos.z);
                result2 = calcposZ2 * calcposZ2 + calcposX2 * calcposX2 + calcposY2 * calcposY2;

                if (squareroot((result2) > 50.0))
                {
                    nextMove = 2;
                    goto LABEL_20;
                }
                goto LABEL_18;
            }

            return;
        }

    LABEL_22:
        if (Chaos0_CheckAttack(bwp, twp, playertwp[0], 120.0))
        {
            chaos_nextmode = 11;
            chaos_punch_num = 3;
        }
        return;
    }

    mode = (unsigned __int8)twp->mode;

    if (mode == 2)
        goto LABEL_22;

    if (mode == 11 && (unsigned __int8)twp->smode == 255)
    {
        if (!(++poleact_flag & 1))
        {
            nextMove = 4;
            twp->counter.b[0] = 2;
        LABEL_20:
            if (nextMove != twp->mode)
            {
                chaos_reqmode = nextMove;
                chaos_nextmode = twp->mode;
                chaos_oldmode = chaos_nextmode;
            }
            return;
        }

        calcPosY = (twp->pos.y - playertwp[0]->pos.y);
        calcPosX = (twp->pos.x - playertwp[0]->pos.x);
        calcPosZ = (twp->pos.z - playertwp[0]->pos.z);
        result = calcPosZ * calcPosZ + calcPosX * calcPosX + calcPosY * calcPosY;

        if (squareroot(result) > 50.0)
        {
            nextMove = 2;
            goto LABEL_20;
        }
    LABEL_18:
        nextMove = 4;
        twp->counter.b[0] = 4;
        goto LABEL_20;
    }
}

void StartBattle_Chaos0(task* tp)
{
    taskwk* data = tp->twp;
    chaoswk* chaosWorker = (chaoswk*)tp->awp;

    InitialChaosPos(data);
    SetDisplayBossName("Chaos 0", -1, 240, 60);
    SetCameraChaosStdParam(0, 0);
    SetParamCameraChaosStageInit(data, 10.0, 20.0, 240);
    CameraSetEventCamera(52, 0);
    camera_change_flag = 0;
    SleepTimer();
    PadReadOffP(0);
    climit_tp = SetCircleLimit_(&playertwp[0]->pos, &limpos, 90.0); 
    SetViewAngle(12743);

    ADX_Close();
    task* gdControlTask = CreateElementalTask(LoadObj_Data1, 0, Chaos_gdcontrol); //manage music start 
    gdControlTask->twp->mode = 20;
    gdControlTask->twp->wtimer = 60;

    chaos_event_flag = 0;
    core_disp_flag = 1;
    
    unsigned __int16 chaosEtcFlag = chaosWorker->etcflag;
    chaosWorker->dispflag = 1;
    chaosWorker->etcflag = chaosEtcFlag & 0xFFFB;
}

void BossChaos0_(task* tp)
{
    obj* v8; 
    obj** v9;
    obj* v10;
    obj* v11;
    obj* v12;
    obj* v13;
    NJS_POINT3* v14; 
    __int16 v15; 
    int* colFlags; 
    int colCount; 
    int mode; 
    _BOOL1 v19; 
    char v20; 
    __int16 v21; 
    __int16 camMode;
    int camModeCopy; 
    NJS_POINT3* camPos; 
    task* EffectChaosTask; 
    double hitPoint;
    double calcPosY;
    double calcPosX;
    double calcPosZ;
    double posY; 
    double playerPosY; 
    double getPosY;

    taskwk* data = tp->twp;
    chaoswk* chaosworker = (chaoswk*)tp->awp;
    motionwk* chaosMWP = tp->mwp;
    chaoswk* chaoswk2 = chaosworker;

    if (data->mode)
    {
        execModeChaos0(tp); //control chaos 0 actions
    }
    else
    {
        cameraControlWork.camsmode = 0;
        chaosworker = (chaoswk*)BInitialize(data, 0xC0u);

        if (!chaosworker)
            return;

        CCL_Init(tp, chaos0_colli_info, 5, 2u);
        SET_COLLI_RANGE(tp->twp->cwp, 300.0);
        chaosworker->bwk.req_action = 0;
        chaosworker->bwk.action = 0;
        chaosworker->bwk.plactptr = chaos0_action; //not sure if the size is correct
        chaosworker->bwk.pljvptr = chaos0_jv_list; // //
        data->mode = 1;
        tp->awp = (anywk*)chaosworker;
        chaosbwp = chaosworker;
        chaoswk2 = chaosworker;
        chaostwp = data;
        sub_546340(); //assign some part of chaos model to some variables, also call clear flag

        BOSSCHAOS0_OBJECTS[33]->evalflags &= 0xFFFFFFFD; 
        chaos_reqmode = data->mode;
        chaosworker->argb_ofs[0].a = 0.0;
        chaosworker->argb_ofs[0].r = 0.0;
        chaosworker->argb_ofs[0].g = 0.0;
        chaosworker->argb_ofs[0].b = 0.0;
        ShakeChaos0_Task =  CreateElementalTask(3u, 2, ShakeChaos0Head);
        tp->dest = (TaskFuncPtr)Chaos0_Delete;
        sub_547350(); //set some scalue value to Chaos model and clear some flags
        setChaosBubble(data, chaosworker, &chaos0_bubble);
        chaosworker->sp_mode = 0;
        effectWaterMove(data, chaosworker, &Chaos_Puddle_Model);
        chaosworker->texlist = *BOSSCHAOS0_TEXLISTS;
        initialChaos(data, chaosworker, 0);
        ChaosUnderLightInit();
        setMaterialChaos0();
        BSetMotion(data, &chaosworker->bwk);
        BJoinVertexes(data, &chaosworker->bwk);
        morph_tp = morph_water_set(BOSSCHAOS0_OBJECTS[33]);
        SetChaosShakeBrain(BOSSCHAOS0_OBJECTS[39]);

        //apply the "visible flag" to every part of the geometry that has collision
        if ((*LANDTABLEBOSSCHAOS0)->COLCount - 1 >= 0)
        {
            colFlags = &(*LANDTABLEBOSSCHAOS0)->Col->Flags;
            colCount = (*LANDTABLEBOSSCHAOS0)->COLCount;
            do
            {
                if ((*colFlags & 0x2000) != 0)
                {
                    *colFlags |= 0x80000000;
                }

                colFlags += 9;
                --colCount;

            } while (colCount);
        }

        tp->disp = Chaos0Display;
        core_disp_flag = 0;

        if (data->mode != MD_CHAOS_EV_WAIT)
        {
            chaos_reqmode = MD_CHAOS_EV_WAIT;
            chaos_oldmode = data->mode;
        }

        chaos_event_flag = 1;
        SetChaosCoreDisplay(tp, 1.0, &c00_corepos_ofs, (void*)0x1120454); //display the red effect on Chaos head
        core_disp_flag = 1;
    }

    if (chaos_event_flag)
    {
        core_disp_flag = 0;

        if (chaoswk2->generaltimer > 1 && !EV_CheckCancel())
        {
            StartBattle_Chaos0(tp);
            chaosworker->bwk.req_action = MD_CHAOS_INIT;
            chaosworker->bwk.action = MD_CHAOS_INIT;

            if ((unsigned __int8)data->smode != 255)
            {
                data->smode = -1;
                execModeChaos0(tp);
            }

            if (data->mode != MD_CHAOS_STND)
            {
                chaos_reqmode = MD_CHAOS_STND;
                chaos_oldmode = data->mode;
            }
        }
    }
    else
    {
        ctrlActionChaos0(data, (motionwk2*)chaosMWP, chaosworker); //decide chaos's next move based on his HP
    }

    if (tp->exec != DestroyTask)
    {
        mode = data->mode;

        if (mode == MD_CHAOS_PUNCH || (v19 = mode == MD_CHAOS_ROLLATTACK, v20 = MD_CHAOS_INIT, v19))
            v20 = MD_CHAOS_STND;

        //those variable seem to be unused but just in case...
        byte_3D0DBC3 = v20;
        byte_3D0DBC4 = v20;
        byte_3D0DBC5 = v20;
        byte_3D0DBCF = v20;
        byte_3D0DBC6 = v20;
        byte_3D0DBC7 = v20;
        byte_3D0DBC8 = v20;
        byte_3D0DBD2 = v20;

        if (data->mode != chaos_reqmode)
        {
            if ((unsigned __int8)data->smode != 255)
            {
                data->smode = -1;
                execModeChaos0(tp);
            }

            chaos_oldmode = data->mode;
            data->mode = chaos_reqmode;
            data->smode = 0;
        }

        //manage camera between regular and the one when Chaos jump on the pole
        if (camera_change_flag)
        {
            if (!chaos_event_flag)
            {
                camMode = 50;

                if ((float)(data->pos.y - playertwp[0]->pos.y) > 60.0)
                {
                    camMode = 51;
                }

                if (data->mode == MD_CHAOS_EDIT)
                {
                    camMode = 0;
                }

                if (chaoswk2->camera_mode != camMode)
                {
                    chaoswk2->camera_mode = camMode;
                    CameraSetEventCamera(camMode, 0);
                    SetChaos0LandFlags(-51 - ((camMode == 51) - 52));
                    camPos = &campos_pole_ofs;

                    if (camMode != 51)
                        camPos = 0;

                    SetCameraChaosStdParam(0, camPos);
                }
            }
        }

        if ((bossmtn_flag & 2) == 0)
            BSetMotion(data, &chaosworker->bwk);

        BJoinVertexes(data, &chaosworker->bwk);

        if ((chaoswk2->dispflag & 1) != 0)
            CreateBubble();

        CalcChaosObjectPos(data, objpos_objnum_tbl, chaosparam->leg_len);
        ChaosSurfacePatternChange(chaosworker);
        Chaos0Display(tp);

        if ((chaoswk2->etcflag & 1) != 0 && walk_dist > 5.0)
        {
            EffectChaosTask = CreateElementalTask(2u, 5, dispEffectChaosTracks);

            if (EffectChaosTask)
            {
                EffectChaosTask->twp->counter.f = 0.80000001;
                walk_dist = 0.0;
            }
        }

        if ((chaoswk2->dispflag & 1) != 0)
            chaoswk2->ground_y = Shadow(data, 0.80000001);

        if (data->pos.y >= 0.0)
        {
            getPosY = data->pos.y;
        }
        else
        {
            getPosY = 0.0;
        }

        data->pos.y = getPosY;
        hitPoint = chaoswk2->HitPoint;
        ++chaoswk2->generaltimer;
        boss_life_f = hitPoint;
        calcPosY = (float)(data->pos.y - playertwp[0]->pos.y);
        calcPosX = (float)(data->pos.x - playertwp[0]->pos.x);
        calcPosZ = (float)(data->pos.z - playertwp[0]->pos.z);

        if (squareroot((float)((float)((float)calcPosZ * (float)calcPosZ)
            + (float)((float)((float)calcPosX * (float)calcPosX)
                + (float)((float)calcPosY * (float)calcPosY)))) < 60.0) 
        {
            dsPlay_timer_v(1020, (int)data, 1, 0, 10, data->pos.x, data->pos.y, data->pos.z);
        }

        dsPlay_timer_v(1022, (int)data, 1, 0, 10, 171.39, 167.0, 442.64999);
        dsPlay_timer_v(1024, (int)data, 1, 0, 10, 151.56, 1.0, 393.29001);
        EntryColliList(data);
        LoopTaskC(tp);

        posY = data->pos.y;

        if (posY <= 0.0)
            posY = 0.0;

        data->pos.y = posY;

        if (!EV_CheckCancel())
        {
            playerPosY = playertwp[0]->pos.y;

            if (playerPosY <= 0.0)
                playerPosY = 0.0;

            playertwp[0]->pos.y = playerPosY;
        }
    }
}

task* setChaos0()
{
    return CreateElementalTask(3u, 2, BossChaos0_);
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
    //setRainEffect(); //unsolved
    Chaos0_Rain_Load();
    LoadChaos0_SkyBox(); //unsolved
    data->mode = 1;
    dsPlay_iloop(1026, -1, 8, 0);

    if (!GetCountKilledPlayer()) //used to display tikal hints
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