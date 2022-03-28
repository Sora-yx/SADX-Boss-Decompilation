#include "pch.h"
#include "Chaos-common.h"
#include "Chaos2.h"

void ExecModeChaos2(task* chaos_object);
void ControlModeChaos2(chaoswk* cwp, taskwk* twp);

void BossChaos2(task* tp)
{
    chaoswk* chaos_worker = (chaoswk*)tp->awp;
    chaoswk* chaos_worker2 = chaos_worker;
    taskwk* chaos_entity = tp->twp;

    if (chaos_entity->mode)
    {
        ExecModeChaos2(tp);
    }
    else
    {
        hintmes_tp = 0;
        chaos_worker = (chaoswk*) BInitialize(chaos_entity, 192);
        if (!chaos_worker) return;

        CCL_Init(tp, chaos2_colli_info, 14, 3u);
        SET_COLLI_RANGE(tp->twp->cwp, 300.0);
        setChaos2ColliParam(chaos_entity, 0);

        chaos_worker->bwk.req_action = 0;
        chaos_worker->bwk.action = 0;
        chaos_worker->bwk.plactptr = chaos2_action;
        chaos_worker->bwk.pljvptr = chaos2_jv_list;
        chaos_entity->mode = 1;
        tp->awp = (anywk*)chaos_worker;

        chaostwp = chaos_entity;
        chaosbwp = chaos_worker;
        chaos_worker2 = chaos_worker;

        tp->disp = Chaos2Display;
        tp->dest = DeleteChaos2;
        setChaosBubble(chaos_entity, chaos_worker, &chaos2_bubble);
        chaos_worker->texlist = &texlist_chaos2;
        initialChaos(chaos_entity, chaos_worker, 1);
        ChaosUnderLightInit();
        SetChaos2Materials();
        
        chaos_entity->mode = 18;
        chaos_event_flag = 1;
        BSetMotion(chaos_entity, &chaos_worker->bwk);
        chaos_worker->attack_tmr = chaosparam->attack_time_base;

        object_chaos2_head0.basicmodel->mats->attrflags |= 1u;
        object_chaos2_head1.basicmodel->mats->attrflags |= 1u;
        
        BJoinVertexes(chaos_entity, &chaos_worker->bwk);
        morph_tp_0 = morph_water_set(&Chaos2_Model);
        SetChaosShakeBrain(&object_chaos2_core0);
        SetChaosCoreDisplay(tp, 1.5, (void*) 0x3C5A508, (void*) 0x11219A4); // Array/Pointer types aren't fully known, using void* instead
        chaos_nextmode = 0;
    }

    if (chaos_event_flag)
    {
        core_disp_flag = 0;
        if (chaos_worker2->generaltimer > 1 && !EV_CheckCancel())
        {
            if (chaos_entity->smode != -1)
            {
                chaos_entity->smode = -1;
                ExecModeChaos2(tp);
            }
            StartBattle_0(tp);
            if (chaos_entity->mode != 1)
            {
                chaos_reqmode = 1;
                chaos_oldmode = chaos_entity->mode;
            }
        }
    }
    else
    {
        ControlModeChaos2(chaos_worker, chaos_entity);
    }

    if (tp->exec == DestroyTask) return;

    byte_3D0DBC2 = chaos_entity->mode == 0xC;
    byte_3D0DBC3 = byte_3D0DBC2;
    byte_3D0DBC4 = byte_3D0DBC2;
    byte_3D0DBC5 = byte_3D0DBC2;

    if (chaos_entity->mode != chaos_reqmode)
    {
        if (chaos_entity->smode != -1)
        {
            chaos_entity->smode = -1;
            ExecModeChaos2(tp);
        }
        chaos_oldmode = chaos_entity->mode;
        chaos_entity->mode = chaos_reqmode;
        chaos_entity->smode = 0;
    }
    if ((bossmtn_flag & 2) == 0)
    {
        BSetMotion(chaos_entity, &chaos_worker->bwk);
    }
    BJoinVertexes(chaos_entity, &chaos_worker->bwk);
    CalcChaosObjectPos(chaos_entity, objpos_objnum_tbl_0, chaosparam->leg_len);
    if ((chaos_worker2->dispflag & 1) != 0)
    {
        CreateBubble();
    }

    GetMMMatrix(0x45, &ra0_matrix._11);
    ChaosSurfacePatternChange(chaos_worker);
    tp->disp(tp);
    setChaosColliParam(chaos_entity);

    short display_flag = chaos_worker2->dispflag;
    if ((display_flag & 0x41) != 0)
    {
        // Set normal chaos shadow
        DisplayChaosBallShadow(&chaos_entity->pos, 7.0);
        chaos_worker2->ground_y = 2.0;
    }
    else if ((display_flag & 0x10) != 0)
    {
        // Set shadow when chaos not in walk form
        float shadow_size = chaos_worker2->sp_scale.x * 19.590952;
        DisplayChaosBallShadow(&chaos_entity->pos, shadow_size);
    }

    ++chaos_worker2->generaltimer;
    boss_life_f = chaos_worker2->HitPoint;
    EntryColliList(chaos_entity);

    float zDif = chaos_entity->pos.z - playertwp[0]->pos.z;
    float yDif = chaos_entity->pos.y - playertwp[0]->pos.y;
    float xDif = chaos_entity->pos.x - playertwp[0]->pos.x;
    float difRoot = squareroot(xDif * xDif + yDif * yDif + zDif * zDif);

    if (difRoot < 60.0)
    {
        dsPlay_timer_v(
            1020,
            (int)chaos_entity,
            1,
            0,
            10,
            chaos_entity->pos.x,
            chaos_entity->pos.y,
            chaos_entity->pos.z);
    }

    LoopTaskC(tp);
    if (EV_CheckCancel()) return;

    if (playertwp[0]->pos.y <= 0.0)
    {
        playertwp[0]->pos.y = 0.0;
    }
    else
    {
        playertwp[0]->pos.y = playertwp[0]->pos.y;
    }
}

void CameraChaos2()
{
    taskwk* player_object = playertwp[0];

    if (player_object->pos.y < c2_tgtposchg_ypos)
    {
        cameraControlWork.tgtxpos = chaostwp->pos.x;
        cameraControlWork.tgtypos = chaostwp->pos.y;
        cameraControlWork.tgtzpos = chaostwp->pos.z;
    }
    else
    {
        cameraControlWork.tgtxpos = player_object->pos.x;
        cameraControlWork.tgtypos = player_object->pos.y;
        cameraControlWork.tgtzpos = player_object->pos.z;
    }

    cameraControlWork.tgtxpos += chaoscam_tgtpos_ofs.x;
    cameraControlWork.tgtypos += chaoscam_tgtpos_ofs.y;
    cameraControlWork.tgtzpos += chaoscam_tgtpos_ofs.z;
    calcAddAngle(0);
    calcCamTargetPos(1);
    calcCameraPos(0);

    // There's a maximum y value for the camera here, so it limits it
    if (cameraControlWork.camypos >= c2_camypos_max)
    {
        cameraControlWork.camypos = c2_camypos_max;
    }
}

#pragma region Chaos2 Mode Functions
void Chaos2Walk(taskwk* twp, chaoswk* cwp, motionwk2* mwp)
{
    if (twp->smode)
    {
        if (twp->smode != 1)
        {
            if (twp->smode == 2)
            {
                cwp->tgtpos = playertwp[0]->pos;
                moveToTargetChaos(twp, mwp, cwp);
                if (!cwp->generaltimer)
                {
                    setDrop(twp, 8, 0.5, 1.0);
                }
                if (walk_dist_Chaos2 > 5.0)
                {
                    task* chaos_tracks_obj = CreateElementalTask(2, 2, dispEffectChaosTracks);
                    if (chaos_tracks_obj)
                    {
                        chaos_tracks_obj->twp->counter.f = 1.6;
                        walk_dist_Chaos2 -= (int)walk_dist_Chaos2;
                    }
                }
                if (++sound_cnt_0 > 30)
                {
                    NJS_VECTOR chaos_pos = twp->pos;
                    sound_cnt_0 = 0;
                    dsPlay_oneshot_v(756, 0, 0, 0, chaos_pos.x, chaos_pos.y, chaos_pos.z);
                }
            }
            return;
        }
    }
    else
    {
        cwp->dispflag = 1;
        core_disp_flag = 1;
        cwp->etcflag &= 0xFDu;
        setChaos2ColliParam(twp, 1);
        cwp->bwk.req_action = 1;
        twp->smode = 1;
        walk_dist_Chaos2 = 0.0;
    }

    bossmtn_flag &= 0xFDu;
    if (cwp->bwk.action == 1)
    {
        sound_cnt_0 = 0;
        twp->smode = 2;
    }
}
#pragma endregion
// Calls different mode functions based on the current chaos 2 mode
void ExecModeChaos2(task* chaos_object)
{
    motionwk2* chaos_motionworker = (motionwk2*) chaos_object->mwp;
    taskwk* chaos_entity = chaos_object->twp;
    chaoswk* chaos_anyworker = (chaoswk*) chaos_object->awp;

    switch (chaos_entity->mode)
    {
    case 1:
        chaos_anyworker->etcflag |= 2u;
        setChaos2ColliParam(chaos_entity, 0);
        if (ccsi_flag && chaos_nextmode != 14)
        {
            SetChaosLifeGauge(0, 0, chaosparam->hitpoint);
            CameraSetEventCameraFunc((CamFuncPtr)CameraChaos2, 0, 3);
            if (chaos_entity->mode != 0xA)
            {
                chaos_reqmode = 0xA;
                chaos_oldmode = chaos_entity->mode;
            }
            chaos_nextmode = 14;
            WakeTimer();
            EnableController(0);
            EnableControl();
            hintmes_tp = CreateElementalTask(2u, 2, c2CheckTikalMessage);
        }
        break;
    case 2:
        chaos_anyworker->etcflag &= 0xFDu;
        Chaos2Walk(chaos_entity, chaos_anyworker, chaos_motionworker);
        CheckDamageChaos2(chaos_entity);
        break;
    case 3:
        chaos_anyworker->etcflag |= 2u;
        Chaos2Damage(chaos_anyworker, chaos_object);
        break;
    case 4:
        chaos_anyworker->etcflag |= 2u;
        Chaos2MorphWater2Ball(chaos_anyworker, chaos_entity);
        break;
    case 6:
        chaos_anyworker->etcflag |= 2u;
        break;
    case 7:
        chaos_anyworker->etcflag |= 2u;
        Chaos2Jump(chaos_entity, chaos_motionworker, chaos_anyworker);
        CheckDamageChaos2(chaos_entity);
        break;
    case 8:
        Chaos2MorphO2W(chaos_anyworker, chaos_entity);
        break;
    case 9:
        Chaos2MorphW2O(chaos_anyworker, chaos_entity);
        break;
    case 0xA:
    case 0xB:
        chaos_anyworker->etcflag |= 2u;
        Chaos2MorphBall(chaos_entity, chaos_anyworker, chaos_anyworker);
        break;
    case 0xC:
        chaos_anyworker->etcflag |= 2u;
        Chaos2Punch(chaos_entity, chaos_anyworker, chaos_anyworker);
        CheckDamageChaos2(chaos_entity);
        break;
    case 0xD:
        chaos_anyworker->etcflag |= 2u;
        Chaos2PunchS(chaos_anyworker, chaos_entity, chaos_anyworker);
        CheckDamageChaos2(chaos_entity);
        break;
    case 0xE:
        chaos_anyworker->etcflag |= 2u;
        Chaos2BallAttack(chaos_object, chaos_motionworker, chaos_anyworker);
        break;
    case 0xF:
        chaos_anyworker->etcflag |= 2u;
        Chaos2WaterAttack(chaos_anyworker, chaos_object);
        break;
    case 0x10:
        chaos_anyworker->etcflag |= 2u;
        Chaos2SplitBallAttack(chaos_object, chaos_entity, chaos_anyworker);
        break;
    case 0x11:
        Chaos2Guard(chaos_anyworker, chaos_object->twp);
        break;
    case 0x12:
    case 0x13:
        setChaos2ColliParam(chaos_entity, 0);
        break;
    case 0x14:
        if ((ControllerPointers[0]->PressedButtons & Buttons_A) != 0 && !GetDebugMode())
        {
            if (chaos_entity->mode != 2)
            {
                chaos_reqmode = 2;
                chaos_oldmode = chaos_entity->mode;
            }
            CameraSetEventCamera(53, 0);
            bossmtn_flag = 0;
        }
        break;
    default:
        return;
    }
}
void ControlModeChaos2(chaoswk* cwp, taskwk* twp)
{
    if (ChaosCheckGuard(cwp, twp)) return;
    if (!ChaosCheckAttack(twp, cwp)) return;

    char chaos_mode = twp->mode;

    double first_rng = sadxRand() / 32768.0;
    switch ((int) cwp->HitPoint)
    {
        case 1:
        case 2:
        {
            if (first_rng <= 0.80000001) // first_rng <= 0.80000001
            {
                if (first_rng <= 0.60000002)
                {
                    PrintDebug("Punch");
                    if (chaos_mode != 12)
                    {
                        chaos_reqmode = 12; // Punch
                        chaos_oldmode = chaos_mode;
                    }

                    chaos_punch_num = 2;
                    if (sadxRand() / 32768.0 >= 0.5) // sadxRand() / 32768.0 >= 0.5
                    {
                        chaos_punch_num = 3;
                    }
                    chaos_nextmode = 2; // Walk
                }
                if (chaos_mode != 10)
                {
                    chaos_reqmode = 10; // Morph Ball
                    chaos_oldmode = chaos_mode;
                }
                chaos_nextmode = 16; // SplitBallAttack
            }
            else
            {
                PrintDebug("Water Attack");
                if (chaos_mode != 15)
                {
                    chaos_reqmode = 15; // Water Attack
                    chaos_oldmode = chaos_mode;
                }
                chaos_nextmode = 2; // Walk
            }
            break;
        }
        case 3:
        {
            if (first_rng <= 0.60000002)
            {
                if (chaos_mode != 12)
                {
                    chaos_reqmode = 12; // Punch
                    chaos_oldmode = chaos_mode;
                }

                chaos_punch_num = 2;
                if (sadxRand() / 32768.0 >= 0.5)
                {
                    chaos_punch_num = 3;
                }
                chaos_nextmode = 7; // Jump
            }
            else
            {
                if (chaos_mode != 15)
                {
                    chaos_reqmode = 15; // Water Attack
                    chaos_oldmode = chaos_mode;
                }
                chaos_nextmode = 7; // Jump
            }
            break;
        }
        case 4:
        {
            if (first_rng <= 0.75)
            {
                if (chaos_mode != 12)
                {
                    chaos_reqmode = 12; // Punch
                    chaos_oldmode = chaos_mode;
                }

                chaos_punch_num = 2;
                if (sadxRand() / 32768.0 >= 0.5)
                {
                    chaos_punch_num = 3;
                }
                chaos_nextmode = 2; // Walk
            }
            else
            {
                if (chaos_mode != 10)
                {
                    chaos_reqmode = 10; // Morph Ball
                    chaos_oldmode = chaos_mode;
                }
                chaos_nextmode = 14; // Ball Attack
            }
            break;
        }

        default:
            return;
    }        
}

#pragma region ChaosInit

void Chaos2Column_(task* tp)
{
    _OBJ_LANDENTRY* collision_list = objLandTable1600.pLandEntry;
    int collision_count = objLandTable1600.ssCount;

    for (int i = 0; i < 16; i++)
    {
        bool skip = false;

        NJS_OBJECT* current_column = column_tbl[i];
        _OBJ_LANDENTRY* collision_list_copy = collision_list;
        column_alpha[i] = 1.0;

        int j = 0;
        while (collision_list_copy->pObject != current_column)
        {
            j++;
            collision_list_copy++;
            if (j >= collision_count)
            {
                skip = true;
                break;
            }
        }

        if (!skip)
            column_landtbl[i] = collision_list_copy;
    }

    tp->disp = Chaos2ColumnDisplay;
    tp->exec = Chaos2ColumnMain;

    column_alpha_flag = 0;
}

task* setChaos2()
{
    return CreateElementalTask(3u, 2, BossChaos2);
}

void LoadChaos2_SkyBox() // Test and check if it's correct
{
    gFog = pFogTable_Chaos02[ssActNumber][ClipLevel];    // LevelFogData
    gClipSky = pClipSky_Chaos02[ssActNumber][ClipLevel]; // SkyboxDrawDistance
    gClipMap = pClipMap_Chaos02[ssActNumber][ClipLevel]; // LevelDrawDistance
    gClipSky.f32Far = gClipSky.f32Far - (float)1000.0;
    
    gSkyScale = SkyBoxScale_Chaos2[ssActNumber][ClipLevel];
}

void RdChaos2Init(task* tp)
{
    LoadChaos2_SkyBox();

    EvChaosInit();
    setChaos2();
    LoadEffectTexture();

    CreateElementalTask(2u, 1, Chaos2Column_);

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
    if (!data->mode)
    {
        RdChaos2Init(tp);
    }
    else if (data->mode == 2)
    {
        ADX_Close();
        ___njFogDisable();
    }
}

void init_Chaos2()
{
    WriteJump(Obj_Chaos2, Rd_Chaos2);
}
#pragma endregion