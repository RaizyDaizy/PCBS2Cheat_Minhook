// dllmain.cpp : Defines the entry point for the DLL application.
#include "includes.hpp"

uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
uintptr_t GameAssembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll"); //Address of Current GameAssembly :D
uintptr_t unlockedpcbay = 0xB3E050; //Address of Unlocked PC Bay :D
uintptr_t addcash = 0xB2F4E0; //AddCash :D
uintptr_t CollectCash_addr = 0xB32AE0;
uintptr_t setbusname_address = 0xB386F0;
uintptr_t updatebusinessname_address = 0xB3CB80;
void CreateConsole() 
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    SetConsoleTitleA("PCBS2CheatMinhook by RaizyDaizy"); //Console Title :D
    printf("Welcome to my Public Cheat for PCBS2... This Cheat made by RaizyDaizy#2897");
}

void MinHookEnable() 
{
    MH_Initialize();
}

bool(__fastcall* UnlockedPCBay_o)(DWORD*, DWORD*); //Method of Current PCBay :D

bool __stdcall UnlockedPCBay_hack(DWORD* __this, DWORD* method) 
{
    printf("\nUnlockedPCBay Function has been Called!!!");

    return true;
}

void MinhookUnlockPCBay()
{
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + unlockedpcbay), &UnlockedPCBay_hack, (LPVOID*)&UnlockedPCBay_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + unlockedpcbay));
}

void(__fastcall* AddCash_o)(DWORD*, int32_t, bool, int32_t, DWORD*); //Method of AddCash :D

void __stdcall AddCash_hack(DWORD* __this, int32_t cash, bool force, int32_t category, DWORD* method) 
{
    cash = 25000000;
    category = 7;
    force = true; //Force it's Instant Add Money :D
    printf("\nSuccessfully Called AddCash Function!!!");

    return AddCash_o(__this, cash, force, category, method); //Original Code :D
}

void MinhookAddCash() 
{
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + addcash), &AddCash_hack, (LPVOID*)&AddCash_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + addcash));
}

void(__fastcall* CollectCash_o)(DWORD*, int32_t, DWORD*);

void __stdcall CollectCash_h(DWORD* __this, int32_t amount, DWORD* method) {
    amount = 500000;

    return CollectCash_o(__this, amount, method);
}

void MinhookCollectCashCheat() 
{
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + CollectCash_addr), &CollectCash_h, (LPVOID*)&CollectCash_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + CollectCash_addr));
}

void(__fastcall* UpdateBusinessName_o)(DWORD*, DWORD*);

void __stdcall UpdateBusinessName_h(DWORD* __this, DWORD* method) 
{
    return true;
}

void(__fastcall* SetBusinessName_o)(DWORD*, const char*, DWORD*);

void __stdcall SetBusinessName_h(DWORD* __this, const char* name, DWORD* method)
{
    name = "ZA WARUDO!!!";
    return SetBusinessName_o(__this, name, method);
}

void MH_SetAndUpdBusinessName() 
{
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + setbusname_address), &SetBusinessName_h, (LPVOID*)&SetBusinessName_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + setbusname_address));
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + updatebusinessname_address), &SetBusinessName_h, (LPVOID*)&SetBusinessName_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + updatebusinessname_address));
    printf("\nBusiness Name was Updated Succesfully!!!");
}
DWORD WINAPI MainCheat(HMODULE m) 
{
    if (FindWindowA(0, "PCBS2")) 
    {
        CreateConsole();
        MinHookEnable();
        MinhookAddCash();
        MinhookUnlockPCBay();
        MinhookCollectCashCheat();
        if (GetAsyncKeyState(VK_DELETE)) //Updating Business Name
        {
            MH_SetAndUpdBusinessName();
        }
        return TRUE;
    }
    else 
    {
        CreateConsole();
        printf("Window is Not Founded Succesfull");
        Sleep(1200);
        FreeLibraryAndExitThread(m, 334);
        return FALSE;
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainCheat, 0, 0, 0); //Creating Thread :D
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

