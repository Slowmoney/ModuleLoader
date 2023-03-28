#pragma once
#include <wtypes.h>
#include <SDK.h>

namespace core {
	class Module
	{
	public:
		std::unordered_map<std::string, core::Resource*>* resources = new std::unordered_map<std::string, core::Resource*>();
		Module(ICore* core, std::string fullModuleName, std::string name) : core(core), name(name) {
			this->hModule = ::LoadLibraryA(fullModuleName.c_str());

			//typedef bool (*FuncModuleMain)(ICore*);
			//
			//FuncModuleMain moduleMain = (FuncModuleMain)::GetProcAddress((HMODULE)this->hModule, "altMain");
			//if (moduleMain != NULL) {
			//
			//	bool hasError = (*moduleMain)((ICore*)core);
			//
			//	
			//	std::cout << "hasError " << hasError << std::endl;
			//}
			//else std::cout << "Error Load function" << std::endl;
		};

		const std::string& GetType() const {
			return type;
		};



		IResource* AddResource(IResource::CreationInfo info) {
			
		
			Resource* resource = new Resource(info);
			resources->insert({ info.name, resource });
			std::cout << "AddResource " << info.name << std::endl;
			return (IResource*)resource;
		}

		HINSTANCE hModule;
		std::string name;
		std::string type;
		ICore* core;

	protected:
		~Module() {
			std::cout << "~Module" << std::endl;
			::FreeLibrary(hModule);
			delete hModule;
		};
	};
}

