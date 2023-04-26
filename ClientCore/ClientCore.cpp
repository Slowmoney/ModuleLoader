// ClientCore.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"
#include "ClientCoreFactory.h"

ClientCoreFactory* clientCoreFactory = new ClientCoreFactory();

EXPORT int coreMain(std::vector<std::string>* args)
{
    std::cout << "coreMain client: " << std::to_string(args->size()) << std::endl;

    while(true){
        
    }
    return 0;
}
