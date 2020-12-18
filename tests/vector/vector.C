#include "vector.decl.h"

#include <Charap.hpp>

std::vector<ck::future<std::vector<double>>> garbage::futures{};

class Main : public CBase_Main
{
public:
    Main(CkArgMsg* msg)
    {
        thisProxy.finish();
    }

    void finish()
    {
        aum::Vector<double> A{1000000, 1};
        aum::Vector<double> B{1000000, 2};
        aum::Vector<double> D{1000000, 3};

        aum::Vector<double> C = A;

        Scalar<double> a = dot(A.transpose(), B);

        A = B - D;

        C = A + B + C;

        aum::Vector<double> E = A.transpose() * B;

        CkStartQD(CkCallback::ckExit);
    }
};

#include "vector.def.h"
