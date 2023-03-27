#pragma once

namespace core {

    class IScriptRuntime;
    class ICore
    {
    public:
        virtual std::string GetVersion() const = 0;
        virtual ILocalStorage* GetLocalStorage() = 0;

        virtual void OnTick() = 0;

        virtual bool RegisterScriptRuntime(const std::string& resourceType, IScriptRuntime* runtime) = 0;

        virtual IResource* GetResource(const std::string& name) = 0;

        virtual core::IPackage::PathInfo Resolve(IResource* resource, const std::string& path, const std::string& currentModulePath) const = 0;

        static ICore& Instance()
        {
            return *_instance();
        }
        static void SetInstance(ICore* server) { _instance() = server; }

    protected:
        virtual ~ICore() = default;

    private:
        static ICore*& _instance()
        {
            static ICore* instance = nullptr;
            return instance;
        }
    };
}