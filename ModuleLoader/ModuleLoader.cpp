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
#include "DlcScriptRuntime.h"

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
			if (isStarted) modules->insert({ name, module });

			//delete module;
		}

		void LoadModules() {
			//auto& dlcRuntime = DlcScriptRuntime::Instance();
			//core->RegisterScriptRuntime("dlc", &dlcRuntime);
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

			std::vector<std::string> resPath = core->GetResourcePaths();

			for (const auto& entry : resources->AsList()) {
				auto name = entry->AsString();
				LoadResource(name, resPath);
			}
		}

		std::string FindResources(std::string name, std::vector<std::string> resPath) {
			for (const auto& entry : resPath) {
				auto package = new Package(entry + name + "\\", alt::IPackage::Mode::READ);
				auto configStr = package->ReadConfig();
				if (configStr.size()) return entry + name;
			}
			return "";
		}

		bool LoadResource(std::string name, std::vector<std::string> resPath, std::string parent = "") {
			auto resource = core->GetResource(name);
			if (resource) {
				core->LogInfo("resource loaded: " + name + parent);
				return true;
			}
			std::string path = FindResources(name, resPath);
			if (!path.size()) {
				core->LogDebug("not find resource: " + name);
				return false;
			}
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
			core->AddResource(info, path);
			return true;
		}

		void AddExtraResFolder(std::string path) {
			std::cout << "AddExtraResFolder: " << path << std::endl;
			core->resourcesFolders.push_back(path);
		}


		Config::Value::ValuePtr LoadResourceConfig(const std::string& cfgString) {
			std::string errr = "";
			auto cfg = Config::ConfigBase<TomlConfig>().Parse(cfgString, errr);
			if (errr.size()) {
				std::cout << errr;
			}
			return cfg;
		}

		void LoadPedModels() {
			std::string dataPath = core->GetDataPath();

			std::ifstream file;
			file.open(dataPath + "pedmodels.bin", std::ios::binary);


			auto _file = (std::ofstream*)&file;
			if (!_file->is_open()) return;
			_file->seekp(0, std::ios::end);
			uint64_t fileSize = _file->tellp();
			_file->seekp(0, std::ios::beg);



			uint16_t pattern = 0;
			file.read((char*)&pattern, sizeof(pattern));

			uint16_t version = 0;
			file.read((char*)&version, sizeof(version));

			int i = 0;
			for (uint64_t current = _file->tellp(); current < fileSize; current = _file->tellp())
			{
				uint32_t hash = 0;
				file.read((char*)&hash, sizeof(alt::PedModelInfo::hash));


				uint8_t nameSize = 0;
				file.read((char*)&nameSize, sizeof(nameSize));
				auto buffSize = nameSize + 1;
				char* name = new char[buffSize];
				name[buffSize] = 0;
				file.read(name, nameSize * sizeof(char));

				//std::cout << "PED = " << name << i++ << std::endl;

				uint8_t typeSize = 0;
				file.read((char*)&typeSize, sizeof(typeSize));
				buffSize = typeSize + 1;
				char* type = new char[buffSize];
				type[buffSize] = 0;
				file.read(type, typeSize * sizeof(char));



				uint8_t dlcNameSize = 0;
				file.read((char*)&dlcNameSize, sizeof(dlcNameSize));
				buffSize = dlcNameSize + 1;
				char* dlcName = new char[buffSize];
				dlcName[buffSize] = 0;
				file.read(dlcName, dlcNameSize * sizeof(char));



				uint8_t defaultUnarmedWeaponSize = 0;
				file.read((char*)&defaultUnarmedWeaponSize, sizeof(defaultUnarmedWeaponSize));
				buffSize = defaultUnarmedWeaponSize + 1;
				char* defaultUnarmedWeapon = new char[buffSize];
				defaultUnarmedWeapon[buffSize] = 0;
				file.read(defaultUnarmedWeapon, defaultUnarmedWeaponSize * sizeof(char));



				uint8_t movementClipSetSize = 0;
				file.read((char*)&movementClipSetSize, sizeof(movementClipSetSize));
				buffSize = movementClipSetSize + 1;
				char* movementClipSet = new char[buffSize];
				movementClipSet[buffSize] = 0;
				file.read(movementClipSet, movementClipSetSize * sizeof(char));


				uint16_t bonesCount = 0;
				file.read((char*)&bonesCount, sizeof(bonesCount));

				alt::PedModelInfo ped;
				ped.hash = hash;
				ped.name = name;
				ped.type = type;
				ped.dlcName = dlcName;
				ped.defaultUnarmedWeapon = defaultUnarmedWeapon;
				ped.movementClipSet = movementClipSet;
				for (size_t i = 0; i < bonesCount; i++)
				{
					//alt::BoneInfo* bone = new alt::BoneInfo();
					uint16_t id = 0;
					uint16_t index = 0;
					std::string name;

					file.read((char*)&id, sizeof(alt::BoneInfo::id));
					file.read((char*)&index, sizeof(alt::BoneInfo::index));
					uint8_t nameSize = 0;
					file.read((char*)&nameSize, sizeof(nameSize));
					auto buffSize = nameSize + 1;
					char* name2 = new char[buffSize];
					name2[buffSize] = 0;
					//name.reserve(nameSize);
					file.read(name2, nameSize * sizeof(char));
					ped.bones.push_back({ id, index, std::string(name2) });
					//uint64_t size = file.tellg();
					//std::cout << "BONE: " << name << i << " | " << std::hex << (int)nameSize << std::dec << std::endl;
				}
				core->pedModels.insert({ hash, ped });
			}



			//file.read((char*)&ped.name, sizeof(ped.hash));
			core->LogDebug("LOAD PEDS: " + std::to_string(core->pedModels.size()));
			file.close();
		}

		void LoadVehicleModels() {
			std::string dataPath = core->GetDataPath();

			std::ifstream file;
			file.open(dataPath + "vehmodels.bin", std::ios::binary);


			auto _file = (std::ofstream*)&file;
			if (!_file->is_open()) return;
			_file->seekp(0, std::ios::end);
			uint64_t fileSize = _file->tellp();
			_file->seekp(0, std::ios::beg);



			uint16_t pattern = 0;
			file.read((char*)&pattern, sizeof(pattern));

			uint16_t version = 0;
			file.read((char*)&version, sizeof(version));

			int i = 0;
			for (uint64_t current = _file->tellp(); current < fileSize; current = _file->tellp())
			{
				uint32_t hash = 0;
				file.read((char*)&hash, sizeof(uint32_t));

				uint8_t titleSize = 0;
				file.read((char*)&titleSize, sizeof(titleSize));
				auto buffSize = titleSize + 1;
				char* title = new char[buffSize];
				title[buffSize] = 0;
				file.read(title, titleSize * sizeof(char));

				uint8_t modelType = 0;
				file.read((char*)&modelType, sizeof(modelType));

				uint8_t wheelsCount = 0;
				file.read((char*)&wheelsCount, sizeof(wheelsCount));

				bool hasArmoredWindows = 0;
				file.read((char*)&hasArmoredWindows, sizeof(hasArmoredWindows));

				uint8_t primaryColor = 0;
				file.read((char*)&primaryColor, sizeof(primaryColor));

				uint8_t secondaryColor = 0;
				file.read((char*)&secondaryColor, sizeof(secondaryColor));

				uint8_t pearlColor = 0;
				file.read((char*)&pearlColor, sizeof(pearlColor));

				uint8_t wheelsColor = 0;
				file.read((char*)&wheelsColor, sizeof(wheelsColor));


				uint8_t interiorColor = 0;
				file.read((char*)&interiorColor, sizeof(interiorColor));

				uint8_t dashboardColor = 0;
				file.read((char*)&dashboardColor, sizeof(dashboardColor));

				uint16_t modkits[2];
				file.read((char*)&modkits, sizeof(modkits));

				uint16_t extras = 0;
				file.read((char*)&extras, sizeof(extras));

				uint16_t defaultExtras = 0;
				file.read((char*)&defaultExtras, sizeof(defaultExtras));

				bool hasAutoAttachTrailer = 0;
				file.read((char*)&hasAutoAttachTrailer, sizeof(hasAutoAttachTrailer));

				VehicleModelInfo model;
				model.title = title;
				model.modelType = static_cast<VehicleModelInfo::Type>(modelType);
				model.wheelsCount = wheelsCount;
				model.hasArmoredWindows = hasArmoredWindows;
				model.primaryColor = primaryColor;
				model.secondaryColor = secondaryColor;
				model.pearlColor = pearlColor;
				model.wheelsColor = wheelsColor;
				model.interiorColor = interiorColor;
				model.dashboardColor = dashboardColor;

				memcpy(model.modkits, modkits, sizeof(modkits));
				model.extras = extras;
				model.defaultExtras = defaultExtras;
				model.hasAutoAttachTrailer = hasAutoAttachTrailer;

				uint8_t bonesCount = 0;
				file.read((char*)&bonesCount, sizeof(bonesCount));

				for (size_t i = 0; i < bonesCount; i++)
				{
					//alt::BoneInfo* bone = new alt::BoneInfo();
					uint16_t id = 0;
					uint16_t index = 0;
					std::string name;

					file.read((char*)&id, sizeof(alt::BoneInfo::id));
					file.read((char*)&index, sizeof(alt::BoneInfo::index));
					uint8_t nameSize = 0;
					file.read((char*)&nameSize, sizeof(nameSize));
					auto buffSize = nameSize + 1;
					char* name2 = new char[buffSize];
					name2[buffSize] = 0;
					//name.reserve(nameSize);
					file.read(name2, nameSize * sizeof(char));
					model.bones.push_back({ id, index, std::string(name2) });
					//uint64_t size = file.tellg();
					//std::cout << "BONE: " << name << i << " | " << std::hex << (int)nameSize << std::dec << std::endl;
				}
				core->vehicleModels.insert({ hash, model });
			}
			core->LogDebug("LOAD VEHICLE MODELS : " + std::to_string(core->vehicleModels.size()));
			file.close();
		}

		void LoadClothesData() {
			std::string dataPath = core->GetDataPath();

			std::ifstream file;
			file.open(dataPath + "clothes.bin", std::ios::binary);


			auto _file = (std::ofstream*)&file;
			if (!_file->is_open()) return;
			_file->seekp(0, std::ios::end);
			uint64_t fileSize = _file->tellp();
			_file->seekp(0, std::ios::beg);



			uint16_t pattern = 0;
			file.read((char*)&pattern, sizeof(pattern));

			if (pattern != 'LC') return;

			uint16_t version = 0;
			file.read((char*)&version, sizeof(version));
			if (version != 2) return;

			int clothCount = 0;
			int propCount = 0;
			for (uint64_t current = _file->tellp(); current < fileSize; current = _file->tellp())
			{
				uint8_t one = 0;
				file.read((char*)&one, sizeof(one));

				uint32_t size = 0;
				file.read((char*)&size, sizeof(size));

				//std::cout << "one: 0x" << std::hex << (static_cast<int>(one)) << std::endl;
				//std::cout << "size: 0x" << std::hex << (static_cast<int>(size)) << std::endl;

				for (size_t i = 0; i < size; i++)
				{
					uint32_t dlchash = 0;
					file.read((char*)&dlchash, sizeof(dlchash));
					//std::cout << "dlchash: 0x" << std::hex << (static_cast<int>(dlchash)) << std::endl;

					
					for (size_t cid = 0; cid < 12; cid++)
					{
						uint32_t count = 0;
						file.read((char*)&count, sizeof(count));

						if (!count) continue;
						for (size_t i = 0; i < count; i++)
						{
							uint16_t drawableId = 0;
							file.read((char*)&drawableId, sizeof(drawableId));
							uint8_t maxTextures = 0;
							file.read((char*)&maxTextures, sizeof(maxTextures));
							uint8_t* textures = new uint8_t[maxTextures];
							file.read((char*)textures, maxTextures * sizeof(uint8_t));

							//std::cout << "drawableId " << std::dec << (static_cast<int>(drawableId)) << " | 0x" << std::hex << (static_cast<int>(maxTextures & 0xFF)) << " | cid: 0x" << std::hex << (static_cast<int>(cid & 0xFF)) << std::endl;
							

							for (size_t i = 0; i < maxTextures; i++)
							{
								clothCount++;
								core->AddCloth((uint8_t)cid, drawableId, textures[i], dlchash);
							}
						}
					}

					for (size_t cid = 0; cid < 8; cid++)
					{
						uint32_t count = 0;
						file.read((char*)&count, sizeof(count));
						if (!count) continue;
						for (size_t i = 0; i < count; i++)
						{
							uint16_t drawableId = 0;
							file.read((char*)&drawableId, sizeof(drawableId));
							uint8_t maxTextures = 0;
							file.read((char*)&maxTextures, sizeof(maxTextures));
							uint8_t* textures = new uint8_t[maxTextures];
							file.read((char*)textures, maxTextures * sizeof(uint8_t));
							//std::cout << "drawableId " << std::dec << (static_cast<int>(drawableId)) << " | 0x" << std::hex << (static_cast<int>(maxTextures & 0xFF)) << " | cid: 0x" << std::hex << (static_cast<int>(cid & 0xFF)) << std::endl;
							

							for (size_t i = 0; i < maxTextures; i++)
							{
								propCount++;
								core->AddProp((uint8_t)cid, drawableId, textures[i], dlchash);
							}

						}
					}
				}
			}
			file.close();

			core->LogDebug("LOAD CLOTHES INFO : " + std::to_string(clothCount));
			core->LogDebug("LOAD PROPS INFO : " + std::to_string(propCount));
		}

		void LoadData() {
			LoadClothesData();
			LoadPedModels();
			LoadVehicleModels();
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

	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg == "--extra-res-folder") {
			i++;
			std::string path = argv[i];

			coreFactory->AddExtraResFolder(path);
		}
	}
	coreFactory->LoadData();
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
