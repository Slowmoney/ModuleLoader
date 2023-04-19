#define ALT_SERVER_API
#include <windows.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <memory>
#include <SDK.h>
#include <signal.h>
#include "LocalStorage.h"
#include "Resource.h"
#include "Core.h"
#include "Package.h"
#include <filesystem>
#include <Shlwapi.h>
#include "TomlConfig.h"
#include "Module.h"

#ifdef _WIN32
#include <windows.h>

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

void activateVirtualTerminal()
{
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode;
	GetConsoleMode(handleOut, &consoleMode);
	consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
	SetConsoleMode(handleOut, consoleMode);
}
#endif

namespace alt {
	class CoreFactory {
	public:
		Core* core = new Core();
		std::unordered_map<std::string, Module*>* modules = new std::unordered_map<std::string, Module*>();
		void Create(std::string name, std::string fullModulePath) {
			std::string moduleName(name.begin(), name.end());
			std::string fullModuleName = core->GetModulesPath() + moduleName;
			AddModule(name, fullModulePath);
			return;
		}

		void AddModule(std::string name, std::string fullModuleName) {

			Module* module = new Module((ICore*)core, fullModuleName, name);
			bool isStarted = module->Start();
			if(isStarted) modules->insert({ name, module });

			//delete module;
		}

		void LoadModules() {
			try
			{
				std::string path = core->GetModulesPath();
				auto modules = core->GetServerConfig()->Get("modules");
				if (!modules->IsList()) {
					std::cerr << "INVALID SEARVER CONFIG";
					return;
				}

				for (const auto& entry : modules->AsList()) {
					std::string name = entry->AsString();
					auto package = alt::Package(path, alt::IPackage::Mode::READ);
					auto hasDir = package.FileExists(name);
					if (hasDir) {
						name = name + "\\" + name + ".dll";
					}
					else {
						name = name + ".dll";
					}
					LoadModule(path + "\\" + name);
					auto error = GetLastError();
					if (error) {
						char ctext[256];
						FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
							NULL,
							error,
							0,
							ctext,
							sizeof(ctext),
							NULL);
						core->LogError(std::string(ctext) + ": " + name);
						//std::cout << "error:" << ctext << "folder: " << path + "\\" + name << std::endl;
						return;
					}
				}
					
			}
			catch (const std::exception& e)
			{
				std::cout << "error load Modules " << e.what() << std::endl;
			}
			
		}

		void LoadModule(std::string entry) {
			
			auto fullPath = std::filesystem::path(entry).lexically_normal();
			auto ext = fullPath.extension().string();
			auto name = fullPath.filename().replace_extension().string();
			auto path = fullPath.string();
			core->LogInfo("Loading module: " + path);
			Create(name, path);
			core->LogInfo("Load module: " + path);
		}

		void LoadResources() {

			auto resources = core->config->Get("resources");
			if (!resources->IsList()) return;

			std::string resPath = core->GetResourcePath();

			for (const auto& entry : resources->AsList()) {
				auto name = entry->AsString();
				LoadResource(name, resPath);
			}
		}

		bool LoadResource(std::string name, std::string resPath, std::string parent = "") {
			auto resource = core->GetResource(name);
			if (resource) {
				core->LogInfo("resource loaded: " + name + parent);
				return true;
			}
			std::string path = resPath + name;
			auto package = new Package(path + "\\", alt::IPackage::Mode::READ);
			auto configStr = package->ReadConfig();
			if (!configStr.size()) {
				std::cout << "no config: " << name << std::endl;
				return false;
			}
			auto config = LoadResourceConfig(configStr);
			auto deps = config->Get("deps")->AsList();
			for (const auto& entry : deps) {
				auto resName = entry->AsString();
				if (parent == resName) {
					core->LogError("circular deps: " + name + " from: " + parent);
					continue;
				}
				LoadResource(resName, resPath, name);
			}

			auto type = config->Get("type")->AsString();
			auto main = config->Get("main")->AsString();
			auto info = alt::IResource::CreationInfo{ type, name, main, (IPackage*)package };
			core->AddResource(info);
			return true;
		}


		Config::Value::ValuePtr LoadResourceConfig(const std::string &cfgString){
			std::string errr = "";
			auto cfg = Config::ConfigBase<TomlConfig>().Parse(cfgString, errr);
			if (errr.size()) {
				std::cout << errr;
			}
			return cfg;
		}

		void OnTick() {
			//auto error = GetLastError();
			//char ctext[256];
			//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
			//	NULL,
			//	error,
			//	0,
			//	ctext,
			//	sizeof(ctext),
			//	NULL);
			//std::cout << ctext;
			if (!core) return;
			core->OnTick();
		}

		void dispose() {
			delete core;
			core = NULL;
		}
	};
}

alt::CoreFactory* coreFactory = new alt::CoreFactory();

void my_handler(int s) {
	printf("Caught signal %d\n", s);
	coreFactory->dispose();
	exit(0);

}

int main(int argc, char** argv)
{
#ifdef _WIN32
	activateVirtualTerminal();
#endif
	setlocale(LC_ALL, "Russian");
	signal(SIGINT, my_handler);
	coreFactory->LoadModules();
	coreFactory->LoadResources();



	while (true)
	{
		coreFactory->OnTick();
		//coreFactory->dispose();
	}
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
