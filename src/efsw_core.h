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
    efsw::WatchID Start();
    void Stop();
    static NAN_METHOD(New);
    static NAN_METHOD(Start);
    static NAN_METHOD(Stop);

  private:
    std::string path;
    Nan::Callback *listener;
    efsw::FileWacher *watcher;
    efsw::WatchId watch_id;
    EFSWCoreListener core_listener;
};
}; // namespace efsw_core
#endif