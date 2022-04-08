#include "pch.h"
#include "Chaos-common.h"
#include "Chaos0.h"
#include "UsercallFunctionHandler.h"

auto execModeChaos0 = GenerateUsercallWrapper<void (*)(task* a1)>(noret, 0x547FB0, rEAX);
FunctionPointer(void, setChaos0ColliParam, (taskwk* twp, int mode), 0x54A420);

int chkChaos0Collision(taskwk* twp)
{
    NJS_POINT3 spd;

    if ((twp->flag & Status_Hurt) == 0)
        return 0;

    spd.x = -2.0f;
    spd.y = 2.0f;
    bossmtn_flag &= 0xFCu;
    spd.z = 0.0f;

    if (twp->smode == 4 || twp->pos.y >= 60.0f)
    {
        if (twp->mode != MD_CHAOS_FALL)
        {
            chaos_reqmode = MD_CHAOS_FALL;
            chaos_oldmode = twp->mode;
            chaos_nextmode = chaos_oldmode;
        }
    }
    else
    {
        if (twp->mode != MD_CHAOS_DAMAGE)
        {
            chaos_reqmode = MD_CHAOS_DAMAGE;
            chaos_oldmode = twp->mode;
        }
        chaos_nextmode = MD_CHAOS_MOVE_WR;
    }
    PConvertVector_P2G(playertwp[0], &spd);
    SetVelocityP(0, spd.x, spd.y, spd.z);
    return 1;
}

void __fastcall setShakeHeadParam(double param)
{
    motionwk* shakeHeadMWP; // r11
    double result; // fp12

    shakeHeadMWP = shakehead_mwp;
    result = (float)((float)param + shakehead_mwp->spd.z);
    shakehead_mwp->spd.z = (float)param + shakehead_mwp->spd.z;
    if (result >= 2.0)
        shakeHeadMWP->spd.z = (float)2.0f * (float)0.60000002;
    else
        shakeHeadMWP->spd.z = (float)result * (float)0.60000002;
}

void chaos0Walk(taskwk* data, motionwk2* mwp, chaoswk* boss)
{
    double v3; // st7
    Angle v4; // ecx
    double shadowPos; // st7
    double v6; // st7
    float v7; // st7
    float v8; // st7
    double GetShadow; // st7
    double g_ypos2Copy; // st7
    float a2a; // [esp+0h] [ebp-2Ch]
    float a2b; // [esp+0h] [ebp-2Ch]
    float shadowPosCopy; // [esp+14h] [ebp-18h]
    float a3a; // [esp+18h] [ebp-14h]
    float a1a; // [esp+1Ch] [ebp-10h]
    Angle3 a4; // [esp+20h] [ebp-Ch] BYREF

    switch (data->smode)
    {
    case 0:
        setChaos0ColliParam(data, 0);
        chaos_attack_tmr = 0;
        boss->bwk.req_action = MD_CHAOS_MOVE;
        sound_cnt = 0;
        data->smode = 1;
        break;
    case 1:

        bossmtn_flag = 0;
        if (boss->bwk.action == MD_CHAOS_MOVE)
        {
            data->smode = 2;
        }
        break;
    case 2:
    case 3:
    case 4:
        v3 = njCos(data->ang.y);
        v4 = data->ang.y;
        data->pos.x = v3 * 0.60000002f + data->pos.x;
        data->pos.z = njSin(v4) * 0.60000002f + data->pos.z;
        walk_dist = walk_dist + 0.60000002f;
        if (!LOBYTE(boss->generaltimer))
        {
            setDrop(data, 8, 0.5f, 1.0f);
            setShakeHeadParam(0.69999999f);
        }
        break;
    default:
        break;
    }
    a2a = data->pos.y + 4.0f;
    shadowPos = GetShadowPos(data->pos.x, a2a, data->pos.z, &a4);
    shadowPosCopy = shadowPos;

    if (shadowPos <= 0.0f)
    {
        shadowPosCopy = 0.0f;
    }
    switch (data->smode)
    {
    case 2:
        boss->etcflag |= 1u;
        turnToPlayer(data, boss);
        if (data->pos.y - 1.0f <= shadowPosCopy)
        {
            a1a = njCos(data->ang.y) * 5.0f + data->pos.x;
            a3a = njSin(data->ang.y) * 5.0f + data->pos.z;
            a2b = data->pos.y + 4.0f;
            GetShadow = GetShadowPos(a1a, a2b, a3a, &a4);
            g_ypos2 = GetShadow;

            if (GetShadow <= 0.0f)
            {
                g_ypos2 = 0.0f;
            }

            if (data->pos.y + 1.0 >= g_ypos2)
            {
                data->pos.y = shadowPosCopy;
            }
            else
            {
                g_ypos2Copy = g_ypos2;
                data->wtimer = 6;
                mwp->spd.y = (g_ypos2Copy - data->pos.y) * 0.16666667f;
                data->smode= 4;
                boss->etcflag &= 0xFFFEu;
            }
        }
        else
        {
            data->smode = 3;
            mwp->spd.y = 0.0f;
            boss->etcflag &= 0xFFFEu;
        }
        break;
    case 3:
        v7 = mwp->spd.y - 0.1f;
        mwp->spd.y = v7;
        v8 = v7 + data->pos.y;
        data->pos.y = v8;

        if (v8 <= shadowPosCopy)
        {
            data->pos.y = shadowPosCopy;
            data->smode = 2;
            setDrop(data, 8, 1.0, 0.0);
            setShakeHeadParam(1.5);
        }

        break;
    case 4:
        v6 = mwp->spd.y;
        --data->wtimer;
        data->pos.y = v6 + data->pos.y;

        if (data->pos.y >= (double)g_ypos2)
        {
            data->pos.y = g_ypos2;
            data->smode = 2;
        }

        break;
    }

    if ((unsigned __int8)data->smode != 255 && ++sound_cnt > 30)
    {
        sound_cnt = 0;
        dsPlay_oneshot_Dolby(756, 0, 0, 0, 120, data);
    }
}

void execModeChaos0_(task* tp)
{
    int mode; 
    bosswk* v8;
    float v9; 
    float v10; 

    taskwk* data = tp->twp;
    chaoswk* chaosWorker = (chaoswk*)tp->awp;
    motionwk* mwp = tp->mwp;

    switch (data->mode)
    {
    case MD_CHAOS_STND:
        if (ccsi_flag)
        {
            SetChaosLifeGauge(0, 0, chaosparam->hitpoint);
            mode = (unsigned __int8)data->mode;
            camera_change_flag = 1;

            if (mode != MD_CHAOS_MOVE)
            {
                chaos_reqmode = MD_CHAOS_MOVE;
                chaos_oldmode = data->mode;
            }

            CameraSetEventCamera(50, 0);
            chaosWorker->camera_mode = 50;
            WakeTimer();
            PadReadOnP(0);
            CreateChildTask(3u, c0CheckTikalMessage, tp);
        }
        return;
    case MD_CHAOS_MOVE:
        chaos0Walk(tp->twp, (motionwk2*)tp->mwp, (chaoswk*)tp->awp);
        chkChaos0Collision(data);
        return;
    case MD_CHAOS_SJUMP:
        //chaos0Jump(tp->twp, (motionwk2*)tp->mwp, (bosswk*)tp->awp);
        return;
    case MD_CHAOS_PUNCH:
        //chaos0Punch(tp->twp, (chaoswk*)tp->awp, (bosswk*)tp->awp);
        chkChaos0Collision(data);
        return;
    case MD_CHAOS_DAMAGE:
       // Chaos0Damage(tp, (chaoswk*)tp->awp);
        return;
    case MD_CHAOS_OBJ2W:
        //Chaos0MorphO2W(tp->twp, (motionwk2*)tp->awp);
        return;
    case MD_CHAOS_W2OBJ:
       // Chaos0MorphW2O(tp->twp, (motionwk2*)tp->awp);
        return;
    case MD_CHAOS_ROLLATTACK:
       // chaos0Roll(tp->twp, (motionwk2*)tp->awp);
        chkChaos0Collision(data);
        return;
    case MD_CHAOS_ONTHEPOLE:
        //chaos0Pole(tp->twp, (motionwk2*)tp->awp);
        return;
    case MD_CHAOS_MOVE_W:
        //chaos0MoveW(tp->twp, (motionwk2*)tp->mwp, (bosswk*)tp->awp);
        return;
    case MD_CHAOS_MOVE_WR:
        if (data->smode)
        {
            if (data->smode != 1)
                return;
        }
        else
        {
            setChaos0ColliParam(tp->twp, 4);
            //data->ang.y = setApartTargetPos((taskwk*)chaosWorker, v8);
            data->smode = 1;
        }
        //moveToTarget(data, (motionwk2*)mwp, &chaosWorker->bwk);
        v9 = (float)(data->pos.x - chaosWorker->tgtpos.x);
        v10 = (float)(data->pos.z - chaosWorker->tgtpos.z);
        if ((float)((float)((float)v10 * (float)v10) + (float)((float)v9 * (float)v9)) < 112.36f)
        {
            if (data->mode != MD_CHAOS_W2OBJ)
            {
                chaos_reqmode = MD_CHAOS_W2OBJ;
                chaos_oldmode = data->mode;
            }
            chaos_nextmode = MD_CHAOS_ROLLATTACK;
        }
        return;
    case MD_CHAOS_GUARD:
       // chaos0Guard(tp->twp, (bosswk*)tp->awp);
        return;
    case MD_CHAOS_FALL:
        //chaos0Fall(tp->twp, (motionwk2*)tp->mwp, (bosswk*)tp->awp);
        return;
    case MD_CHAOS_EV_WAIT:
    case MD_CHAOS_EV_WATER:
        setChaos0ColliParam(tp->twp, 6);
        return;
    case MD_CHAOS_EDIT:
        if ((per[0]->press & Buttons_A) != 0 && !GetDebugMode())
        {
            if (data->mode != MD_CHAOS_MOVE)
            {
                chaos_reqmode = MD_CHAOS_MOVE;
                chaos_oldmode = data->mode;
                chaos_nextmode = chaos_oldmode;
            }
            setChaos0ColliParam(data, -1);
            bossmtn_flag = 0;
        }
        return;
    default:
        return;
    }
}

int Chaos0_CheckAttack(chaoswk* chwp, taskwk* twp, taskwk* player, float range)
{
    Float calcPosY;
    Float calcPosX;
    Float calcPosZ;
    double resultPos;
    int result;
    int resultCopy;

    resultCopy = 0;
    ++chaos_attack_tmr;

    if ((chwp->etcflag & 1) == 0)
        return resultCopy;

    calcPosY = (twp->pos.y - playertwp[0]->pos.y);
    calcPosX = (twp->pos.x - playertwp[0]->pos.x);
    calcPosZ = (twp->pos.z - playertwp[0]->pos.z);

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

    if (twp->mode != MD_CHAOS_PUNCH)
    {
        chaos_reqmode = MD_CHAOS_PUNCH;
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
                if (Chaos0_CheckAttack(bwp, twp, playertwp[0], 80.0f))
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

                if (squareroot((result2) > 50.0f))
                {
                    nextMove = 2;
                    goto LABEL_20;
                }
                goto LABEL_18;
            }

            return;
        }

    LABEL_22:
        if (Chaos0_CheckAttack(bwp, twp, playertwp[0], 120.0f)) //they pass the player ptr as an argument but it's not used.
        {
            chaos_nextmode = MD_CHAOS_ROLLATTACK;
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

        if (squareroot(result) > 50.0f)
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
    Float calcPosY;
    Float calcPosX;
    Float calcPosZ;
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
        SetChaosCoreDisplay(tp, 1.0f, &c00_corepos_ofs, (void*)0x1120454); //display the red effect on Chaos head
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

                if ((data->pos.y - playertwp[0]->pos.y) > 60.0f)
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

        if ((chaoswk2->etcflag & 1) != 0 && walk_dist > 5.0f)
        {
            EffectChaosTask = CreateElementalTask(2u, 5, dispEffectChaosTracks);

            if (EffectChaosTask)
            {
                EffectChaosTask->twp->counter.f = 0.80000001;
                walk_dist = 0.0f;
            }
        }

        if ((chaoswk2->dispflag & 1) != 0)
            chaoswk2->ground_y = Shadow(data, 0.80000001);

        if (data->pos.y >= 0.0f)
        {
            getPosY = data->pos.y;
        }
        else
        {
            getPosY = 0.0f;
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
    float scale = (data->counter.f * 0.25f);

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
    Float posCheck;
    float scalePos;
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
    float shadowPos;
    float sclValue; 

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
        scalePos = (data->scl.x + data->pos.y);
        sclY = data->scl.y;
        data->pos.y = data->scl.x + data->pos.y;

        if (scalePos >= sclY)
        {
            DisplayRain(tp);
        }
        else
        {
            if ((chaostwp->pos.y - playertwp[0]->pos.y) > 60.0f)
            {
                DestroyTask(tp);
                return;
            }
            data->pos.y = sclY;
            data->counter.f = 1.0f;
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
        data->pos.y = 120.0f;
        data->pos.z = camPosZ;
        rng = rand();
        posZ = data->pos.z;
        posX = data->pos.x;
        data->scl.x = -rng * (float)0.000030517578 * rain_param.spd_ofs + rain_param.spd_base;
        shadowPos = GetShadowPos(posX, 5.0f, posZ, &data->ang) + 0.1f;
        sclValue = 0.1f;
        data->scl.y = shadowPos + 0.1f;
        if ((shadowPos + 0.1f) > 0.1f)
            sclValue = (float)((float)shadowPos + 0.1f);
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
    data->mode = MD_RDCHAOS0_WAIT;
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
        if (data->mode == MD_RDCHAOS0_END)
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