#include <windows.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <memory>
#include <signal.h>
#include <Shlwapi.h>

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


class Core {
public:
	Core(std::string name): name(name){}

	void LoadLib() {
		this->hModule = ::LoadLibraryEx(name.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	}

	void Start(std::vector<std::string>* args) {
		this->LoadLib();
		typedef int (*FuncCoreMain)(std::vector<std::string>*);
		FuncCoreMain coreMain = (FuncCoreMain)::GetProcAddress(this->hModule, "coreMain");
		this->hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)coreMain, args, 0, NULL);
	}

	HMODULE hModule;
	std::string name;
	HANDLE hThread;

	size_t Wait() {
		return WaitForSingleObject(hThread, INFINITE);
	}

	~Core() {
		CloseHandle(hThread);
	}
};

HMODULE LoadLib(const char * name) {
	auto hModule = ::LoadLibraryEx(name, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	return hModule;
}

//ServerCoreFactory* serverCoreFactory = new ServerCoreFactory();
//ClientCoreFactory* clientCoreFactory = new ClientCoreFactory();


void my_handler(int s) {
	printf("Caught signal %d\n", s);
	//serverCoreFactory->dispose();
	exit(0);

}

int main(int argc, char** argv)
{

#ifdef _WIN32
	activateVirtualTerminal();
#endif
	setlocale(LC_ALL, "Russian");
	signal(SIGINT, my_handler);
	std::vector<std::string>* args = new std::vector<std::string>();
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		args->push_back(arg);
	}

	Core clientCore("ClientCore.dll");
	clientCore.Start(args);

	Core serverCore("ServerCore.dll");
	serverCore.Start(args);


	serverCore.Wait();
	clientCore.Wait();
}

