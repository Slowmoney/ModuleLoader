#pragma once
#include <SDK.h>
#include <wtypes.h>
#include <iostream>
#include <deps/ConfigBase.h>
namespace alt {
	class Resource : IResource {
	public:
		Resource(ICore* core,  CreationInfo info, std::string path) : core(core), info(info), path(path) {};

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
			return path;
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
			if (!exports || !this->exports) {
				std::cout << "SetExports: not exports = " << std::endl;
			}
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
			core->LogDebug("RUN UNIMPLEMENTED GetClientType");
			return "";
		}
		virtual std::string GetClientMain() const override {
			core->LogDebug("RUN UNIMPLEMENTED GetClientMain");
			return "";
		}
		virtual const std::vector<std::string>& GetClientFiles() const override {
			core->LogDebug("RUN UNIMPLEMENTED GetClientFiles");
			return std::vector < std::string>();
		}
		virtual Config::Value::ValuePtr GetConfig() const override {
			return config;
		}
		virtual std::set<std::string> GetMatchedFiles(const std::vector<std::string>& patterns) override {
			core->LogDebug("RUN UNIMPLEMENTED GetMatchedFiles");
			return std::set<std::string>();
		}

		bool Start() {
			try
			{
				std::cout << "Start resource " << info.name << std::endl;
				started = impl->Start();
				return started;
			}
			catch (...)
			{
				std::cout << "Error start resource " << info.name << std::endl;
			}
			return false;
			
		}

		ICore* core;
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
