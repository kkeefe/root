// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME data_headers_rflx
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "data_headers.hh"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_data_headers_rflx_Impl() {
    static const char* headers[] = {
"0",
0
    };
    static const char* includePaths[] = {
"/Users/kevinkeefe/Documents/root_build/root-6.20.00-build/include/",
"/Users/kevinkeefe/Documents/root_basic/py_root_basic/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "data_headers_rflx dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "data_headers_rflx dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#ifndef __DATA_HEADERS_H_
#define __DATA_HEADERS_H_

#include <cstdio>
#include "TObject.h"

// basic structure example -- try to use methods and assign values
// within pyRoot?
class extype : public TObject {
    private:
        // some variables
        Int_t a;
        Int_t b;
    public:
        // some constructors
        extype() = default;
        extype(Int_t a1, Int_t b1) : a(a1), b(b1){};

        // some member functions
        Int_t get_a();
        Int_t get_b();

        void cprint();

        ClassDef(extype, 0);
};

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

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("data_headers_rflx",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_data_headers_rflx_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_data_headers_rflx_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_data_headers_rflx() {
  TriggerDictionaryInitialization_data_headers_rflx_Impl();
}
