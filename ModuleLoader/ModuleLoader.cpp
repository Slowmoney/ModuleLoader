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
namespace alt {
	class CoreFactory {
	public:
		Core* core = new Core();
		std::unordered_map<std::string, Module*>* modules = new std::unordered_map<std::string, Module*>();
		void Create(std::string name, std::string fullModulePath) {
			std::string moduleName(name.begin(), name.end());
			std::string fullModuleName = modulesFolder + moduleName;
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
				std::string path = getExecutableDir() + modulesFolder;
				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					auto isDir = entry.is_directory();
					if (isDir) {
						auto name = entry.path().filename().replace_extension().string();
						auto ext = ".dll";
						std::string folder = entry.path().string();
						std::string full = folder + "/" + entry.path().filename().string() + ext;
						
						std::filesystem::directory_entry dir(full);
						
						auto exist = std::filesystem::exists(dir);
						
						std::wstring sd(folder.begin(), folder.end());
						

						//::AddDllDirectory(sd.c_str());
						auto error = GetLastError();
						wchar_t ctext[256];
						FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
							NULL,
							error,
							0,
							ctext,
							sizeof(ctext),
							NULL);
						std::wstring errorStr(ctext);
						std::wcout << L"error:" << errorStr.c_str() << L"sd: " << sd << std::endl;
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
			std::string path = getExecutableDir() + resourcesFolder;
			for (const auto& entry : std::filesystem::directory_iterator(path)) {
				auto name = entry.path().filename().string();
				std::string path = getExecutableDir() + resourcesFolder + name;
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
		std::string modulesFolder = "modules/";
		std::string resourcesFolder = "resources/";

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
