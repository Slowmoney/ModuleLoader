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

std::string getExecutablePath() {
	char rawPathName[MAX_PATH];
	GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
	return std::string(rawPathName);
}
std::string getExecutableDir() {
	std::string executablePath = getExecutablePath();
	std::filesystem::path path(executablePath.c_str());
	return path.remove_filename().generic_string();
}
namespace core {
	class CoreFactory {
	public:
		core::Core* core = new core::Core();
		std::unordered_map<std::string, core::Module*>* modules = new std::unordered_map<std::string, core::Module*>();
		void Create(std::string name) {
			std::string moduleName(name.begin(), name.end());
			std::string fullModuleName = modulesFolder + moduleName;
			AddModule(name, fullModuleName);
			return;
		}

		void AddModule(std::string name, std::string fullModuleName) {

			Module* module = new Module((ICore*)core, fullModuleName, name);
			modules->insert({ name, module });
		}

		void LoadModules() {
			try
			{
				std::string path = getExecutableDir() + modulesFolder;
				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					auto ext = entry.path().extension();
					auto name = entry.path().filename().replace_extension();
					if (ext != L".dll") continue;
					core->LogInfo("Load module: " + entry.path().string());
					Create(name.string());
				}
					
			}
			catch (const std::exception& e)
			{
				std::cout << "error load Modules " << e.what() << std::endl;
			}
			
		}

		void LoadResources() {
			std::string path = getExecutableDir() + resourcesFolder;
			for (const auto& entry : std::filesystem::directory_iterator(path)) {
				auto name = entry.path().filename().string();
				std::string path = getExecutableDir() + resourcesFolder + name;
				auto package = new core::Package(path+"/", core::IPackage::Mode::READ);
				auto config = LoadResourceConfig(package->ReadConfig());
				auto type = config->Get("type")->AsString();
				auto main = config->Get("main")->AsString();
				auto info = IResource::CreationInfo{ type, name, main, (IPackage*)package };
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
		std::string modulesFolder = "modules/";
		std::string resourcesFolder = "resources/";

	};
}

core::CoreFactory* coreFactory = new core::CoreFactory();


void my_handler(int s) {
	printf("Caught signal %d\n", s);
	coreFactory->dispose();
	exit(0);

}

int main(int argc, char** argv)
{
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
