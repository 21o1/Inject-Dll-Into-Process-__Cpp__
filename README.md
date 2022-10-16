# Inject Dll Into Process (C++)
***So Sometimes to add some contents to game source without reach the main source and change it you have to inject the dll's to the procces in the memory while the process running so lets start with what is dll?.***   
## DLL
***Dynamic Linked Library(DLL) its a shareable file use for windows os , its like a library include func, codes the programs can use.***   
## FAQ
- **How this will be useful?**    
***For Hackers that thing will help a lot like adding sub-code to the main will be good especially in Game Hacking.***
- **How the dll will run after inject?**     
***well after injecting  the dll will auto run in the main memory.***    
- **Is The dll file will get the access to the main source?**    
***yea for sure the dll file will get the access to the source and this is a great point for game hacking.***   
## Source&Explain
***lets start with the includes so we need 2 lib***    
``#include <iostream>``             
``#include <TlHelp32.h>``    
      
***So Now Lets try to find the process id of the program which we will provide soon , so lets store the id as double word, ``DWORD`` so lets start( Read The Comments in the source,, AND I ATTACHED CPP INJ WITH THIS RESP U CAN CHECK IT ).***
```
#include <iostream>             
#include <TlHelp32.h>
DOWRD getProcessId(cont char* procname){
    DWORD PID =0; //lets set process id here to 0 to mk it possible to reach in next lines
    HANDLE hSn = CreateToolhelp32SnapShot(TH32CS_SNAPPROCESS, 0);//lets add our handle which will help us to find the process id in the memory
    if{hSn != INVALID_HANDLE_VALUE}{
        PROCESSENTRY32 PrEn;//so first we add if statment to check if our handle created then def id for our handle
        PrEnt.dwSize = sizeof(PrEn);//here we def the size of ent(jst to find the address)
        if(Process32First(hSn,&PrEnt)){
            do{
                if(!_stricmp(PrEn.szExeFile,procname)){
                    pid = PrEn.th32parentProcessID;//so we added if cond to check the first process which we created , then we started loop which will change the procces until reach the process we want (you will understand what i mean by reading the source)
                    break; //so what this lines will do , this lines will jst keep trying the running process until find process have the same name(procname which we will provide soon) after find the process will get the pid then store it
                }while(Process32Next(hSn,&PrEn));
            }
        }
    }
    CloseHandle(hSn);//to close the handle
    return pid;
}
int main(){
      const char* procname = "anything.exe";//so here we will provide the name of the program that we want to inj
      const char* path "C:\\\....";//the path of the dll file
      DWORD pid = 0;//def the pid again here to use it soon
      pid = getProcessId(procname);//give pid new value (the address of our program)
      HANDLE hPrc = OpenProcess(PROCESS_ALL_ACCESS,0,pid);//def handle and open our program process in the memory with full access (read,write,exec) 
      if(hprc && hprc != INVALID_HANDLE_VALUE){
            void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);//so we added if stat to check the handle then we start alloc memory to write in
            WriteProcessMemory(hPrc,loc,path,strlen(path)+1,0);//and yea we inj our dll here into the process 
            HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);//so here we start thread to load the dll or jst to mk the inj logical and useable
            if(hThread){
                 CloseHandle(hThread);
            }
      }
      if(hPrc){
            CloseHandle(hPrc);
      }
}
