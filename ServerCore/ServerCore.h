#pragma once
#include "BaseCore.h"
#include "Package.h"
#include "Module.h"
#include <filesystem>
#include "events/CServerStartedEvent.h"

std::string getExecutablePath() {
	char rawPathName[MAX_PATH];
	GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
	return std::string(rawPathName);
}


class ServerCore : public BaseCore
{
public:
	const std::string root = LoadRoot();
	const Config::Value::ValuePtr config = LoadConfig();
	std::unordered_map<uint32_t, alt::PedModelInfo> pedModels;
	std::unordered_map<uint32_t, alt::VehicleModelInfo> vehicleModels;
	std::unordered_map<uint32_t, BaseCore::ClothInfo> clothesInfo;
	std::unordered_map<uint32_t, BaseCore::PropInfo> propsInfo;
	std::unordered_map<uint32_t, BaseCore::VehicleModKitInfo> modKitInfos;

	std::vector<std::string> resourcesFolders = std::vector<std::string>({ "./resources" });
	std::string modulesFolder = "modules\\";
	std::string dataFolder = "data\\";
	virtual void SetSyncedMetaData(const std::string& key, alt::MValue val) override {
		metaData->insert({ key, val });
	};
	virtual void DeleteSyncedMetaData(const std::string& key) {
		metaData->erase(key);
	};

	virtual const std::string& GetRootDirectory() override {
		return root;
	};

	virtual alt::IResource* StartResource(const std::string& name) override {
		//LogDebug("RUN UNIMPLEMENTED StartResource");
		alt::Resource* resource = (alt::Resource*)resources->at(name);
		resource->Start();
		if (!resource->IsStarted()) {
			LogError("ERROR START RESOURCE " + name, (alt::IResource*)resource);
		}
		else {
			LogInfo("Stared resource: " + name, (alt::IResource*)resource);
			eventQueue->push_back({ new alt::CResourceStartEvent((alt::IResource*)resource) });
		}

		return (alt::IResource*)resource;
	};

	virtual void StopResource(const std::string& name) override {
		//LogDebug("RUN UNIMPLEMENTED StopResource");
		alt::IResource* resource = (alt::IResource*)resources->at(name);
		eventQueue->push_back({ new alt::CResourceStopEvent(resource) });
	};
	virtual void RestartResource(const std::string& name) override {
		//LogDebug("RUN UNIMPLEMENTED RestartResource");
		StopResource(name);
		StartResource(name);
	};

	virtual void TriggerClientEvent(alt::IPlayer* target, const std::string& ev, alt::MValueArgs args) override {
		//LogDebug("RUN UNIMPLEMENTED TriggerClientEvent " + ev);

		alt::Player* player = (alt::Player*)target;

		const std::shared_ptr<alt::IPlayer>& ptr = std::make_shared<alt::Player>(*player);
		//const std::shared_ptr<alt::Player>& ptr = std::make_shared<alt::Player>(target);
		eventQueue->push_back({ new alt::CClientScriptEvent(ptr, ev, args)});
	};
	virtual void TriggerClientEvent(std::vector<alt::IPlayer*> targets, const std::string& ev, alt::MValueArgs args) override {
		//LogDebug("RUN UNIMPLEMENTED TriggerClientEvent " + ev);


		for (size_t i = 0; i < targets.size(); i++)
		{
			auto target = targets.at(i);
			TriggerClientEvent(target, ev, args);
		}
	};
	virtual void TriggerClientEventForAll(const std::string& ev, alt::MValueArgs args) override {
		//LogDebug("RUN UNIMPLEMENTED TriggerClientEventForAll " + ev);
		std::vector<alt::IPlayer*> targets = GetPlayers();
		for (size_t i = 0; i < targets.size(); i++)
		{
			auto target = targets.at(i);
			TriggerClientEvent(target, ev, args);
		}
	};

	void TriggerClientEventUnreliable(alt::IPlayer* target, const std::string& ev, alt::MValueArgs args) {

	};
	void TriggerClientEventUnreliable(std::vector<alt::IPlayer*> targets, const std::string& ev, alt::MValueArgs args) {

	};
	void TriggerClientEventUnreliableForAll(const std::string& ev, alt::MValueArgs args) {

	};

	virtual alt::IVehicle* CreateVehicle(uint32_t model, alt::Position pos, alt::Rotation rot) override {
		LogDebug("RUN UNIMPLEMENTED CreateVehicle");
		//int id = idProvider.Next();
		//auto cs = new alt::Vehicle(id, model, pos, rot);
		//return (alt::IVehicle*)(cs);
		return NULL;
	};

	virtual alt::ICheckpoint* CreateCheckpoint(uint8_t type, alt::Position pos, float radius, float height, alt::RGBA color) override {
		LogDebug("RUN UNIMPLEMENTED CreateCheckpoint");
		return NULL;
	};
	//
	//
	//virtual IVirtualEntity* CreateVirtualEntity(IVirtualEntityGroup* group, Position pos, uint32_t streamingDistance) override {
	//	return NULL;
	//};
	//
	//
	//virtual IVirtualEntityGroup* CreateVirtualEntityGroup(uint32_t streamingRangeLimit) override {
	//	return NULL;
	//};

	virtual alt::IBlip* CreateBlip(alt::IPlayer* target, alt::IBlip::BlipType type, alt::Position pos) override {
		//LogDebug("RUN UNIMPLEMENTED CreateBlip");
		int id = idProvider.Next();
		auto cs = new alt::Blip(id, target, type, pos);
		return (alt::IBlip*)(cs);
	};

	virtual alt::IBlip* CreateBlip(alt::IPlayer* target, alt::IBlip::BlipType type, alt::IEntity* attachTo) override {
		int id = idProvider.Next();
		auto cs = new alt::Blip(id, target, type, attachTo);
		return (alt::IBlip*)(cs);
	};

	virtual alt::IVoiceChannel* CreateVoiceChannel(bool spatial, float maxDistance) override {
		LogDebug("RUN UNIMPLEMENTED CreateVoiceChannel");
		int id = idProvider.Next();
		auto cs = new alt::VoiceChannel(id, spatial, maxDistance);
		return (alt::IVoiceChannel*)(cs);
		//return NULL;
	};

	virtual alt::IColShape* CreateColShapeCylinder(alt::Position pos, float radius, float height) override {
		LogDebug("RUN UNIMPLEMENTED CreateColShapeCylinder");
		return NULL;
	};
	virtual alt::IColShape* CreateColShapeSphere(alt::Position pos, float radius) override {
		LogDebug("RUN UNIMPLEMENTED CreateColShapeSphere");
		return NULL;
	};
	virtual alt::IColShape* CreateColShapeCircle(alt::Position pos, float radius) override {
		//LogDebug("RUN UNIMPLEMENTED CreateColShapeCircle");
		int id = idProvider.Next();
		auto cs = new alt::ColShape(id, alt::IColShape::ColShapeType::CIRCLE);
		return (alt::IColShape*)(cs);
	};
	virtual alt::IColShape* CreateColShapeCube(alt::Position pos, alt::Position pos2) override {
		//LogDebug("RUN UNIMPLEMENTED CreateColShapeCube");
		int id = idProvider.Next();
		auto cs = new alt::ColShape(id, alt::IColShape::ColShapeType::CUBOID);
		return (alt::IColShape*)(cs);
	};
	virtual alt::IColShape* CreateColShapeRectangle(float x1, float y1, float x2, float y2, float z) override {
		//LogDebug("RUN UNIMPLEMENTED CreateColShapeRectangle");
		int id = idProvider.Next();
		auto cs = new alt::ColShape(id, alt::IColShape::ColShapeType::RECT);
		return (alt::IColShape*)(cs);
		//return NULL;
	};
	virtual alt::IColShape* CreateColShapePolygon(float minZ, float maxZ, std::vector<alt::Vector2f> points) override {
		//LogDebug("RUN UNIMPLEMENTED CreateColShapePolygon");
		int id = idProvider.Next();
		auto cs = new alt::ColShape(id, alt::IColShape::ColShapeType::POLYGON);
		return (alt::IColShape*)(cs);
		//return NULL;
	};

	virtual std::vector<alt::IPlayer*> GetPlayersByName(const std::string& name) const override {
		LogDebug("RUN UNIMPLEMENTED GetPlayersByName");
		return std::vector<alt::IPlayer*>();
	};

	virtual uint32_t GetNetTime() const override {
		LogDebug("RUN UNIMPLEMENTED GetNetTime");
		return 423;
	};

	virtual void SetPassword(const std::string& password) const override {
		LogDebug("RUN UNIMPLEMENTED SetPassword " + password);
	};
	virtual uint64_t HashServerPassword(const std::string& password) const override {
		LogDebug("RUN UNIMPLEMENTED HashServerPassword");
		return 0;
	};

	virtual void StopServer() override {
		LogDebug("RUN UNIMPLEMENTED StopServer");
		//throw "StopServer";
	};

	virtual const alt::VehicleModelInfo& GetVehicleModelByHash(uint32_t hash) const override {
		LogDebug("RUN UNIMPLEMENTED GetVehicleModelByHash");
		return alt::VehicleModelInfo();
	};

	virtual const alt::PedModelInfo& GetPedModelByHash(uint32_t hash) const override {
		auto it = pedModels.find(hash);
		if (it != pedModels.end()) pedModels.at(hash);
		LogDebug("GetPedModelByHash NOT FOUND: " + std::to_string(hash));
		return alt::PedModelInfo();
	};


	virtual Config::Value::ValuePtr GetServerConfig() const override {
		return config;
	};

	virtual void SetWorldProfiler(bool state) override {
		LogDebug("RUN UNIMPLEMENTED SetWorldProfiler");
	};

	const std::string LoadRoot() {
		std::string executablePath = getExecutablePath();
		std::filesystem::path path(executablePath.c_str());
		std::string root = path.remove_filename().lexically_normal().string();
		std::string str2 = root.substr(0, root.length() - 1);
		return str2;
	}

	const Config::Value::ValuePtr LoadConfig() {
		std::string cfg;
		std::string error;
		std::string line;
		std::string path = GetRootDirectory() + "\\server.toml";
		std::ifstream myfile(path);
		if (myfile.is_open())
		{
			while (std::getline(myfile, line))
			{
				cfg.append(line + '\n');
			}
			myfile.close();
		}

		else std::cout << "Unable to open file";
		return TomlConfig::Parse(cfg, error);
	}

	std::string GetModulesPath() {
		return GetRootDirectory() + "/" + modulesFolder;
	}

	std::string GetDataPath() {
		return GetRootDirectory() + "/" + dataFolder;
	}

	std::vector<std::string> GetResourcePaths() {
		std::vector<std::string> paths;
		for (const auto& entry : resourcesFolders) {
			auto execPath = std::filesystem::path(GetRootDirectory());
			auto path = execPath.append(entry).lexically_normal();
			paths.push_back({ path.string() + "\\" });
		}
		return paths;
	}

	void AddResource(alt::IResource::CreationInfo info, std::string path) {
		if (runtimes->find(info.type) == runtimes->end()) {
			LogError("UNKNOWN RUNTIME TYPE:" + info.type);
			return;
		}

		alt::IScriptRuntime* runtime = runtimes->at(info.type);
		alt::Resource* resource = new alt::Resource((alt::ICore*)(this), info, path);
		resources->insert({ info.name, (alt::IResource*)resource });
		auto impl = runtime->CreateImpl((alt::IResource*)resource);
		resource->impl = impl;
		resource->runtime = runtime;
		this->StartResource(info.name);
	}

	void AddCloth(uint8_t componentId, uint8_t drawableId, uint8_t textureId, uint32_t dlc) {
		clothesInfo.insert({
			dlc,
			BaseCore::ClothInfo{
				componentId,
				drawableId,
				textureId,
				dlc
			}
			});
	}

	void AddProp(uint8_t componentId, uint8_t drawableId, uint8_t textureId, uint32_t dlc) {
		propsInfo.insert({
			dlc,
			BaseCore::PropInfo{
				componentId,
				drawableId,
				textureId,
				dlc
			}
			});
	}

	void AddModKit(BaseCore::VehicleModKitInfo modKit) {
		modKitInfos.insert({ modKit.modKitId, modKit });
	}

	uint32_t CreatePlayer() {
		uint32_t clientId = idProvider.Next();
		auto player = new alt::Player(this, clientId);

		entities->insert({ clientId, player });

		const std::shared_ptr<alt::Player>& ptr = std::make_shared<alt::Player>(*player);

		OnCreateBaseObject(player);

		CEvent* event = new CPlayerConnectEvent(ptr);

		eventQueue->push_back({ event });

		return clientId;
	}
};

#undef ALT_SERVER_API