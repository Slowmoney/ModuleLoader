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
				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					auto isDir = entry.is_directory();
					if (isDir) {
						auto name = entry.path().filename().replace_extension().string();
						auto ext = ".dll";
						std::string folder = entry.path().string();
						std::string full = folder + "/" + entry.path().filename().string() + ext;
						
						std::filesystem::directory_entry dir(full);
						
						auto exist = std::filesystem::exists(dir);
					
						

						//::AddDllDirectory(sd.c_str());
						auto error = GetLastError();
						char ctext[256];
						FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
							NULL,
							error,
							0,
							ctext,
							sizeof(ctext),
							NULL);
						std::cout << "error:" << ctext << "folder: " << folder << std::endl;
						//LoadModule(dir);



						LoadModule(dir);
					}
					else
					{
						auto ext = entry.path().extension().string();
						if (ext != ".dll") continue;
						LoadModule(entry);
					}


					
					
				}
					
			}
			catch (const std::exception& e)
			{
				std::cout << "error load Modules " << e.what() << std::endl;
			}
			
		}

		void LoadModule(std::filesystem::directory_entry entry) {
			
			auto fullPath = std::filesystem::path(entry).lexically_normal();
			auto ext = fullPath.extension().string();
			auto name = fullPath.filename().replace_extension().string();
			auto path = fullPath.string();
			core->LogInfo("Load module: " + path);
			Create(name, path);
		}

		void LoadResources() {

			auto resources = core->config->Get("resources");
			if (!resources->IsList()) return;


			std::string resPath = core->GetResourcePath();
			//
			//auto list = resources->AsList();
			//
			//for (const auto& entry : list) {
			//	auto name = entry->AsString();
			//	std::string path = resPath + name;
			//	auto package = new Package(path + "\\", alt::IPackage::Mode::READ);
			//	auto configStr = package->ReadConfig();
			//	if (!configStr.size()) {
			//		std::cout << "no config: " << name << std::endl;
			//		continue;
			//	}
			//	auto config = LoadResourceConfig(configStr);
			//	
			//	auto type = config->Get("type")->AsString();
			//	auto main = config->Get("main")->AsString();
			//	auto info = alt::IResource::CreationInfo{ type, name, main, (IPackage*)package };
			//	core->AddResource(info);
			//}

			for (const auto& entry : std::filesystem::directory_iterator(resPath)) {
				auto name = entry.path().filename().string();
				std::string path = resPath + name;
				auto package = new Package(path+"/", alt::IPackage::Mode::READ);
				auto config = LoadResourceConfig(package->ReadConfig());
				auto type = config->Get("type")->AsString();
				auto main = config->Get("main")->AsString();
				auto info = alt::IResource::CreationInfo{ type, name, main, (IPackage*)package };
				core->AddResource(info);
			}
		}


		Config::Value::ValuePtr LoadResourceConfig(const std::string &cfgString){
			std::string errr = "";
			auto cfg = Config::ConfigBase<TomlConfig>().Parse(cfgString, errr);
			return cfg;
		}

		void OnTick() {
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
