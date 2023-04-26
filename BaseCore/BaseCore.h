#pragma once
#include "SDK.h"
#include "BaseObject.h"
#include "MValue.h"
#include "Blip.h"
#include "Vehicle.h"
#include "IdProvider.h"
#include "deps/toml/TomlConfig.h"
#include "Colshape.h"
#include "VoiceChannel.h"
#include "Resource.h"

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

class BaseCore : public alt::ICore
{
public:
	struct ClothInfo {
		uint8_t componentId;
		uint8_t drawableId;
		uint8_t textureId;
		uint32_t dlc;

		ClothInfo() = default;

		ClothInfo(uint8_t _componentId, uint8_t _drawableId, uint8_t _textureId, uint32_t _dlc) :
			componentId(componentId), drawableId(_drawableId), textureId(_textureId), dlc(_dlc) { }

		friend std::ostream& operator<<(std::ostream& stream, const ClothInfo& cloth)
		{
			stream << "ClothInfo{ " << (int)cloth.drawableId << ", " << (int)cloth.textureId << ", "
				<< (int)cloth.componentId << ", " << (int)cloth.dlc << " }";
			return stream;
		}
	};
	struct PropInfo {
		uint8_t componentId;
		uint8_t drawableId;
		uint8_t textureId;
		uint32_t dlc;

		PropInfo() = default;

		PropInfo(uint8_t _componentId, uint8_t _drawableId, uint8_t _textureId, uint32_t _dlc) :
			componentId(componentId), drawableId(_drawableId), textureId(_textureId), dlc(_dlc) { }

		friend std::ostream& operator<<(std::ostream& stream, const PropInfo& cloth)
		{
			stream << "PropInfo{ " << (int)cloth.drawableId << ", " << (int)cloth.textureId << ", "
				<< (int)cloth.componentId << ", " << (int)cloth.dlc << " }";
			return stream;
		}
	};
	struct VehicleModInfo {
		uint8_t category;
		uint8_t count;
		std::vector<uint16_t> components;

		VehicleModInfo(uint8_t category, uint8_t count) :
			category(category), count(count) {
		}

		friend std::ostream& operator<<(std::ostream& stream, const VehicleModInfo& cloth)
		{
			stream << "VehicleModInfo{ " << (int)cloth.category << ", " << cloth.count << " }";
			return stream;
		}
	};

	struct VehicleModKitInfo {
		uint16_t modKitId;
		std::string name;
		uint8_t modsCount;

		std::vector<BaseCore::VehicleModInfo> mods;

		friend std::ostream& operator<<(std::ostream& stream, const VehicleModKitInfo& cloth)
		{
			stream << "VehicleModKitInfo{ " << (int)cloth.modKitId << ", " << cloth.name << ", "
				<< (int)cloth.modsCount << " }";
			return stream;
		}
	};
	IdProvider idProvider;
	std::unordered_map<std::string, alt::MValue>* metaData = new std::unordered_map<std::string, alt::MValue>();
	std::unordered_map<std::string, alt::MValue>* metaSyncedData = new std::unordered_map<std::string, alt::MValue>();
	std::unordered_map<std::string, alt::IScriptRuntime*>* runtimes = new std::unordered_map<std::string, alt::IScriptRuntime*>();
	std::unordered_map<std::string, alt::IResource*>* resources = new std::unordered_map<std::string, alt::IResource*>();
	bool started = false;
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

	virtual alt::MValueNone CreateMValueNone() override {
		alt::IMValueNone* s = new alt::IMValueNoneImpl();
		return alt::MValueNone(s);
	}

	virtual alt::MValueNil CreateMValueNil() override {
		alt::IMValueNil* s = new alt::IMValueNilImpl();
		return alt::MValueNil(s);
	}

	virtual alt::MValueBool CreateMValueBool(bool val) override {
		alt::IMValueBool* s = new alt::IMValueBoolImpl(val);
		return alt::MValueBool(s);
	}

	virtual alt::MValueInt CreateMValueInt(int64_t val) override {
		alt::IMValueInt* s = new alt::IMValueIntImpl(val);
		return alt::MValueInt(s);
	}

	virtual alt::MValueUInt CreateMValueUInt(uint64_t val) override {
		alt::IMValueUInt* s = new alt::IMValueUIntImpl(val);
		return alt::MValueUInt(s);
	}

	virtual alt::MValueDouble CreateMValueDouble(double val) override {
		alt::IMValueDouble* s = new alt::IMValueDoubleImpl(val);
		return alt::MValueDouble(s);
	}

	virtual alt::MValueString CreateMValueString(const std::string& val) override {
		alt::IMValueString* s = new alt::IMValueStringImpl(val);
		return alt::MValueString(s);
	}

	virtual alt::MValueList CreateMValueList(alt::Size size = 0) override {
		alt::IMValueList* s = new alt::IMValueListImpl(size);
		return alt::MValueList(s);
	};

	virtual alt::MValueDict CreateMValueDict() override {
		alt::IMValueDict* s = new alt::IMValueDictImpl();
		return alt::MValueDict(s);
	}

	virtual alt::MValueBaseObject CreateMValueBaseObject(alt::IBaseObject* val) override {
		alt::IMValueBaseObject* s = new alt::IMValueBaseObjectImpl(val);
		return alt::MValueBaseObject(s);
	};
	virtual alt::MValueBaseObject CreateMValueBaseObject(std::shared_ptr<alt::IBaseObject> val) override {
		alt::IMValueBaseObject* s = new alt::IMValueBaseObjectImpl(val.get());
		return alt::MValueBaseObject(s);
	};
	virtual alt::MValueFunction CreateMValueFunction(alt::IMValueFunction::Impl* impl) override {
		alt::IMValueFunction::Impl* const impl1 = std::as_const(impl);
		alt::IMValueFunctionImpl* s = new alt::IMValueFunctionImpl(impl1);
		return alt::MValueFunction(s);
	};
	virtual alt::MValueVector2 CreateMValueVector2(alt::Vector2f val) override {
		alt::IMValueVector2* s = new alt::IMValueVector2Impl(val);
		return alt::MValueVector2(s);
	};
	virtual alt::MValueVector3 CreateMValueVector3(alt::Vector3f val) override {
		alt::IMValueVector3* s = new alt::IMValueVector3Impl(val);
		return alt::MValueVector3(s);
	};
	virtual alt::MValueRGBA CreateMValueRGBA(alt::RGBA val) override {
		alt::IMValueRGBA* s = new alt::IMValueRGBAImpl(val);
		return alt::MValueRGBA(s);
	};
	virtual alt::MValueByteArray CreateMValueByteArray(const uint8_t* data, alt::Size size) override {
		alt::IMValueByteArray* s = new alt::IMValueByteArrayImpl(data, size);
		return alt::MValueByteArray(s);
	};
	virtual alt::MValueByteArray CreateMValueByteArray(alt::Size size) override {
		alt::IMValueByteArray* s = new alt::IMValueByteArrayImpl(size);
		return alt::MValueByteArray(s);
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

	virtual bool RegisterScriptRuntime(const std::string& resourceType, alt::IScriptRuntime* runtime) override {
		runtimes->insert({ resourceType, runtime });
		LogInfo("RegisterScriptRuntim type: " + resourceType);
		return true;
	};

	virtual bool SubscribeCommand(const std::string& cmd, alt::CommandCallback cb) override {
		LogDebug("RUN UNIMPLEMENTED SubscribeCommand");
		return true;
	}

	virtual bool FileExists(const std::string& path) override {
		LogDebug("RUN UNIMPLEMENTED FileExists");
		return false;
	}

	virtual std::string FileRead(const std::string& path) override {
		LogDebug("RUN UNIMPLEMENTED FileRead");
		return "";
	}

	virtual alt::IResource* GetResource(const std::string& name) override {
		//LogDebug("GetResource: => " + name);
		if (resources->find(name) != resources->end())
			return (alt::IResource*)resources->at(name);
		return NULL;
	};

	virtual alt::IEntity* GetEntityByID(uint16_t id) const override {
		LogDebug("RUN UNIMPLEMENTED GetEntityByID");
		return NULL;
	};

	virtual std::vector<alt::IEntity*> GetEntities() const override {
		LogDebug("RUN UNIMPLEMENTED GetEntities");
		return std::vector<alt::IEntity*>();
	};
	virtual std::vector<alt::IPlayer*> GetPlayers() const override {
		LogDebug("RUN UNIMPLEMENTED GetPlayers");
		return std::vector<alt::IPlayer*>();
	};
	virtual std::vector<alt::IVehicle*> GetVehicles() const override {
		LogDebug("RUN UNIMPLEMENTED GetVehicles");
		return std::vector<alt::IVehicle*>();
	};
	virtual std::vector<alt::IBlip*> GetBlips() const override {
		LogDebug("RUN UNIMPLEMENTED GetBlips");
		return std::vector<alt::IBlip*>();
	};

	virtual void TriggerLocalEvent(const std::string& ev, alt::MValueArgs args) override {
		LogDebug("RUN UNIMPLEMENTED TriggerLocalEvent: " + ev);

	};
	virtual void TriggerLocalEventOnMain(const std::string& ev, alt::MValueArgs args) override {
		LogDebug("RUN UNIMPLEMENTED TriggerLocalEventOnMain: " + ev);

	};

	virtual bool HasMetaData(const std::string& key) const override {
		return metaData->contains(key);
	};
	virtual alt::MValueConst GetMetaData(const std::string& key) const override {
		auto it = metaData->find(key);
		if (it == metaData->end()) return alt::MValueConst(alt::MValueNone());
		auto data = metaData->at(key);

		return data;
	};
	virtual void SetMetaData(const std::string& key, alt::MValue val)override {
		metaData->insert({ key, val });
	};
	virtual void DeleteMetaData(const std::string& key) override {
		metaData->erase(key);
	};

	std::vector<std::string> GetMetaDataKeys() const {
		std::vector<std::string> keys;
		for (auto& i : *metaData) keys.push_back(i.first);
	    return keys;
	};

	virtual bool HasSyncedMetaData(const std::string& key) const override {
		return metaData->contains(key);
	};
	virtual alt::MValueConst GetSyncedMetaData(const std::string& key) const override {
		auto it = metaData->find(key);
		if (it == metaData->end()) return alt::MValueConst(alt::MValueNone());
		auto data = metaData->at(key);

		return data;
	};

	virtual const alt::Array<alt::Permission> GetRequiredPermissions() const override {
		LogDebug("RUN UNIMPLEMENTED GetRequiredPermissions");
		return alt::Array<alt::Permission>();
	};
	virtual const alt::Array<alt::Permission> GetOptionalPermissions() const override {
		LogDebug("RUN UNIMPLEMENTED GetOptionalPermissions");
		return alt::Array<alt::Permission>();
	};

	virtual alt::IPackage::PathInfo Resolve(alt::IResource* resource, const std::string& path, const std::string& currentModulePath) const override {
		alt::IPackage* pkg1 = NULL;
		return alt::IPackage::PathInfo{ pkg1, path, currentModulePath };
	}

	virtual void DestroyBaseObject(alt::IBaseObject* handle) override {
		LogDebug("RUN UNIMPLEMENTED DestroyBaseObject");
	};

	virtual const std::vector<alt::IResource*> GetAllResources() const override {
		std::vector<alt::IResource*> arr;
		for (auto it = resources->begin(); it != resources->end(); it++) {
			auto res = (alt::IResource*)it->second;
			arr.push_back({ res });
		}
		return arr;
	}

	virtual std::string StringToSHA256(const std::string& str) const override {
		LogDebug("RUN UNIMPLEMENTED StringToSHA256: " + str);
		return "";
	};

	virtual bool IsEventEnabled(alt::CEvent::Type type) const override {
		LogDebug("RUN UNIMPLEMENTED IsEventEnabled");
		return false;
	};

	virtual void ToggleEvent(alt::CEvent::Type type, bool state) override {
		LogDebug("RUN UNIMPLEMENTED ToggleEvent");
	};

	//std::shared_ptr<alt::INative::Context> CreateNativesContext() const {
	//	auto ctx = std::make_shared<NativeContext>();
	//
	//
	//	alt::INative::Context* ptr = static_cast<alt::INative::Context*>(ctx.get());
	//
	//	auto shread = std::make_shared<alt::INative::Context>(ptr);
	//
	//	return shread;
	//}

	void OnTick() {
		if (!started) return;
		for (auto it = resources->begin(); it != resources->end(); ++it) {
			try
			{
				if (!it->second->IsStarted()) return;
				it->second->GetRuntime()->OnTick();
				it->second->GetImpl()->OnTick();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}

		}
	}
};
