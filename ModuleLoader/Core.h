#pragma once
#include <SDK.h>
#include <iostream>
#include <unordered_map>
#include "ScriptRuntime.h"
#include "BaseObject.h"
#include "WorldObject.h"
#include "VoiceChannel.h"
#include "Vehicle.h"
#include "Colshape.h"
#include "MValue.h"
#include "Blip.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include "TomlConfig.h"
#include "IdProvider.h"
#ifndef _COLORS_
#define _COLORS_

/* FOREGROUND */
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#define LOG(c, x, resource) std::string name = "";if(resource != NULL) name = "[" + resource->GetName() + "] ";std::cout  << c << KGRN << name << c << x << str << RST << std::endl;

#endif  /* _COLORS_ */

std::string getExecutablePath() {
	char rawPathName[MAX_PATH];
	GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
	return std::string(rawPathName);
}
std::string getExecutableDir() {
	std::string executablePath = getExecutablePath();
	std::filesystem::path path(executablePath.c_str());

	std::string root = path.remove_filename().lexically_normal().string();


	std::string r(root.begin(), root.end());
	r.resize(r.size() - 2);
	std::string str2 = root.substr(0, root.length() - 1);
	return str2;
}

namespace alt {
	class Core : ICore {
		IdProvider idProvider;
		std::unordered_map<std::string, MValue>* metaData = new std::unordered_map<std::string, MValue>();
		std::unordered_map<std::string, MValue>* metaSyncedData = new std::unordered_map<std::string, MValue>();
	public:
		std::unordered_map<std::string, Resource*>* resources = new std::unordered_map<std::string, Resource*>();
		std::unordered_map<std::string, IScriptRuntime*>* runtimes = new std::unordered_map<std::string, IScriptRuntime*>();
		virtual std::string GetVersion() const override {
			return "CORE v2";
		};

		virtual std::string GetBranch() const override {
			return "master";
		}

		virtual void LogInfo(const std::string& str, alt::IResource* resource = nullptr) override {
			LOG(RST, "[info] ", resource);
		}

		virtual void LogDebug(const std::string& str, alt::IResource* resource = nullptr) override {
			LOG(KMAG, "[debug] ", resource);
		}

		virtual void LogWarning(const std::string& str, alt::IResource* resource = nullptr) override {
			LOG(KYEL, "[warning] ", resource);
		}

		virtual void LogError(const std::string& str, alt::IResource* resource = nullptr) override {
			LOG(KRED, "[error] ", resource);
		}

		virtual void LogColored(const std::string& str, alt::IResource* resource = nullptr) override {
			LOG(KCYN, "[colored] ", resource);
		}

		void const LogInfo(const std::string& str, alt::IResource* resource = nullptr) const {
			LOG(RST, "[info] ", resource);
		}

		void const LogDebug(const std::string& str, alt::IResource* resource = nullptr) const {
			LOG(KMAG, "[debug] ", resource);
		}

		virtual MValueNone CreateMValueNone() override {
			alt::IMValueNone* s = new IMValueNoneImpl();
			return MValueNone(s);
		}

		virtual MValueNil CreateMValueNil() override {
			alt::IMValueNil* s = new IMValueNilImpl();
			return MValueNil(s);
		}

		virtual MValueBool CreateMValueBool(bool val) override {
			alt::IMValueBool* s = new IMValueBoolImpl(val);
			return MValueBool(s);
		}

		virtual MValueInt CreateMValueInt(int64_t val) override {
			alt::IMValueInt* s = new IMValueIntImpl(val);
			return MValueInt(s);
		}

		virtual MValueUInt CreateMValueUInt(uint64_t val) override {
			alt::IMValueUInt* s = new IMValueUIntImpl(val);
			return MValueUInt(s);
		}

		virtual MValueDouble CreateMValueDouble(double val) override {
			alt::IMValueDouble* s = new IMValueDoubleImpl(val);
			return MValueDouble(s);
		}

		virtual MValueString CreateMValueString(const std::string& val) override {
			alt::IMValueString* s = new IMValueStringImpl(val);
			return MValueString(s);
		}

		virtual MValueList CreateMValueList(alt::Size size = 0) override {
			alt::IMValueList* s = new IMValueListImpl(size);
			return MValueList(s);
		};

		virtual MValueDict CreateMValueDict() override {
			alt::IMValueDict* s = new IMValueDictImpl();
			return MValueDict(s);
		}

		virtual MValueBaseObject CreateMValueBaseObject(alt::IBaseObject* val) override {
			alt::IMValueBaseObject* s = new IMValueBaseObjectImpl(val);
			return MValueBaseObject(s);
		};
		virtual MValueBaseObject CreateMValueBaseObject(std::shared_ptr<IBaseObject> val) override {
			alt::IMValueBaseObject* s = new IMValueBaseObjectImpl(val.get());
			return MValueBaseObject(s);
		};
		virtual MValueFunction CreateMValueFunction(alt::IMValueFunction::Impl* impl) override {
			alt::IMValueFunction::Impl* const impl1 = std::as_const(impl);
			IMValueFunctionImpl* s = new IMValueFunctionImpl(impl1);
			return MValueFunction(s);
		};
		virtual MValueVector2 CreateMValueVector2(Vector2f val) override {
			alt::IMValueVector2* s = new IMValueVector2Impl(val);
			return MValueVector2(s);
		};
		virtual MValueVector3 CreateMValueVector3(Vector3f val) override {
			alt::IMValueVector3* s = new IMValueVector3Impl(val);
			return MValueVector3(s);
		};
		virtual MValueRGBA CreateMValueRGBA(RGBA val) override {
			alt::IMValueRGBA* s = new IMValueRGBAImpl(val);
			return MValueRGBA(s);
		};
		virtual MValueByteArray CreateMValueByteArray(const uint8_t* data, Size size) override {
			alt::IMValueByteArray* s = new IMValueByteArrayImpl(data, size);
			return MValueByteArray(s);
		};
		virtual MValueByteArray CreateMValueByteArray(Size size) override {
			alt::IMValueByteArray* s = new IMValueByteArrayImpl(size);
			return MValueByteArray(s);
		};

		virtual bool IsDebug() const override {
			LogDebug("RUN UNIMPLEMENTED IsDebug");
			return false;
		};

		virtual uint32_t Hash(const std::string& str) const override {
			uint32_t hash = 0;
			for (const char c : str)
			{
				hash += c;
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}
			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);
			return hash;
		};

		virtual bool SubscribeCommand(const std::string& cmd, CommandCallback cb) override {
			LogDebug("RUN UNIMPLEMENTED SubscribeCommand");
			return true;
		}

		virtual bool RegisterScriptRuntime(const std::string& resourceType, IScriptRuntime* runtime) override {
			runtimes->insert({ resourceType, runtime });
			LogInfo("RegisterScriptRuntim type: " + resourceType);
			return true;
		};

		virtual bool FileExists(const std::string& path) override {
			LogDebug("RUN UNIMPLEMENTED FileExists");
			return false;
		}

		virtual std::string FileRead(const std::string& path) override {
			LogDebug("RUN UNIMPLEMENTED FileRead");
			return "";
		}

		virtual IResource* GetResource(const std::string& name) override {
			//LogDebug("GetResource: => " + name);
			if (resources->find(name) != resources->end())
				return (IResource*)resources->at(name);
			return NULL;
		};

		virtual IEntity* GetEntityByID(uint16_t id) const override {
			LogDebug("RUN UNIMPLEMENTED GetEntityByID");
			return NULL;
		};

		virtual std::vector<IEntity*> GetEntities() const override {
			LogDebug("RUN UNIMPLEMENTED GetEntities");
			return std::vector<IEntity*>();
		};
		virtual std::vector<IPlayer*> GetPlayers() const override {
			LogDebug("RUN UNIMPLEMENTED GetPlayers");
			return std::vector<IPlayer*>();
		};
		virtual std::vector<IVehicle*> GetVehicles() const override {
			LogDebug("RUN UNIMPLEMENTED GetVehicles");
			return std::vector<IVehicle*>();
		};
		virtual std::vector<IBlip*> GetBlips() const override {
			LogDebug("RUN UNIMPLEMENTED GetBlips");
			return std::vector<IBlip*>();
		};
		//virtual std::vector<ICheckpoint*> GetCheckpoints() const override {
		//	return std::vector<ICheckpoint*>();
		//};
		//virtual std::vector<IPed*> GetPeds() const override {
		//	return std::vector<IPed*>();
		//};;
		//virtual std::vector<IVirtualEntity*> GetVirtualEntities() const override {
		//	return std::vector<IVirtualEntity*>();
		//};
		//virtual std::vector<IVirtualEntityGroup*> GetVirtualEntityGroups() const override {
		//	return std::vector<IVirtualEntityGroup*>();
		//};
		//virtual std::vector<INetworkObject*> GetNetworkObjects() const override {
		//	return std::vector<INetworkObject*>();
		//};

		virtual void TriggerLocalEvent(const std::string& ev, MValueArgs args) override {
			LogDebug("RUN UNIMPLEMENTED TriggerLocalEvent");

		};
		virtual void TriggerLocalEventOnMain(const std::string& ev, MValueArgs args) override {
			LogDebug("RUN UNIMPLEMENTED TriggerLocalEventOnMain");

		};

		virtual bool HasMetaData(const std::string& key) const override {
			return metaData->contains(key);
		};
		virtual MValueConst GetMetaData(const std::string& key) const override {
			auto it = metaData->find(key);
			if (it == metaData->end()) return MValueConst(MValueNone());
			auto data = metaData->at(key);

			return data;
		};
		virtual void SetMetaData(const std::string& key, MValue val)override {
			metaData->insert({ key, val });
		};
		virtual void DeleteMetaData(const std::string& key) override {
			metaData->erase(key);
		};
		//virtual std::vector<std::string> GetMetaDataKeys() const override {
		//	std::vector<std::string> keys;
		//	for (auto& i : *metaData) keys.push_back(i.first);
		//	return keys;
		//};

		virtual bool HasSyncedMetaData(const std::string& key) const override {
			return metaData->contains(key);
		};
		virtual MValueConst GetSyncedMetaData(const std::string& key) const override {
			auto it = metaData->find(key);
			if (it == metaData->end()) return MValueConst(MValueNone());
			auto data = metaData->at(key);

			return data;
		};
		virtual void SetSyncedMetaData(const std::string& key, MValue val) override {
			metaData->insert({ key, val });
		};
		virtual void DeleteSyncedMetaData(const std::string& key) {
			metaData->erase(key);
		};
		//virtual std::vector<std::string> GetSyncedMetaDataKeys() const override {
		//	std::vector<std::string> keys;
		//	for (auto& i : *metaData) keys.push_back(i.first);
		//	return keys;
		//};

		virtual const Array<Permission> GetRequiredPermissions() const override {
			LogDebug("RUN UNIMPLEMENTED GetRequiredPermissions");
			return Array<Permission>();
		};
		virtual const Array<Permission> GetOptionalPermissions() const override {
			LogDebug("RUN UNIMPLEMENTED GetOptionalPermissions");
			return Array<Permission>();
		};

		virtual IPackage::PathInfo Resolve(IResource* resource, const std::string& path, const std::string& currentModulePath) const override {
			IPackage* pkg1 = NULL;
			return IPackage::PathInfo{ pkg1, path, currentModulePath };
		}

		virtual void DestroyBaseObject(IBaseObject* handle) override {
			LogDebug("RUN UNIMPLEMENTED DestroyBaseObject");
		};

		virtual const std::vector<IResource*> GetAllResources() const override {
			LogDebug("RUN UNIMPLEMENTED GetAllResources");
			return std::vector<IResource*>();
		}

		virtual std::string StringToSHA256(const std::string& str) const override {
			LogDebug("RUN UNIMPLEMENTED StringToSHA256");
			return "";
		};

		virtual bool IsEventEnabled(alt::CEvent::Type type) const override {
			LogDebug("RUN UNIMPLEMENTED IsEventEnabled");
			return false;
		};
		virtual void ToggleEvent(alt::CEvent::Type type, bool state) override {
			LogDebug("RUN UNIMPLEMENTED ToggleEvent");
		};

		virtual const std::string& GetRootDirectory() override {
			auto dir = getExecutableDir();
			return dir;
		};

		virtual IResource* StartResource(const std::string& name) override {
			LogDebug("RUN UNIMPLEMENTED StartResource");
			return (IResource*)resources->at(name);
		};

		virtual void StopResource(const std::string& name) override {
			LogDebug("RUN UNIMPLEMENTED StopResource");
			resources->at(name);
		};
		virtual void RestartResource(const std::string& name) override {
			LogDebug("RUN UNIMPLEMENTED RestartResource");
			resources->at(name);
		};

		virtual void TriggerClientEvent(IPlayer* target, const std::string& ev, MValueArgs args) override {
			LogDebug("RUN UNIMPLEMENTED TriggerClientEvent");

		};
		virtual void TriggerClientEvent(std::vector<IPlayer*> targets, const std::string& ev, MValueArgs args) override {
			LogDebug("RUN UNIMPLEMENTED TriggerClientEvent");

		};
		virtual void TriggerClientEventForAll(const std::string& ev, MValueArgs args) override {
			LogDebug("RUN UNIMPLEMENTED TriggerClientEventForAll");
		};

		//virtual void TriggerClientEventUnreliable(IPlayer* target, const std::string& ev, MValueArgs args)override {
		//	
		//};
		//virtual void TriggerClientEventUnreliable(std::vector<IPlayer*> targets, const std::string& ev, MValueArgs args)override {
		//	
		//};
		//virtual void TriggerClientEventUnreliableForAll(const std::string& ev, MValueArgs args)override {
		//	
		//};

		virtual IVehicle* CreateVehicle(uint32_t model, Position pos, Rotation rot) override {
			LogDebug("RUN UNIMPLEMENTED CreateVehicle");
			int id = idProvider.Next();
			auto cs = new alt::Vehicle(id, model, pos, rot);
		    return (IVehicle*)(cs);
			//return NULL;
		};

		virtual ICheckpoint* CreateCheckpoint(uint8_t type, Position pos, float radius, float height, RGBA color) override {
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

		virtual IBlip* CreateBlip(IPlayer* target, IBlip::BlipType type, Position pos) override {
			//LogDebug("RUN UNIMPLEMENTED CreateBlip");
			int id = idProvider.Next();
			auto cs = new alt::Blip(id, target, type, pos);
			return (IBlip*)(cs);
		};

		virtual IBlip* CreateBlip(IPlayer* target, IBlip::BlipType type, IEntity* attachTo) override {
			int id = idProvider.Next();
			auto cs = new alt::Blip(id, target, type, attachTo);
			return (IBlip*)(cs);
		};

		virtual IVoiceChannel* CreateVoiceChannel(bool spatial, float maxDistance) override {
			LogDebug("RUN UNIMPLEMENTED CreateVoiceChannel");
			int id = idProvider.Next();
			auto cs = new alt::VoiceChannel(id, spatial, maxDistance);
			return (IVoiceChannel*)(cs);
			//return NULL;
		};

		virtual IColShape* CreateColShapeCylinder(Position pos, float radius, float height) override {
			LogDebug("RUN UNIMPLEMENTED CreateColShapeCylinder");
			return NULL;
		};
		virtual IColShape* CreateColShapeSphere(Position pos, float radius) override {
			LogDebug("RUN UNIMPLEMENTED CreateColShapeSphere");
			return NULL;
		};
		virtual IColShape* CreateColShapeCircle(Position pos, float radius) override {
			//LogDebug("RUN UNIMPLEMENTED CreateColShapeCircle");
			int id = idProvider.Next();
			auto cs = new alt::ColShape(id, alt::IColShape::ColShapeType::CIRCLE);
			return (IColShape*)(cs);
		};
		virtual IColShape* CreateColShapeCube(Position pos, Position pos2) override {
		    //LogDebug("RUN UNIMPLEMENTED CreateColShapeCube");
			int id = idProvider.Next();
			auto cs = new alt::ColShape(id, alt::IColShape::ColShapeType::CUBOID);
			return (IColShape*)(cs);
		};
		virtual IColShape* CreateColShapeRectangle(float x1, float y1, float x2, float y2, float z) override {
			LogDebug("RUN UNIMPLEMENTED CreateColShapeRectangle");
			int id = idProvider.Next();
			auto cs = new alt::ColShape(id, alt::IColShape::ColShapeType::RECT);
			return (IColShape*)(cs);
			//return NULL;
		};
		virtual IColShape* CreateColShapePolygon(float minZ, float maxZ, std::vector<Vector2f> points) override {
			LogDebug("RUN UNIMPLEMENTED CreateColShapePolygon");
			int id = idProvider.Next();
			auto cs = new alt::ColShape(id, alt::IColShape::ColShapeType::POLYGON);
			return (IColShape*)(cs);
			//return NULL;
		};

		virtual std::vector<IPlayer*> GetPlayersByName(const std::string& name) const override {
			LogDebug("RUN UNIMPLEMENTED GetPlayersByName");
			return std::vector<IPlayer*>();
		};

		virtual uint32_t GetNetTime() const override {
			LogDebug("RUN UNIMPLEMENTED GetNetTime");
			return 423;
		};

		virtual void SetPassword(const std::string& password) const override {
			LogDebug("RUN UNIMPLEMENTED SetPassword");
		};
		virtual uint64_t HashServerPassword(const std::string& password) const override {
			LogDebug("RUN UNIMPLEMENTED HashServerPassword");
			return 0;
		};

		virtual void StopServer() override {
			LogDebug("RUN UNIMPLEMENTED StopServer");
		};

		virtual const VehicleModelInfo& GetVehicleModelByHash(uint32_t hash) const override {
			LogDebug("RUN UNIMPLEMENTED GetVehicleModelByHash");
			return VehicleModelInfo();
		};

		virtual const cdecl PedModelInfo& GetPedModelByHash(uint32_t hash) const override {
			LogDebug("RUN UNIMPLEMENTED GetPedModelByHash");
			std::string sss = "sss";
			auto data = new PedModelInfo{
				hash,
				sss,
				"type",
				"dlcName",
				"defaultUnarmedWeapon",
				"movementClipSet",
				std::vector<BoneInfo>()
			};
			std::cout << &data << std::endl;

			auto data2 = PedModelInfo(*data);
			std::cout << &data2 << std::endl;
			return *data;
		};


		virtual Config::Value::ValuePtr GetServerConfig() const override {
			return config;
		};

		virtual void SetWorldProfiler(bool state) override {
			LogDebug("RUN UNIMPLEMENTED SetWorldProfiler");
		};

		//virtual IPed* CreatePed(uint32_t model, Position pos, Rotation rot) override {
		//	return 0;
		//};

		//virtual std::vector<IBaseObject*> GetEntitiesInDimension(int32_t dimension, uint64_t allowedTypes) const override {
		//	return std::vector<IBaseObject*>();
		//}
		//virtual std::vector<IBaseObject*> GetEntitiesInRange(Position position, int32_t range, int32_t dimension, uint64_t allowedTypes) const override{
		//	return std::vector<IBaseObject*>();
		//}
		//virtual std::vector<IBaseObject*> GetClosestEntities(Position position, int32_t range, int32_t dimension, int32_t limit, uint64_t allowedTypes) const override {
		//	return std::vector<IBaseObject*>();
		//}

		//virtual INetworkObject* CreateNetworkObject(uint32_t model, Position pos, Rotation rot, uint8_t alpha = 255, uint8_t textureVariation = 0, uint16_t lodDistance = 100) override {
		//	return 0;
		//};

		//virtual std::vector<IColShape*> GetColShapes() const override {
		//	return std::vector<IColShape*>();
		//}


		void OnTick() {
			if (!started) return;
			for (auto it = resources->begin(); it != resources->end(); ++it) {
				try
				{
					if (!it->second->IsStarted()) return;
					it->second->runtime->OnTick();
					it->second->GetImpl()->OnTick();
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}

			}
		}

		void AddResource(IResource::CreationInfo info) {
			if (runtimes->find(info.type) == runtimes->end()) {
				LogError("UNKNOWN RUNTIME TYPE:" + info.type);
				return;
			}
			IScriptRuntime* runtime = runtimes->at(info.type);
			Resource* resource = new Resource((alt::ICore*)(this), info, GetResourcePath());
			resources->insert({ info.name, resource });
			auto impl = runtime->CreateImpl((IResource*)resource);
			resource->impl = impl;
			resource->runtime = runtime;
			resource->Start();
			if (!resource->IsStarted()) {
				LogError("ERROR START RESOURCE " + info.type, (IResource*)resource);
			}
			else {
				LogInfo("Stared resource: " + info.name, (IResource*)resource);
			}
		}

		void Stop() {
			started = false;
		}

		const Config::Value::ValuePtr LoadConfig() {
			std::string cfg;
			std::string error;
			std::string line;
			std::string path = getExecutableDir() + "/server.toml";
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

		std::string GetResourcePath() {
			std::string path = getExecutableDir() + "\\" + resourcesFolder;
			return path;
		}

		std::string GetModulesPath() {
			return getExecutableDir() + "\\" + modulesFolder;
		}

		bool started = true;
		const Config::Value::ValuePtr config = LoadConfig();
		std::string resourcesFolder = "resources\\";
		std::string modulesFolder = "modules\\";

		~Core() {
			std::cout << "~Core" << std::endl;
			resources->clear();
			//delete localStorage;
		}
	};
}

