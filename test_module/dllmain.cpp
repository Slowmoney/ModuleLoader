﻿// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <iostream>
#include <unordered_set>
#include <SDK.h>
#define MODULE_TYPE "test"

class TestResourceImpl : public core::IResource::Impl {
public:
    TestResourceImpl() = default;
    void OnTick() {
        //std::cout << "TestResourceImpl tick" << std::endl;
    };
};


class TestScriptRuntime : public core::IScriptRuntime {
public:
    TestScriptRuntime() = default;
    std::unordered_set<TestResourceImpl*> resources;
    void OnTick() override {
        //std::cout << "TestScriptRuntime tick" << std::endl;
    };

    void DestroyImpl(core::IResource::Impl* impl) override
    {
        auto res = static_cast<TestResourceImpl*>(impl);
        resources.erase(res);
        delete res;
    }

    void OnDispose() override {
        delete this;
    }

    core::IResource::Impl* CreateImpl(core::IResource* resource)
    {
        auto res = new TestResourceImpl();
        resources.insert(res);
        return res;
    }

    static TestScriptRuntime& Instance()
    {
        static TestScriptRuntime _Instance;
        return _Instance;
    }
};


EXPORT bool altMain(core::ICore* server) {
        std::cout << __FILE__ << std::endl;
        core::ICore::SetInstance(server);
        auto& runtime = TestScriptRuntime::Instance();

        core::ICore::Instance().RegisterScriptRuntime(MODULE_TYPE, &runtime);
        //std::cout << core::ICore::Instance().GetResource("test_module")->GetType() << std::endl;
        
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


EXPORT const char* GetType()
{
    return MODULE_TYPE;
}