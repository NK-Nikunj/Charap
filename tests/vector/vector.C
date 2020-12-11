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

        A.check('A');
        A.check('A');
        // B.check('B');
        Vector C = A + B;

        CkWaitQD();

        D.check('D');
        D.check('D');
        C.check('C');
        C.check('C');
        A.check('A');
        B.check('B');

        A = B;

        // C.print_vector();

        // Quiscence detection
        CkStartQD(CkCallback::ckExit);
    }
};

#include "vector.def.h"