#include <cstdint>
#include "../memory/memoryWork.h"
#include <detours.h>
#include <sstream>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

static string pointerToString(PVOID* ppPointer)
{
    stringstream ss;
    ss << *ppPointer;
    ss << ", ";
    ss << ppPointer;
    string str = ss.str();
    return str;
}

LONG memory::detourAttach(PVOID* ppPointer, PVOID pDetour)
{
    if (ppPointer == NULL || *ppPointer == NULL)
    {
        return NULL;
    }

    return DetourAttach(ppPointer, pDetour);
}

LONG memory::detourDetach(PVOID* ppPointer, PVOID pDetour)
{
    if (ppPointer == NULL || *ppPointer == NULL)
    {
        return NULL;
    }

    return DetourDetach(ppPointer, pDetour);
}

LONG memory::detourAttach(PVOID* ppPointer, PVOID pDetour, std::string function)
{
    if (ppPointer == NULL || *ppPointer == NULL)
    {
        LOG_ALWAYS(RELEASE, "detourAttach(" + function + " --> NULL pointer)");
        return NULL;
    }

    LOG_ALWAYS(RELEASE, "detourAttach(" + function + " --> " + pointerToString(ppPointer) + ")");
    return DetourAttach(ppPointer, pDetour);
}

LONG memory::detourDetach(PVOID* ppPointer, PVOID pDetour, std::string function)
{
    if (ppPointer == NULL || *ppPointer == NULL)
    {
        LOG_ALWAYS(RELEASE, "detourDetach(" + function + " --> NULL pointer)");
        return NULL;
    }

    LOG_ALWAYS(RELEASE, "detourDetach(" + function + " --> " + pointerToString(ppPointer) + ")");
    return DetourDetach(ppPointer, pDetour);
}

uint32_t memory::Read(uint32_t address)
{
    uint32_t result = 0;
    ReadProcessMemory(GetCurrentProcess(), (BYTE*)address, &result, sizeof(uint32_t), 0);
    return result;
}

uint32_t memory::ReadF(uint32_t address)
{
    uint32_t result = 0;
    ReadProcessMemory(GetCurrentProcess(), (BYTE*)address, &result, sizeof(float), 0);
    return result;
}

void memory::Write(void* ptr, DWORD to, size_t size)
{
    HANDLE h = GetCurrentProcess();
    DWORD oldMemProtect = 0;
    VirtualProtectEx(h, (LPVOID)to, size, PAGE_EXECUTE_READWRITE, &oldMemProtect);
    WriteProcessMemory(h, (LPVOID)to, ptr, size, NULL);
    VirtualProtectEx(h, (LPVOID)to, size, oldMemProtect, &oldMemProtect);
    CloseHandle(h);
}

static void test_read_write(uint32_t RomeTW_ALX_exe)
{
    uint32_t charorogin = RomeTW_ALX_exe + 0x011F7F50;
    //  MessageBoxA(nullptr, to_string(Read(charorogin)).c_str(), "charorogin", MB_OK);

    uint32_t charbase = memory::Read(memory::Read(memory::Read(memory::Read(memory::Read(memory::Read(charorogin) + 0x0) + 0x0) + 0x4) + 0xC) + 0x4) + 0x78;
    //  MessageBoxA(nullptr, to_string(Read(charbase)).c_str(), "charbase_1", MB_OK);

    uint32_t command = memory::Read(charbase) + 0x2C;
    MessageBoxA(nullptr, std::to_string(memory::Read(command)).c_str(), "command", MB_OK);


    uint32_t write = 10;
    bool tr = WriteProcessMemory(GetCurrentProcess(), (BYTE*)command, &write, sizeof(uint32_t), 0);
}

template <typename  data>
void Read_2(DWORD from, data* p, size_t size = 4)
{
    memset(p, 0, size);
    memcpy(p, (LPVOID)from, size);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

















