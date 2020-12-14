#include "vector.decl.h"

#include <Charap.hpp>

std::vector<ck::future<std::vector<double>>> garbage::futures {};

class Main : public CBase_Main
{
public:
    Main(CkArgMsg* msg)
    {
        thisProxy.finish();
    }

    void finish()
    {
        Vector A {1000000, 1};
        Vector B {1000000, 2};
        Vector D {1000000, 3};

        Vector C = A;

        C = A + B + C;

        A = B - D;

        CkStartQD(CkCallback::ckExit);
    }
};

#include "vector.def.h"