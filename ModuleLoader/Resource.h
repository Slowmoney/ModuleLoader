#pragma once
#include <SDK.h>
#include <wtypes.h>
#include <iostream>
#include <deps/ConfigBase.h>
namespace alt {
	class Resource : IResource {
	public:
		Resource(CreationInfo info, std::string path) : info(info), path(path){};

		virtual IScriptRuntime* GetRuntime() const override {
			return runtime;
		}

		virtual Impl* GetImpl() const override {
			return impl;
		};
		virtual bool IsStarted() const override {
			return started;
		}
		virtual const std::string& GetType() const override {
			return info.type;
		};
		virtual const std::string& GetName() const override { 
			return info.name; 
		};
		virtual const std::string& GetPath() const override { 
			return path + info.name;
		};
		virtual const std::string& GetMain() const override { 
			return info.main; 
		};

		virtual IPackage* GetPackage() const override {
			return info.pkg;
		}

		virtual MValueDict GetExports() const override {
			return this->exports;
		}

		virtual void SetExports(MValueDict exports) override {
			auto size = exports.As<IMValueDict>();
			std::cout << size->GetSize() << std::endl;
			this->exports = exports;
		}

		virtual const Array<std::string> GetDependencies() const override {
			return Array<std::string>();
		}
		virtual const Array<std::string> GetDependants() const override {
			return Array<std::string>();
		}

		virtual const Array<Permission> GetRequiredPermissions() const override{
			return Array<Permission>();
		}
		virtual const Array<Permission> GetOptionalPermissions() const override {
			return Array<Permission>();
		}

		virtual std::string GetClientType() const override {
			return "";
		}
		virtual std::string GetClientMain() const override {
			return "";
		}
		virtual const std::vector<std::string>& GetClientFiles() const override {
			return std::vector < std::string>();
		}
		virtual Config::Value::ValuePtr GetConfig() const override {
			return config;
		}
		virtual std::set<std::string> GetMatchedFiles(const std::vector<std::string>& patterns) override {
			return std::set<std::string>();
		}

		bool Start() {
			try
			{
				started = impl->Start();
				return started;
			}
			catch (...)
			{
				std::cout << "Error start resource " << info.name << std::endl;
			}
			return false;
			
		}

		Impl* impl = NULL;
		IScriptRuntime* runtime = NULL;
		CreationInfo info;
		Config::Value::ValuePtr config;
		MValueDict exports;
		std::string path;
	protected:
		bool started = false;
		virtual ~Resource() override {
			std::cout << "~Resource" << std::endl;
			runtime->OnDispose();
			delete runtime;
			delete impl;
		};
	};
};
