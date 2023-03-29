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
			if (this->hModule == NULL) {
				core->LogError("Fail load Module " + name);
				return;
			}
			typedef bool (*FuncModuleMain)(ICore*);
			FuncModuleMain moduleMain = (FuncModuleMain)::GetProcAddress((HMODULE)this->hModule, "altMain");
			if (moduleMain != NULL) {
				bool hasError = (*moduleMain)((ICore*)core);
			}
			else core->LogError("Error Load function" + name);
		};

		const std::string& GetType() const {
			return type;
		};

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

