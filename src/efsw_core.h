#ifndef _EFSW_CORE_H_
#define _EFSW_CORE_H_
#include <string>
#include <nan.h>
#include "./deps/efsw/include/efsw/efsw.hpp"
#include "efsw_core_listener.h"

namespace efsw_core
{
class EFSWCore : public Nan::ObjectWrap
{
  public:
    static NAN_MODULE_INIT(Init);

  private:
    explicit EFSWCore(const char *path, Nan::Callback *listener);
    ~EFSWCore();
    static NAN_METHOD(New);

  private:
    std::string path;
    Nan::Callback *listener;
    efsw::FileWacher *watcher;
    efsw::WatchID watch_id;
    EFSWCoreListener core_listener;
};
}; // namespace efsw_core
#endif