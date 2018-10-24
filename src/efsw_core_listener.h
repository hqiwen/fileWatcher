#ifndef __EFSW_CORE_LISTENER_H__
#define _EFSW_CORE_LISTENER_H_
#include <string>
#include <nan.h>
#include "./deps/efsw/include/efsw/efsw.hpp"

namespace efsw_core
{
#define Watch watch
#define AddWatch addWatch
#define HandleFileAction handleFileAction
#define GetLastErrorLog getLastErrorLog
#define WatchId WatchID

class EFSWCoreListener : public efsw::FileWatcherListener
{
  public:
    EFSWCoreListener(Nan::Callback *listener);
    ~EFSWCoreListener();

    void HandleFileAction(
        efsw::WatchId,
        const std::string &dir,
        const std::string &filename,
        efsw::Action action,
        std::string old_filename);

  private:
    Nan::Callback *listener;
};
} // namespace efsw_core
#endif
