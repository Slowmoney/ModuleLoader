// ClientCore.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"
#include "ClientCoreFactory.h"

ClientCoreFactory* clientCoreFactory = new ClientCoreFactory();

EXPORT int coreMain(std::vector<std::string>* args)
{
    std::cout << "coreMain client: " << std::to_string(args->size()) << std::endl;
    clientCoreFactory->Start();
    
    return 0;
}

EXPORT int Stop() {
    clientCoreFactory->Stop();
    return 0;
}

EXPORT uint32_t OnServerConnected(uint32_t clientId) {
    clientCoreFactory->OnConnected(clientId);
    return 0;
}

EXPORT void OnTick() {
    if (clientCoreFactory->core) {
        clientCoreFactory->OnTick();
    }
}