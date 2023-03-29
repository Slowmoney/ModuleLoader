#pragma once
#include <wtypes.h>
#include <SDK.h>
#include <version/version.h>
#include <winerror.h>

namespace alt {
	class Module
	{
	public:
		Module(ICore* core, std::string fullModuleName, std::string name) : core(core), name(name), fullModuleName(fullModuleName){};

		bool LoadLib() {
			std::wstring folder(fullModuleName.begin(), fullModuleName.end());
			this->hModule = ::LoadLibraryEx(folder.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
			if (this->hModule == NULL) {
				core->LogError("Fail load Module " + name + " => " + fullModuleName);
				return false;
			}
			return true;
		}

		bool CheckSDKHash() {
			typedef char* (*FuncModuleGetSDKHash)();
			FuncModuleGetSDKHash GetSDKHash = (FuncModuleGetSDKHash)::GetProcAddress((HMODULE)this->hModule, "GetSDKHash");
			if (GetSDKHash != NULL) {
				std::string hash((*GetSDKHash)());

				if (hash != ALT_SDK_VERSION) { 
					core->LogError("Fail CheckSDKHash " + name + "=>" + hash + " != " + ALT_SDK_VERSION);
					return false;
				}
			}
			else {
				return false;
			}
			return true;
		}

		bool StartLib() {
			typedef bool (*FuncModuleMain)(ICore*);
			FuncModuleMain moduleMain = (FuncModuleMain)::GetProcAddress((HMODULE)this->hModule, "altMain");
			if (moduleMain != NULL) {
				bool done = (*moduleMain)((ICore*)core);
				if (!done) {
					core->LogError("Fail StartLib " + name);
					return false;
				}
			}
			else return false;
			return true;
		}

		bool Start() {
			if (!LoadLib()) { 
				core->LogError("Fail LoadLib " + name);
				return false;
			}
			if (!CheckSDKHash()) { 
				core->LogError("Fail CheckSDKHash " + name);
				return false;
			}
			if (!StartLib()) { 
				core->LogError("Fail StartLib " + name);
				return false;
			}
			core->LogInfo("Module Start " + name);
			return true;
		}

		HINSTANCE hModule;
		std::string name;
		std::string fullModuleName;
		ICore* core;
		~Module() {
			std::cout << "~Module" << std::endl;
			::FreeLibrary(hModule);
			delete hModule;
		};
	};
}

