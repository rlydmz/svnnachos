#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }

static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }

SynchConsole::SynchConsole(const char *in, const char *out)
{
readAvail = new Semaphore("read avail", 0);
writeDone = new Semaphore("write done", 0);
console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, 0);
}

SynchConsole::~SynchConsole()
{
delete console;
delete writeDone;
delete readAvail;
}

void SynchConsole::SynchPutChar(int ch)
{
  console->PutChar (ch);
  writeDone->P ();
}

int SynchConsole::SynchGetChar()
{
  readAvail->P ();
  return console->GetChar ();
} 

void SynchConsole::SynchPutString(const char s[])
{
  if(s != NULL){
    int i = 0;
    while(s[i] != '\0'){
      SynchPutChar(s[i]); 
      i++;
    }
  }
  else{
    fprintf(stderr, "Chaine vide");
  }
}

void SynchConsole::SynchGetString(char *s, int n)
{
// ...
}

int SynchConsole::copyStringFromMachine(int from, char *to, unsigned size){
  int tmp = 0;
  for(unsigned i=0; i<size; i++){
    machine->ReadMem(from+i, 1, &tmp); 
    if((char)tmp != '\0'){
      to[i] = (char)tmp;
    } 
    else{
      to[i] = '\0';
      return i+1;
    } 
  }
  to[size-1] = '\0';
  return size;
}


#endif // CHANGED
