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

    int index = currentThread->space->threadStack->Find();
    if(index != -1){
        printf("Thread créé à l'index %d\n", index);
        currentThread->SetIndex(index);
        Thread *t = new Thread("newThread");
        struct schmurtz *argStart = (struct schmurtz*)malloc(sizeof(struct schmurtz));
        argStart->f = f;
        argStart->arg = arg;   
        currentThread->space->IncNbThreads();
        t->Start(StartUserThread, argStart);
        return 0;
    }
    else{
        printf("Impossible de créer le thread\n");
        return -1;
    }
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
    
    currentThread->space->RestoreState();
    currentThread->space->DecNbThreads();
    if(currentThread->space->GetNbThreads() == 0){
        interrupt->Halt();
    }
    currentThread->space->threadStack->Clear(currentThread->GetIndex());
    currentThread->Finish();

    return 0;
}