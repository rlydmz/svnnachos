#include "copyright.h"
#include "system.h"
#include "userthread.h"
#include "thread.h"
#include "syscall.h"

typedef struct schmurtz schmurtz;
struct schmurtz
{
    int f;
    int arg;
};

int do_ThreadCreate(int f, int arg){

    Thread *t = new Thread("newThread");
    struct schmurtz *argStart = (struct schmurtz*)malloc(sizeof(struct schmurtz));
    argStart->f = f;
    argStart->arg = arg;   
    t->Start(StartUserThread, argStart);

    return 0;
}

void StartUserThread(void *arg){

    schmurtz *threadArgs = (schmurtz* )arg;

    int i;
    
        for (i = 0; i < NumTotalRegs; i++)
        machine->WriteRegister (i, 0);
    
        machine->WriteRegister (PCReg, threadArgs->f);

        machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);

        machine->WriteRegister (4, threadArgs->arg);

        machine->WriteRegister (StackReg, currentThread->space->AllocateUserStack());
        DEBUG ('a', "Initializing stack register to 0x%x\n",
            currentThread->space);
                
        machine->Run();

}

int do_ThreadExit(){
    currentThread->Finish();
    currentThread->space->RestoreState();

    return 0;
}

