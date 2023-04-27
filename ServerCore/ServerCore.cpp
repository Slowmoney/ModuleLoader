// ServerCore.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"
#include "ServerCoreFactory.h"

ServerCoreFactory* serverCoreFactory = new ServerCoreFactory();

EXPORT int coreMain(std::vector<std::string>* args)
{
	std::cout << "coreMain server: " << std::to_string(args->size()) << std::endl;

	for (size_t i = 0; i < args->size(); i++)
	{
		std::string arg = args->at(i); 
		if (arg == "--extra-res-folder") {
			std::string path = args->at(i+1);
			serverCoreFactory->AddExtraResFolder(path);
		}
	}

	serverCoreFactory->Start();
	serverCoreFactory->LoadData();
	serverCoreFactory->LoadModules();
	serverCoreFactory->LoadResources();

	//while (serverCoreFactory->core) {
	//	serverCoreFactory->OnTick();
	//}
    return 0;
}

EXPORT int Stop() {
	serverCoreFactory->Stop();
	return 0;
}

EXPORT uint32_t OnClientConnect() {
	std::cout << "OnClientConnect: " << std::endl;
	return serverCoreFactory->OnClientConnect();
}

EXPORT void OnTick() {
	if (serverCoreFactory->core) {
		serverCoreFactory->OnTick();
	}
}