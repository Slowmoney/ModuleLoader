#pragma once
#include <SDK.h>
#include <iostream>
#include <unordered_map>

namespace core {
	class Core : ICore {
	public:
		core::LocalStorage* localStorage = new core::LocalStorage();
		std::unordered_map<std::string, core::Resource*>* resources = new std::unordered_map<std::string, core::Resource*>();
		virtual std::string GetVersion() const override {
			return "CORE v2";
		};

		virtual core::ILocalStorage* GetLocalStorage() override {
			return localStorage;
		}

		virtual void OnTick() override {
			if (!started) return;
			for (auto it = resources->begin(); it != resources->end(); ++it) {
				try
				{
					if (!it->second->IsStarted()) return;
					it->second->runtime->OnTick();
					it->second->GetImpl()->OnTick();
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}

			}
		}

		virtual bool RegisterScriptRuntime(const std::string& resourceType, IScriptRuntime* runtime) override {
			//runtimes->insert({ resourceType, (core::ScriptRuntime*)runtime });
			std::cout << "RegisterScriptRuntim type: " << resourceType << std::endl;
			//IResource* resource = module->AddResource(IResource::CreationInfo{ resourceType, });
			//
			//
			//auto impl = runtime->CreateImpl(resource);
			//core::Resource* res1 = (core::Resource*)resource;
			//res1->impl = impl;
			//res1->runtime = runtime;
			//res1->started = true;
			return true;
		};

		void AddResource(IResource::CreationInfo info) {
			Resource* resource = new Resource(info);
			resources->insert({ info.name, resource });
			std::cout << "AddResource " << info.name << std::endl;
		}


		virtual IPackage::PathInfo Resolve(IResource* resource, const std::string& path, const std::string& currentModulePath) const override {
			IPackage* pkg1 = NULL;
			return IPackage::PathInfo{ pkg1, path, currentModulePath };
		}

		//Module* GetModuleByType(const std::string& resourceType) {
		//	auto map = *modules;
		//	for (const auto& [key, value] : map)
		//		if (value->GetType() == resourceType)
		//			return value;
		//	return NULL;
		//};



		virtual IResource* GetResource(const std::string& name) override {
			if (resources->find(name) != resources->end()) 
				return (IResource*)resources->at(name);
			return NULL;
		};

		void Stop() {
			started = false;
		}

		bool started = true;

		~Core() {
			std::cout << "~Core" << std::endl;
			resources->clear();
			delete localStorage;
		}
	};
}

