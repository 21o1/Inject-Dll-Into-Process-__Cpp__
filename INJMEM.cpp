
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

using namespace std;

DWORD GetPrName(const char* pName){
    DWORD PID = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 PrEnt;
        PrEnt.dwSize = sizeof(PrEnt);
        if (Process32First(hSnap, &PrEnt)) {
            do {
                if (!_stricmp(PrEnt.szExeFile, pName)) {
                    PID = PrEnt.th32ParentProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &PrEnt));
        }
    }
    CloseHandle(hSnap);
    return PID;
}
int main()
{
    const char* pName = "csgo.exe";
    const char* path = "helloworld";
    
    cout << "Path: " << path << "\nProcess Name: " << pName << endl;
    cout << "injcting the dll ...." << endl;
    bool hr = true;
    const char* stages[5] = { "Checking The ProcId","Alloc The mem, injecting the dll","Done[+]" };
    int n = 0;
    int na = 0;
    DWORD PID = 0;
    while (hr == true) {

        cout << "loading(" << stages[n] << ")\r";
        if (PID && n == 0) {
            n += 1;
            na = 0;
        }
        else {
            PID = GetPrName(pName);
            Sleep(35);
            if (na == 200) {
                cout << "\nTime Out Check The Process Name(You Can Use Task Manager To Find Process Name)";
                return 0;
            }


            HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, PID);


            if (hProc && hProc != INVALID_HANDLE_VALUE && n == 1) {
                void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                WriteProcessMemory(hProc, loc, path, strlen(path) + 1, 0);
                HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
                if (hThread) {
                    CloseHandle(hThread);
                }
                n += 1;
                

            }
            if (hProc && n == 2) {
                
                CloseHandle(hProc);
                hr = false;

            }
             
            na += 1;

        }

    }
    system("cls");
    cout << "\n\n\n\n\t\t\t\tCheck The Process Now...!{Injecting Done}\n\n\n";
}
