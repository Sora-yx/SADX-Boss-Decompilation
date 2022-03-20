#include "pch.h"
#include "Chaos-common.h"
#include "Chaos2.h"


void BossChaos2(task* tp)
{
    __int16 v5; // ax
    float v6; // ecx
    double v7; // st7
    double v8; // st6
    double v9; // st5
    double v10; // st7
    float v11; // [esp+0h] [ebp-14h]
    float v12; // [esp+0h] [ebp-14h]

    chaoswk* chaos_worker = (chaoswk*)tp->awp;
    chaoswk* chaos_worker2 = chaos_worker;
    taskwk* chaos_entity = tp->twp;

    if (chaos_entity->mode)
    {
        ExecModeChaos2(tp);
    }
    else
    {
        hintmes_tp = 0; // Good
        chaos_worker = (chaoswk*) BInitialize(chaos_entity, 192); // Good
        if (!chaos_worker)
        {
            return;
        }

        CCL_Init(tp, chaos2_colli_info, 14, 3u); // Pushes from right to left (chaos2_colli_info becomes 0x011215B0) Probably good
        SET_COLLI_RANGE(tp->twp->cwp, 300.0); // cwp is +0x38 from twp here
        setChaos2ColliParam(chaos_entity, 0); // Probably Good

        chaos_worker->bwk.req_action = 0;
        chaos_worker->bwk.action = 0;
        chaos_worker->bwk.plactptr = chaos2_action; // Places 0x0117C778
        chaos_worker->bwk.pljvptr = chaos2_jv_list; // Places 0x01120830
        chaos_entity->mode = 1;
        tp->awp = (anywk*)chaos_worker;

        chaostwp = chaos_entity;
        chaosbwp = chaos_worker; // Previously referenced the same address as chaostwp (oops)
        chaos_worker2 = chaos_worker;

        tp->disp = Chaos2Display;
        tp->dest = DeleteChaos2;
        setChaosBubble(chaos_entity, chaos_worker, &chaos2_bubble); // Probably fine
        chaos_worker->texlist = &texlist_chaos2;
        initialChaos(chaos_entity, chaos_worker, 1); // Probably fine
        ChaosUnderLightInit(); // Fine
        SetChaos2Materials(); // Fine
        
        chaos_entity->mode = 18;
        chaos_event_flag = 1;
        BSetMotion(chaos_entity, &chaos_worker->bwk);
        chaos_worker->attack_tmr = chaosparam->attack_time_base;

        object_chaos2_head0.basicmodel->mats->attrflags |= 1u;
        object_chaos2_head1.basicmodel->mats->attrflags |= 1u;
        
        BJoinVertexes(chaos_entity, &chaos_worker->bwk);
        morph_tp_0 = morph_water_set(&Chaos2_Model);
        SetChaosShakeBrain(&object_chaos2_core0);
        SetChaosCoreDisplay(tp, 1.5, (void*) 0x3C5A508, (void*) 0x11219A4); // Good
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

    if (tp->exec != DestroyTask)
    {
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
        GetMMMatrix(0x45u, ra0_matrix);
        ChaosSurfacePatternChange(chaos_worker);
        Chaos2Display(tp);
        setChaosColliParam(chaos_entity);
        v5 = chaos_worker2->dispflag;
        if ((v5 & 0x41) != 0)
        {
            DisplayChaosBallShadow(&chaos_entity->pos, 7.0);
            chaos_worker2->ground_y = 2.0;
        }
        else if ((v5 & 0x10) != 0)
        {
            v11 = chaos_worker2->sp_scale.x * 19.590952;
            DisplayChaosBallShadow(&chaos_entity->pos, v11);
        }
        v6 = chaos_worker2->HitPoint;
        ++chaos_worker2->generaltimer;
        boss_life_f = v6;
        EntryColliList(chaos_entity);

        v7 = chaos_entity->pos.z - EntityData1Ptrs[0]->Position.z;
        v8 = chaos_entity->pos.y - EntityData1Ptrs[0]->Position.y;
        v9 = chaos_entity->pos.x - EntityData1Ptrs[0]->Position.x;
        v12 = v9 * v9 + v8 * v8 + v7 * v7;
        v10 = squareroot(v12);
        if (v10 < 60.0)
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
        if (!EV_CheckCancel())
        {
            if (playertwp[0]->pos.y <= 0.0)
            {
                playertwp[0]->pos.y = 0.0;
            }
            else
            {
                playertwp[0]->pos.y = playertwp[0]->pos.y;
            }
        }
    }
}


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