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


namespace core {
	class CoreFactory {
	public:
		core::Core* core = new core::Core();
		core::Core* Create(core::IResource::CreationInfo info) {
			std::wstring folder = L"modules\\";
			std::wstring moduleName(info.name.begin(), info.name.end());
			
			std::wstring fullModuleName = folder + moduleName;

			HINSTANCE hModule = NULL;
			typedef void (*FuncModuleMain)(core::Core*);
			FuncModuleMain me = NULL;
			hModule = ::LoadLibrary(fullModuleName.c_str());
			if (hModule != NULL)
			{
				auto it = core->resources->find(info.type);
				if (it != core->resources->end()) {
					std::cout << "error resources has " << info.type << std::endl;
					return NULL;
				};
				core->AddResource(info, hModule);
				me = (FuncModuleMain)::GetProcAddress((HMODULE)hModule, "moduleMain");
				if (me != NULL)
				{
					(*me)(core);
					
				}
				else std::cout << "Error Load function" << std::endl;
				
			}
			else std::cout << "error load Dll " << moduleName.c_str() << std::endl;
			return core;
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

core::CoreFactory* coreFactory = new core::CoreFactory();


void my_handler(int s) {
	printf("Caught signal %d\n", s);
	coreFactory->dispose();
	exit(0);

}

int main()
{
	signal(SIGINT, my_handler);
	auto testModule = coreFactory->Create(core::IResource::CreationInfo{"test", "test_module", "atest_module"});
	auto twoModule = coreFactory->Create(core::IResource::CreationInfo{ "two", "two_module", "atwo_module" });

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
