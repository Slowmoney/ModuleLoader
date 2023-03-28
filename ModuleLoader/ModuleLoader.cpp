// ModuleLoader.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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

			typedef void (*FuncModuleMain)(core::Core*);
			typedef const char* (*FuncGetType)();
			HINSTANCE hModule = ::LoadLibraryA(fullModuleName.c_str());
			if (hModule != NULL)
			{

				//FuncGetType GetType = (FuncGetType)::GetProcAddress((HMODULE)hModule, "GetType");
				//if (GetType == NULL) {
				//	std::cout << "Error Load Type" << std::endl;
				//	return;
				//}
				//std::string type(GetType());
				//auto it = modules->find(type);
				//if (it != modules->end()) {
				//	std::cout << "error resources has " << type << std::endl;
				//	return;
				//};

				//std::cout << GetType() << " => Load dll type" << std::endl;





				FuncModuleMain moduleMain = (FuncModuleMain)::GetProcAddress((HMODULE)hModule, "altMain");
				if (moduleMain != NULL) {
					Module* module = new Module((ICore*)core, fullModuleName, name);
					modules->insert({ name, module });
					std::cout << "AddModule " << name << " = " << std::endl;
				}
				else std::cout << "Error Load function" << std::endl;
				::FreeLibrary(hModule);
			}
			else std::cout << "error load Dll " << name << std::endl;
		}

		void LoadModules() {
			try
			{
				std::string path = getExecutableDir() + modulesFolder;
				std::cout << "Modules " << path << std::endl;
				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					auto ext = entry.path().extension();
					auto name = entry.path().filename().replace_extension();
					if (ext != L".dll") continue;
					std::cout << entry.path() << std::endl;

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
				//Resource resource(core);
				auto name = entry.path().filename().string();
				std::string path = getExecutableDir() + resourcesFolder + name;
				auto package = new core::Package(path+"/", core::IPackage::Mode::READ);
				auto config = LoadResourceConfig(package->ReadConfig());

				auto type = config->Get("type")->AsString();
				auto main = config->Get("main")->AsString();
				
				auto info = IResource::CreationInfo{ type, name, main, (IPackage*)package };

				//Module* module = core->GetModuleByType(type);
				//module->AddResource(info);

				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					core::IPackage::File* file = package->OpenFile(entry.path().filename().string());
					std::string src(package->GetFileSize(file), '\0');
					package->ReadFile(file, src.data(), src.size());
					package->CloseFile(file);
					std::cout << "cfg= " << src << std::endl;
					//std::cout << entry.path() << std::endl;
					//auto ext = entry.path().extension();
					//if (ext == L".toml") {
					//	std::ifstream file(entry.path());
					//	if (file.is_open()) {
					//		std::string content;
					//		std::string line;
					//		while (std::getline(file, line)) {
					//			// using printf() in all tests for consistency
					//			//printf("%s", line.c_str());
					//			content.append(line+'\n');
					//		}
					//		Config::Value::ValuePtr cfg = LoadResourceConfig(content);
					//		auto str = Config::Util::ConvertValueToString(cfg);
					//		std::cout << "cfg= " << str << std::endl;
					//		printf("%s", content.c_str());
					//		file.close();
					//	}
					//}
					
				}

				
				
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
