#pragma once

#include <SDK.h>

class BoilerplateResource;
class BoilerplateRuntime : public core::IScriptRuntime
{
    std::unordered_map<core::IResource*, BoilerplateResource*> resources;

public:
    BoilerplateRuntime();
    core::IResource::Impl* CreateImpl(core::IResource* resource) override;
    void DestroyImpl(core::IResource::Impl* impl) override;
    void OnTick() override;

    BoilerplateResource* GetResource(core::IResource* resource)
    {
        if(resources.count(resource) == 0) return nullptr;
        return resources.at(resource);
    }

    // Gets the current runtime instance or creates one if not exists
    static BoilerplateRuntime& Instance()
    {
        static BoilerplateRuntime _instance;
        return _instance;
    }
};
