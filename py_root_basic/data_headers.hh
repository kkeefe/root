#ifndef __DATA_HEADERS_H_
#define __DATA_HEADERS_H_

#include <cstdio>
#include "TObject.h"

// basic structure example -- try to use methods and assign values
// within pyRoot?
class extype {
    private:

    public:
        // some constructors
        extype() = default;
        extype(Int_t a1, Int_t b1) : a(a1), b(b1){};
        ~extype(){};

        // some member functions
        Int_t get_a();
        Int_t get_b();
        void mult(const int& f);

        // some variables
        Int_t a;
        Int_t b;

        void cprint();

        // ClassDef(extype, 1);
};

void extype::mult(const int& f)
{
    a *= f;
    b *= f;
}

void extype::cprint()
{
    printf("a: %i\t b: %i\n", a, b);
}

Int_t extype::get_a()
{
    return this->a;
}

Int_t extype::get_b()
{
    return this->b;
}

#endif // __DATA_HEADERS_H_

#if !defined(__CLING__)
ClassImp(extype);
#endif
