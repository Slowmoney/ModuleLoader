#pragma once
#include <SDK.h>
#include <wtypes.h>
#include <iostream>
namespace core {
	class Resource : IResource {
	public:
		Resource(CreationInfo info) : info(info) {};

		virtual Impl* GetImpl() const override {
			return impl;
		};
		virtual bool IsStarted() const override {
			return started;
		}
		virtual const std::string& GetType() const override {
			return info.type;
		};
		virtual const std::string& GetName() const override { return info.name; };
		virtual const std::string& GetPath() const override { return info.name; };
		virtual const std::string& GetMain() const override { return info.main; };
		bool started = false;
		Impl* impl = NULL;
		IScriptRuntime* runtime = NULL;
		CreationInfo info;
		Config::Value::ValuePtr config;
	protected:
		virtual ~Resource() override {
			std::cout << "~Resource" << std::endl;
			runtime->OnDispose();
			delete runtime;
			delete impl;
		};
	};
};
