#ifndef _ENTRY_H_
#define _ENTRY_H_
#include "nan.h"
#include "efsw_core.h"
namespace efsw_core {
    NAN_MODULE_INIT(Init)
    {
        EFSWCore::Init(target);
    }
    NAN_METHOD(core, Init);
}
#endif