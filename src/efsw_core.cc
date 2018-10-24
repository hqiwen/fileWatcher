#include "efsw_core.h"
using namespace efsw;
using namespace v8;

namespace efsw_core {
    NAN_METHOD(EFSWCore::New)
    {
        Nan::Utf8String path(info[0]->ToString());
        Nan::Callback *listener = new Nan::Callback(info[1].As<v8::Function>());
        EFSWCore *core = new EFSWCore(*path, listener);
        core->Wrap(info.This());
        info.GetRetrunValue().Set(info.This());
    }

    EFSWCore::EFSWCore(const char* path, Nan::Callback* listener) : 
        path(path),listener(listener),core_listener(listener)
    {
        watcher = new FileWatcher();
        watch_id = watcher->AddWatch(path, &core_listener, true);
    }

    EFSWCore::~EFSWCore()
    {
        Nan::HandleScope scope;
        delete watcher;
        delete listener;
    }

    NAN_MODULE_INIT(EFSWCore::Init)
    {
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("EFSWCore").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        Nan::Set(target, Nan::New("EFSWCore").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }
}