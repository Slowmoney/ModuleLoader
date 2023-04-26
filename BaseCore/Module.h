#pragma once
#include <wtypes.h>
#include <libloaderapi.h>
#include <SDK.h>
#include <winerror.h>
#include <version/version.h>

DWORD WINAPI thread2(LPVOID t)
{
	std::cout << "thread2\n";
	try
	{
		alt::ICore* core = (alt::ICore*)t;
		std::cout << "Second thread\n";
		return 0;
	}
	catch (...)
	{
		std::cout << "THG+ASD\n";
	}
	return 0;
}

namespace alt {
	class Module
	{
	public:
		Module(ICore* core, std::string fullModuleName, std::string name) : core(core), name(name), fullModuleName(fullModuleName){};

		bool LoadLib() {
			this->hModule = ::LoadLibraryEx(fullModuleName.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
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
			LPTHREAD_START_ROUTINE moduleMain = (LPTHREAD_START_ROUTINE)::GetProcAddress((HMODULE)this->hModule, "altMain");
			if (moduleMain != NULL) {
				core->LogDebug("altMain " + name);
				//HANDLE hThread = CreateThread(NULL, 0, moduleMain, core, 0, NULL);

				//if (hThread == NULL)
				//{
				//	// Thread creation failed.
				//	// More details can be retrieved by calling GetLastError()
				//	core->LogError("Fail StartLib CreateThread" + name);
				//	return false;
				//}
				//WaitForSingleObject(hThread, INFINITE);
				//CloseHandle(hThread);
				bool done = (*moduleMain)((ICore*)core);
				auto error = GetLastError();
				char ctext[256];
				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					error,
					0,
					ctext,
					sizeof(ctext),
					NULL);
				std::cout << ctext;
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

