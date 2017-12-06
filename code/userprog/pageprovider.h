#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "copyright.h"
#include "filesys.h"
#include "bitmap.h"

class PageProvider:dontcopythis{
    public:
        PageProvider(int numpPages);
        ~PageProvider();
        int GetEmptyPage();
        void ReleasePage(int numpage);
        int NumAvailPage();
    private:
        BitMap *map;
};

#endif // PAGEPROVIDER_H