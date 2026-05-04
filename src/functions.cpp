#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"
#include "variables.h"
#include <string>
#include <cstdint>
//#include <iostream>
//#include <thread>
#include <cstdlib> // Needed for std::atoi

SV_GameSendServerCommand_t SV_GameSendServerCommand = (SV_GameSendServerCommand_t)0x588340;
Cbuf_AddText_t Cbuf_AddText = (Cbuf_AddText_t)0x563BE0;
OpenMenu_t OpenMenu = (OpenMenu_t)0x59DDE0;
SV_SpawnServer_t SV_SpawnServer = (SV_SpawnServer_t)0x589D90;
BalanceTeams_t BalanceTeams = (BalanceTeams_t)0x4D73B0;
MapRestart_t MapRestart = (MapRestart_t)0x5850A0;
Cbuf_AddCall_t Cbuf_AddCall = (Cbuf_AddCall_t)0x563C90;


namespace functions
{
void SetDvarInt(std::uintptr_t dvarAddress, int value)
{
    DWORD dwPointer = *reinterpret_cast<DWORD*>(dvarAddress);
    *reinterpret_cast<int*>(dwPointer + 0xC) = value;
}

void SetDvarFloat(std::uintptr_t dvarAddress, float value)
{
    DWORD dwPointer = *reinterpret_cast<DWORD*>(dvarAddress);
    *reinterpret_cast<float*>(dwPointer + 0xC) = value;
}

    // Values
    // Memory Addresses
    std::uintptr_t mFOV = 0xAAC1F8;              // FOV
    std::uintptr_t mFOVMin = 0x88CB54;           // FOV Min
    std::uintptr_t mFPS = 0x1B90730;             // FPS
    std::uintptr_t mChat = 0xAA61C0;             // Chat
    std::uintptr_t mMapSize = 0x886E7C;          // Map Size
    std::uintptr_t mBypassMouseInput = 0xAB2B0C; // Mouse Bypass Input
    std::uintptr_t mMouseAccel = 0xBC37E0;       // Mouse Acceleration
    std::uintptr_t mYawSpeed = 0xAB2B08;         // Yaw Speed
    std::uintptr_t mPitchSpeed = 0xAB2B14;       // Pitch Speed
    std::uintptr_t mMouseFilter = 0xBC4490;      // m_filter
    std::uintptr_t mNoCamo1 = 0x695D9C4;  // No Camo
    std::uintptr_t mNoCamo2 = 0x695D860;  // No Camo
    std::uintptr_t mNoFog1 = 0x695DB18;   // No Fog
    std::uintptr_t mNoFog2 = 0x695D9D0;   // No Fog
    std::uintptr_t mNoBullets = 0x88E20C; // No Bullets
    std::uintptr_t mMovie = 0x695D898;    // Movies
    std::uintptr_t mGunX = 0xAAF7FC;       // cg_gun_x
    std::uintptr_t mGunY = 0xAAF7D4;       // cg_gun_y
    std::uintptr_t mGunZ = 0xAAF7E4;       // cg_gun_z
    std::uintptr_t mCustomPort = 0x642D6CC; // net_port
    std::uintptr_t mDLCLocation = 0x637A7C0; // DLC Location
    std::uintptr_t mAccountLevelLoc = 0x1B8B768; // Account Level Location
    std::uintptr_t mPrestigeLoc = 0x1B8B770; // Prestige Location

    void handleMouseCursor()
    {
        ImGuiIO &io = ImGui::GetIO();
        if (gui::open)
        {
            io.MouseDrawCursor = true;
            // Tell the game to release the mouse to the UI
            *reinterpret_cast<BYTE *>(0x6427D3D) = 0;
        }
        else
        {
            io.MouseDrawCursor = false;
            // Tell the game to capture the mouse again
            *reinterpret_cast<BYTE *>(0x6427D3D) = 1;
        }
    }
    void debug()
    {
        // Make map larger to verify
        SetDvarFloat(mMapSize, 2.0f);
    }
    int getHostId()
    {
        auto hostid = reinterpret_cast<int *>(0x00AB5DDC);
        return *hostid;
    }
    int GetAmmo(int client)
    {
        auto hostid = reinterpret_cast<int *>(0x1B0E42C + (client * 0x366C)); // done
        return *hostid;
    }
    void fuckTheSunAway()
    {
        if (!variables::bDrawSun)
        {
            Cbuf_AddText(0, "r_drawsun 1");
        }
        else
        {
            Cbuf_AddText(0, "r_drawsun 0");
        }
    }

    void clearGlass()
    {
        if (!variables::bGlass)
        {
            Cbuf_AddText(0, "glass_angular_vel 5 35;glass_edge_angle 5 10;glass_fall_delay 0.2 0.9;glass_fall_gravity 800;glass_fall_ratio 1.5 3;glass_fringe_maxcoverage 0.2;glass_fringe_maxsize 150;glass_fx_chance 0.25;glass_hinge_friction 50;glass_linear_vel 200 400;glass_max_pieces_per_frame 100;glass_max_shatter_fx_per_frame 6;glass_physics_chance 0.15;glass_physics_maxdist 512;glass_shard_maxsize 300;glass_shattered_scale 48;glass_trace_interval 100");
        }
        else
        {
            Cbuf_AddText(0, "glass_angular_vel 180 180;glass_edge_angle 5 10;glass_fall_delay 0 0;glass_fall_gravity 800;glass_fall_ratio 0 0;glass_fringe_maxcoverage 0;glass_fringe_maxsize 0;glass_fx_chance 0;glass_hinge_friction 0;glass_linear_vel 10000 10000;glass_max_pieces_per_frame 1;glass_max_shatter_fx_per_frame 1;glass_physics_chance 0;glass_physics_maxdist 0;glass_shard_maxsize 1;glass_shattered_scale 999999;glass_trace_interval 1");
        }
    }

    void sendNoCamo()
    {
        SetDvarInt(mNoCamo1, variables::fNoCamoBool ? variables::fNoCamo1 : 1);
        SetDvarInt(mNoCamo2, variables::fNoCamoBool ? variables::fNoCamo2 : 1);
    }

    void sendNoFog()
    {
        SetDvarInt(mNoFog1, variables::fNoCFogBool ? variables::fNoFog1 : 1);
        SetDvarInt(mNoFog2, variables::fNoCFogBool ? variables::fNoFog2 : 1);
    }

    void sendNoBullets()
    {
        SetDvarInt(mNoBullets, variables::fNoBulletsBool ? variables::fNoBullets : 1);
    }

    void sendMovie()
    {
        SetDvarInt(mMovie, variables::fMovieBool ? variables::fMovie : 0);
    }

    void sendFPSandFOV()
    {
        SetDvarFloat(mFOV, variables::fFieldOfView);
        *reinterpret_cast<int*>(0x638152C) = variables::iFPS; // FPS
    }

    void sendMapSize()
    {
        SetDvarFloat(mMapSize, variables::fMapSize);
    }

    void funFOVMin()
    {
        SetDvarFloat(mFOVMin, variables::fFOVMin ? variables::fFOVMinSlider : variables::fFOVMinDefault);
    }


    void funChat()
    {
        SetDvarInt(mChat, variables::bChat ? 12000 : 0);
    }
    void bypassMouseInput()
    {
        // cl_bypassMouseInput
        SetDvarInt(mBypassMouseInput, variables::fBypassMouseInput);
    }

    void mouseAccel()
    {
        // cl_mouseAccel
        SetDvarFloat(mMouseAccel, variables::fMouseAccel);
    }

    void yawspeed()
    {
        // cl_yawspeed
        SetDvarFloat(mYawSpeed, variables::fYawSpeed);
    }

    void pitchspeed()
    {
        // cl_pitchspeed
        SetDvarFloat(mPitchSpeed, variables::fPitchSpeed);
    }

    void mousefilter()
    {
        SetDvarInt(mMouseFilter, variables::fMouseFilter);
    }

    void funMouseFix()
    {
        /*
        * < -noforcemaccel -noforcemparms > in launch options
            dword_B173DC = sub_5BDBD0((char)"m_pitch", 0.022, -1.0, 1.0, 1);
            dword_B173D4 = sub_5BDBD0((char)"m_yaw", 0.022, -1.0, 1.0, 1);
            dword_BC37D8 = sub_5BDBD0((char)"m_forward", 0.25, -1.0, 1.0, 1);
            dword_BC4488 = sub_5BDBD0((char)"m_side", 0.25, -1.0, 1.0, 1);
            dword_BC4490 = sub_5BDB40((char)"m_filter", 0, 1);
           */
        Cbuf_AddText(0, "cl_maxpackets 100; cl_packetdup 5"); // not really a mouse fix but yolo added connection fixer here, thanks twinz
        bypassMouseInput();
        mouseAccel();
        yawspeed();
        pitchspeed();
        mousefilter();
    }
    void doSaveBarracks()
    {
        *reinterpret_cast<int*>(0x1B8B7B0) = std::atoi(variables::BarracksWins);
        *reinterpret_cast<int*>(0x1B8B7B4) = std::atoi(variables::BarracksLosses);
        *reinterpret_cast<int*>(0x1B8B7B8) = std::atoi(variables::BarracksTies);
        *reinterpret_cast<int*>(0x1B8B7BC) = std::atoi(variables::BarracksWinStreak);
        *reinterpret_cast<int*>(0x1B8b77C) = std::atoi(variables::BarracksKills);
        *reinterpret_cast<int*>(0x1B8B790) = std::atoi(variables::BarracksHeadshots);
        *reinterpret_cast<int*>(0x1B8B78C) = std::atoi(variables::BarracksAssists);
        *reinterpret_cast<int*>(0x1B8B780) = std::atoi(variables::BarracksKillStreak);
        *reinterpret_cast<int*>(0x01B8B784) = std::atoi(variables::BarracksDeaths);
        *reinterpret_cast<int*>(0x1B8B79C) = std::atoi(variables::BarracksTimePlayed);
    }

    void doGiveDeag()
    {
        *(int *)0x1B8BB7C = 327776; // class 2
        *(int *)0x1B8BBBC = 327776; // class 3
        *(int *)0x1B8BBFC = 327776; // class 4
        *(int *)0x1B8BC7C = 327776; // class 6
        *(int *)0x1B8BCFC = 327776; // class 8
        *(int *)0x1B8BD3C = 327776; // class 9
    }
    /*
        void writeMemory(DWORD dwAddress, void *bytes, DWORD dwSize)
        {
            DWORD flOldProtect = 0;
            VirtualProtect((void *)dwAddress, dwSize, PAGE_EXECUTE_READWRITE, &flOldProtect);
            memcpy((void *)dwAddress, bytes, dwSize);
            VirtualProtect((void *)dwAddress, dwSize, flOldProtect, &flOldProtect);
        }
     */
    void writeMemory(DWORD dwAddress, void *bytes, DWORD dwSize)
    {
        DWORD flOldProtect = 0;

        // Change memory protection to allow writing
        VirtualProtect(reinterpret_cast<void*>(dwAddress), dwSize, PAGE_EXECUTE_READWRITE, &flOldProtect);

        // Write the bytes
        memcpy(reinterpret_cast<void*>(dwAddress), bytes, dwSize);

        // Restore the original memory protection
        VirtualProtect(reinterpret_cast<void*>(dwAddress), dwSize, flOldProtect, &flOldProtect);
    }


    void unlockAll()
    {
        const uint8_t NOP = 0x90;
        uint8_t *unlockAll = (uint8_t *)malloc(2572);
        if (unlockAll != NULL)
        {
            memset(unlockAll, NOP, 2572);
            writeMemory(0x01B8BD8F, unlockAll, 2572);
            free(unlockAll);
        }
    }
    void doLevel70()
    {
        *(DWORD *)mAccountLevelLoc = 2651000;
    }
    void doLevel1()
    {
        *(DWORD *)mAccountLevelLoc = 0;
    }
    void sendPrestige(int prestige)
    {
        *(DWORD *)mPrestigeLoc = prestige;
    }
    void doDLCMaps()
    {
        switch (variables::iDLCMode)
        {
        case 1:
            *(int *)mDLCLocation = 8; // DLC 1
            break;
        case 2:
            *(int *)mDLCLocation = 4; // DLC 2
            break;
        default:
            *(int *)mDLCLocation = 0; // No DLC
            break;
        }
    }
    void WriteBytes(LPVOID address, const char *bytes, int length)
    {
        DWORD origProtect;
        VirtualProtect(address, length, PAGE_EXECUTE_READWRITE, &origProtect);
        memcpy(address, bytes, length);
    }

    void doMaxPlayers(int amount)
    {
        if(amount < 2 || amount > 18) return;

        std::string player = std::to_string(amount);
        std::string command = "sv_maxclients " + player + ";party_maxplayers " + player + ";ui_maxclients " + player;
        Cbuf_AddText(0, command.c_str());

    }
    void doStartMatch()
    {
        Cbuf_AddText(0, ";xblive_privatematch 1;wait 2;xpartygo;wait 2;xblive_privatematch 0;");
    }
    void doBalanceTeams()
    {
        BalanceTeams(reinterpret_cast<void *>(G_LOBBYDATA));
        BalanceTeams(reinterpret_cast<void *>(PARTYSESSION_P));
    }
    void FastRestart()
    {
        MapRestart(0, 0);
        return;
    }
    void ChangeMap()
    {
        SV_SpawnServer((char *)variables::realmaplist[variables::imap_list_number], 0, 0);
        return;
    }
    void ChangeGamemode()
    {
        switch (variables::igamemode_list_number)
        {
        case 0:
            Cbuf_AddText(0, "g_gametype dom; ui_gametype dom; party_gametype dom");
            break;
        case 1:
            Cbuf_AddText(0, "g_gametype war; ui_gametype war; party_gametype war");
            break;
        case 2:
            Cbuf_AddText(0, "g_gametype sd; ui_gametype sd; party_gametype sd");
            break;
        case 3:
            Cbuf_AddText(0, "g_gametype ffa; ui_gametype ffa; party_gametype ffa");
            break;
        case 4:
            Cbuf_AddText(0, "g_gametype koth; ui_gametype koth; party_gametype koth");
            break;
        case 5:
            Cbuf_AddText(0, "g_gametype dem; ui_gametype dem; party_gametype dem");
            break;
        case 6:
            Cbuf_AddText(0, "g_gametype sab; ui_gametype sab; party_gametype sab");
            break;
        case 7:
            Cbuf_AddText(0, "g_gametype ctf; ui_gametype ctf; party_gametype ctf");
            break;
        case 8:
            Cbuf_AddText(0, "g_gametype gtnw; ui_gametype gtnw; party_gametype gtnw");
            break;
        case 9:
            Cbuf_AddText(0, "g_gametype oneflag; ui_gametype oneflag; party_gametype oneflag");
            break;
        case 10:
            Cbuf_AddText(0, "g_gametype vip; ui_gametype vip; party_gametype vip");
            break;
        case 11:
            Cbuf_AddText(0, "g_gametype arena; ui_gametype arena; party_gametype arena");
            break;
        default:
            Cbuf_AddText(0, "g_gametype dom; ui_gametype dom; party_gametype dom"); // default to domination if failed
            break;
        }
    }

    void doForceHost()
    {
        Cbuf_AddText(0, "party_connectTimeout 1000");
        Cbuf_AddText(0, "party_connectTimeout 1");
        Cbuf_AddText(0, "party_host 1");
        Cbuf_AddText(0, "party_hostmigration 0");
        Cbuf_AddText(0, "onlinegame 1");
        Cbuf_AddText(0, "onlinegameandhost 1");
        Cbuf_AddText(0, "onlineunrankedgameandhost 0");
        Cbuf_AddText(0, "migration_msgtimeout 0");
        Cbuf_AddText(0, "migration_timeBetween 999999");
        Cbuf_AddText(0, "migration_verboseBroadcastTime 0");
        Cbuf_AddText(0, "migrationPingTime 0");
        Cbuf_AddText(0, "bandwidthtest_duration 0");
        Cbuf_AddText(0, "bandwidthtest_enable 0");
        Cbuf_AddText(0, "bandwidthtest_ingame_enable 0");
        Cbuf_AddText(0, "bandwidthtest_timeout 0");
        Cbuf_AddText(0, "cl_migrationTimeout 0");
        Cbuf_AddText(0, "lobby_partySearchWaitTime 0");
        Cbuf_AddText(0, "bandwidthtest_announceinterval 0");
        Cbuf_AddText(0, "partymigrate_broadcast_interval 99999");
        Cbuf_AddText(0, "partymigrate_pingtest_timeout 0");
        Cbuf_AddText(0, "partymigrate_timeout 0");
        Cbuf_AddText(0, "partymigrate_timeoutmax 0");
        Cbuf_AddText(0, "partymigrate_pingtest_retry 0");
        Cbuf_AddText(0, "partymigrate_pingtest_timeout 0");
        Cbuf_AddText(0, "g_kickHostIfIdle 0");
        Cbuf_AddText(0, "sv_cheats 1");
        Cbuf_AddText(0, "xblive_playEvenIfDown 1");
        Cbuf_AddText(0, "party_hostmigration 0");
        Cbuf_AddText(0, "badhost_endGameIfISuck 0");
        Cbuf_AddText(0, "badhost_maxDoISuckFrames 0");
        Cbuf_AddText(0, "badhost_maxHappyPingTime 99999");
        Cbuf_AddText(0, "badhost_minTotalClientsForHappyTest 99999");
        Cbuf_AddText(0, "bandwidthtest_enable 0");
    }
    void doFFATeamFix()
    {
        if (variables::bFFATeamFix)
        {
            for (int i = 0; i < 18; i++)
            {
                *reinterpret_cast<int *>(0x1B1139C - 0x80 + (0x366C * i)) = 0x00;
            }
        }
    }
    void handleHotkeys()
    {
        if (GetAsyncKeyState(VK_F2) & 1) // F2
        {
            Cbuf_AddText(0, reinterpret_cast<const char *>(0x00AB2D88));
        }
        if (GetAsyncKeyState(VK_F3) & 1) // F3
        {
            functions::doForceHost();
        }
        if (GetAsyncKeyState(VK_F4) & 1) // F4
        {
            functions::ChangeGamemode();
            OpenMenu(0, "popup_gamesetup");
            Cbuf_AddText(0, "xblive_privatematch 1");
        }
        if (GetAsyncKeyState(VK_F5) & 1) // F5
        {
            functions::ChangeGamemode();
            functions::doMaxPlayers(variables::iMaxPlayers);
            functions::doStartMatch();
            functions::doBalanceTeams();
        }
        if (GetAsyncKeyState(88) & 1) // Key: X
        {
            variables::bNoClip = !variables::bNoClip;
            if (variables::bNoClip)
            {
                *reinterpret_cast<int *>(0x1B114D4 + (getHostId() * 0x366C)) = 0x01;
            }
            if (!variables::bNoClip)
            {
                *reinterpret_cast<int *>(0x1B114D4 + (getHostId() * 0x366C)) = 0x00;
            }
        }
    }
    void sendViewModel()
    {
        SetDvarFloat(mGunX, variables::fcg_gun_x);
        SetDvarFloat(mGunY, variables::fcg_gun_y);
        SetDvarFloat(mGunZ, variables::fcg_gun_z);
    }
    void sendOpenMenu(const char *menu)
    {
        OpenMenu(0, menu);
    }
    void sendElevatorsToggle()
    {
        //const char elevatorsDepatch[] = {144, 144};
        //const char elevatorsOriginal[] = {74, 42};
        // NOP techinally too large for char which max is -128 to 127, so use signed char instead
        const char elevatorsDepatch[] = {(char)144, (char)144};
        const char elevatorsOriginal[] = {(char)74, (char)42};
        if (variables::bElevators)
        {
            WriteBytes((LPVOID)0x00471329, elevatorsDepatch, sizeof(elevatorsDepatch));
        }
        else
        {
            WriteBytes((LPVOID)0x00471329, elevatorsOriginal, sizeof(elevatorsOriginal));
        }
    }
    void sendBouncesToggle()
    {
        //const char bounceDepatch[] = {144, 144};
        //const char bounceOriginal[] = {117, 20};
        const char bounceDepatch[] = {(char)144, (char)144};
        const char bounceOriginal[] = {(char)117, (char)20};
        if (variables::bBounces)
        {
            WriteBytes((LPVOID)0x004736E2, bounceDepatch, sizeof(bounceDepatch));
        }
        else
        {
            WriteBytes((LPVOID)0x004736E2, bounceOriginal, sizeof(bounceOriginal));
        }
    }

    char *getPlayerName(int client)
    {
        return reinterpret_cast<char*>(0x99786C + (client * 0x52C)); // thanks josh xo
        //return (char *)(0x99786C + (client * 0x52C)); // thanks josh xo
    }
    /*
    char* getPlayerName(int client)
    {
        char* name = (char*)(0x99786C + client * 0x52C);
        if (*name) return name;
        static char buf[12] = "AAAAAAAAAAA";
        for (int i = 0; i < 11; i++) buf[i] = 33 + rand() % 94;
        return buf;
    }
    */
    void sendCustomPort()
    {
        SetDvarInt(mCustomPort, variables::customPort);
    }

    void doIronSight()
    {
        BYTE bytes1[2] = {0x00, 0x00};
        BYTE bytes2[1] = {0x00};
        BYTE bytes3[2] = {0x3E, 0x16};
        BYTE bytes4[1] = {0x40};

        if (variables::bIronSightInter)
        {
            *(float *)0x06399684 = 1.0f;
            *(float *)0x0639971C = 1.125f;
            *(float *)0x0639C43C = 0.4f;
            memcpy((void *)0x2516392D, bytes1, 2);
            memcpy((void *)0x251639AD, bytes1, 2);
            memcpy((void *)0x2516396D, bytes1, 2);
            memcpy((void *)0x251639ED, bytes1, 2);
            memcpy((void *)0x25162F1F, bytes2, 1);
            strcpy((char *)0x33CB8FEC, "Intervention IRON Sight");
        }
        else
        {
            *(float *)0x06399684 = 0.0f;
            *(float *)0x0639971C = 0.0f;
            *(float *)0x0639C43C = 0.65f;
            memcpy((void *)0x2516392D, bytes3, 2);
            memcpy((void *)0x251639AD, bytes3, 2);
            memcpy((void *)0x2516396D, bytes3, 2);
            memcpy((void *)0x251639ED, bytes3, 2);
            memcpy((void *)0x25162F1F, bytes4, 1);
            strcpy((char *)0x33CB8FEC, "Intervention ACOG Sight");
        }
    }

    void writeSensitivity(float sens)
    {
        // writeMemory(0x063832DC, &sens, sizeof(float)); // I am not sure why this doesn't work
        std::string cmd = "sensitivity " + std::to_string(sens) + ";";
        Cbuf_AddText(0, cmd.c_str());
    }

    float readSensitivity()
    {
        float val = *reinterpret_cast<float *>(0x063832DC);
        // std::cout << "[Sensitivity] Read: " << val << std::endl;
        return val;
    }

    void menuUITweaks()
    {
        // main menu tweaks
        strcpy((char *)0x33BD7AF4, "^1d^7ismay's ^1degen^7 tool"); // ITnet
        strcpy((char *)0x33BD80C0, "^2FIND GAME");                 // Find game
        strcpy((char *)0x33BD8519, "^1PRIVATE SESH");              // private match
        strcpy((char *)0x33BD8A99, "^3CREATE A CLASS");            // create a class
        strcpy((char *)0x33BD9BE0, "^4STREAKS/CALLSIGNS");         // killstreaks
        strcpy((char *)0x33BDA69E, "^5BARRACKS OBAMA");            // barracks
        strcpy((char *)0x33BDAFE1, "^6INVITE PEEPS");              // invite

        strcpy((char *)0x33BE3F80, "^0PLAYLISTS"); // playlists

        strcpy((char *)0x33C0759C, "^2START");    // start game
        strcpy((char *)0x33C079A5, "^1SETTINGS"); // settings

        // title iron lungs
        strcpy((char *)0x33CBD9E6, "dismay >");
    }

}
