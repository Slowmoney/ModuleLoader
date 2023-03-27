// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <iostream>
#include <unordered_set>
#include <SDK.h>

class TwoResourceImpl : public core::IResource::Impl {
public:
    TwoResourceImpl() = default;
    void OnTick() {
        //std::cout << "TwoResourceImpl tick" << std::endl;
    };
};


class TwoScriptRuntime : public core::IScriptRuntime {
public:
    TwoScriptRuntime() = default;
    std::unordered_set<TwoResourceImpl*> resources;
    void OnTick() override {
        //std::cout << "TwoScriptRuntime tick" << std::endl;
    };

    core::IResource::Impl* CreateImpl(core::IResource* resource)
    {
        auto res = new TwoResourceImpl();
        resources.insert(res);
        return res;
    }

    void DestroyImpl(core::IResource::Impl* impl) override
    {
        auto res = static_cast<TwoResourceImpl*>(impl);
        resources.erase(res);
        delete res;
    }

    void OnDispose() override {
        delete this;
    }

    static TwoScriptRuntime& Instance()
    {
        static TwoScriptRuntime _Instance;
        return _Instance;
    }
};

EXPORT bool moduleMain(core::ICore* server) {
    std::cout << __FILE__ << std::endl;
    core::ICore::SetInstance(server);
    core::ICore::SetInstance(server);
    auto& runtime = TwoScriptRuntime::Instance();

    core::ICore::Instance().RegisterScriptRuntime("two", &runtime);
    return true;
}


