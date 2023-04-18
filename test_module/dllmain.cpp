// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <iostream>
#include <unordered_set>
#include <SDK.h>
#include <version/version.h>
#define MODULE_TYPE "test"
#include <fstream>
#include <sstream>
class TestResourceImpl : public alt::IResource::Impl {
public:
    TestResourceImpl() = default;
    void OnTick() {
        
        //std::cout << "TestResourceImpl tick" << std::endl;
    };
};


class TestScriptRuntime : public alt::IScriptRuntime {
public:
    TestScriptRuntime() = default;
    std::unordered_set<TestResourceImpl*> resources;
    void OnTick() override {
        //std::cout << "TestScriptRuntime tick" << std::endl;
    };

    void DestroyImpl(alt::IResource::Impl* impl) override
    {
        auto res = static_cast<TestResourceImpl*>(impl);
        resources.erase(res);
        delete res;
    }

    void OnDispose() override {
        delete this;
    }

    alt::IResource::Impl* CreateImpl(alt::IResource* resource)
    {
        auto res = new TestResourceImpl();
        resources.insert(res);
        alt::ICore::Instance().LogWarning("TestResourceImpl tick", resource);
        alt::ICore::Instance().LogDebug("TestResourceImpl tick", resource);
        alt::ICore::Instance().LogError("TestResourceImpl tick", resource);
        alt::ICore::Instance().LogInfo("TestResourceImpl tick", resource);

        return res;
    }

    static TestScriptRuntime& Instance()
    {
        static TestScriptRuntime _Instance;
        return _Instance;
    }
};


EXPORT bool altMain(alt::ICore* server) {
        //std::cout << __FILE__ << std::endl;
        alt::ICore::SetInstance(server);
        auto& runtime = TestScriptRuntime::Instance();

        alt::ICore::Instance().RegisterScriptRuntime(MODULE_TYPE, &runtime);
        
        //TestResourceImpl::
        //core::ICore::Instance().Resolve()
        //core::ILocalStorage* storage = core::ICore::Instance().GetLocalStorage();
        //storage->Set("test", "sadas");
        //std::cout << storage->Get("test") << std::endl;
        //std::cout << storage->Get("test1") << std::endl;
        //storage->Save();
        //std::cout << core::ICore::Instance().GetVersion() << std::endl;
        return true;

    }


EXPORT const char* GetSDKHash()
{
    return ALT_SDK_VERSION;
}


