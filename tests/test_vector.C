#include "test_vector.decl.h"

#include <Charap.hpp>

class Main : public CBase_Main
{
public:
    Main(CkArgMsg* msg)
    {
        Vector A = std::vector<double>({1, 2, 3});
        Vector B = {2, 4, 6};
        Vector D = {3, 6, 9};

        Vector C = A + B + D;

        C.print_vector();

        // Quiscence detection
        CkStartQD(CkCallback::ckExit);
    }
};

#include "test_vector.def.h"