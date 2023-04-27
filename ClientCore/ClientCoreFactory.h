#pragma once
#include "ClientCore.h"


class ClientCoreFactory {
public:
	ClientCore* core = new ClientCore();

	void LoadModules() {

	}

	void Start() {
		
	}

	void OnConnected(uint32_t clientId) {
		this->core->CreateLocalPlayer(clientId);
	}

	void OnTick() {
		auto c = core;
		if (!c) return;
		//std::cout << "client on tick" << std::endl;
		c->OnTick();
	}

	void Stop() {
		delete core;
		core = NULL;
	}


};