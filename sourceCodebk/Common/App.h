#ifndef _COMMON_APP_H_
#define _COMMON_APP_H_
#include <stdlib.h>

class App
{
public:
    static void ExitNormal(){exit(0);}
    static void ExitWithCoredump(){abort();}
};

#endif
