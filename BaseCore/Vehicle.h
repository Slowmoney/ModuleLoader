#pragma once
#include <SDK.h>
#include <string>
namespace alt {
	class Vehicle : public alt::IVehicle
	{
		std::unordered_map<std::string, MValue>* metaData = new std::unordered_map<std::string, MValue>();
		std::unordered_map<std::string, MValue>* streamSyncedMetaData = new std::unordered_map<std::string, MValue>();
		std::unordered_map<std::string, MValue>* syncedMetaData = new std::unordered_map<std::string, MValue>();
	public:

		Vehicle(int id, uint32_t model, Position pos, Rotation rot) : id(id), model(model), pos(pos), rot(rot) {};
		virtual alt::IBaseObject::Type GetType() const override {
			return type;
		};

		virtual bool HasMetaData(const std::string& key) const {
			return metaData->contains(key);
		};
		virtual MValueConst GetMetaData(const std::string& key) const {
			auto it = metaData->find(key);
			if (it == metaData->end()) return MValueConst(MValueNone());
			auto data = metaData->at(key);

			return data;
		};
		virtual void SetMetaData(const std::string& key, MValue val) {
			metaData->insert({ key, val });
		};
		virtual void DeleteMetaData(const std::string& key) {
			metaData->erase(key);
		};
		virtual std::vector<std::string> GetMetaDataKeys() const {
			std::vector<std::string> keys;
			for (auto& i : *metaData) keys.push_back(i.first);
			return keys;
		};

		virtual bool IsRemoved() const {
			return removed;
		};

		virtual bool HasSyncedMetaData(const std::string& key) const {
			return syncedMetaData->contains(key);
		};

		virtual MValueConst GetSyncedMetaData(const std::string& key) const {
			auto it = syncedMetaData->find(key);
			if (it == syncedMetaData->end()) return MValueConst(MValueNone());
			auto data = syncedMetaData->at(key);

			return data;
		};
		virtual std::vector<std::string> GetSyncedMetaDataKeys() const {
			std::vector<std::string> keys;
			for (auto& i : *syncedMetaData) keys.push_back(i.first);
			return keys;
		};
#ifdef ALT_SERVER_API
		virtual void SetSyncedMetaData(const std::string& key, MValue val) {
			syncedMetaData->insert({ key, val });
		};
		virtual void DeleteSyncedMetaData(const std::string& key) {
			syncedMetaData->erase(key);
		};
#endif

		Position GetPosition() const {
			return this->pos;
		};
		void SetPosition(Position pos) {
			this->pos = pos;
		};

		int32_t GetDimension() const {
			return this->dimension;
		};
		void SetDimension(int32_t dimension) {
			this->dimension = dimension;
		};


		virtual uint16_t GetID() const {
			return id;
		}

		virtual IPlayer* GetNetworkOwner() const {
			return netOwner;
		}

		virtual uint32_t GetModel() const {
			return model;
		}

		virtual Rotation GetRotation() const {
			return rot;
		}
		virtual void SetRotation(Rotation rot) {
			this->rot = rot;
		}

		virtual bool HasStreamSyncedMetaData(const std::string& key) const {
			return streamSyncedMetaData->contains(key);
		};
		virtual MValueConst GetStreamSyncedMetaData(const std::string& key) const {
			auto it = streamSyncedMetaData->find(key);
			if (it == streamSyncedMetaData->end()) return MValueConst(MValueNone());
			auto data = streamSyncedMetaData->at(key);

			return data;
		};


		virtual std::vector<std::string> GetStreamSyncedMetaDataKeys() const {
			std::vector<std::string> keys;
			for (auto& i : *streamSyncedMetaData) keys.push_back(i.first);
			return keys;
		};

		virtual bool GetVisible() const {
			return false;
		}

#ifdef ALT_SERVER_API
		virtual void SetNetworkOwner(IPlayer* player, bool disableMigration) {

		}
		virtual void SetStreamSyncedMetaData(const std::string& key, MValue val) {
			streamSyncedMetaData->insert({ key, val });
		};
		virtual void DeleteStreamSyncedMetaData(const std::string& key) {
			streamSyncedMetaData->erase(key);
		};
		virtual void SetVisible(bool toggle) {

		}

		virtual void AttachToEntity(IEntity* entity, int16_t otherBoneIndex, int16_t myBoneIndex, Position position, Rotation rotation, bool collision, bool noFixedRotation) { }
		virtual void AttachToEntity(IEntity* entity, const std::string& otherBoneName, const std::string& myBoneName, Position position, Rotation rotation, bool collision, bool noFixedRotation) { }
		virtual void Detach() { }

		virtual void SetStreamed(bool toggle) { }
		virtual bool GetStreamed() const {
			return false;
		}

		virtual bool IsFrozen() const {
			return false;
		}
		virtual void SetFrozen(bool state) { }

		virtual bool HasCollision() const {
			return false;
		}
		virtual void SetCollision(bool state) { }
#endif // ALT_SERVER_API

#ifdef ALT_CLIENT_API
		virtual int32_t GetScriptGuid() const {}
#endif // ALT_CLIENT_API

		virtual IPlayer* GetDriver() const {
			return NULL;
		}
		virtual bool IsDestroyed() const {
			return false;
		}
		virtual uint8_t GetMod(uint8_t category) const { return NULL; }
		virtual uint8_t GetModsCount(uint8_t category) const { return NULL; }
		virtual uint8_t GetModKitsCount() const { return NULL; }
		virtual uint8_t GetModKit() const { return NULL; }
		virtual bool IsPrimaryColorRGB() const { return NULL; }
		virtual uint8_t GetPrimaryColor() const { return NULL; }
		virtual RGBA GetPrimaryColorRGB() const { return RGBA{ 0,0,0,0 }; }
		virtual bool IsSecondaryColorRGB() const { return NULL; }
		virtual uint8_t GetSecondaryColor() const { return NULL; }
		virtual RGBA GetSecondaryColorRGB() const { return RGBA{ 0,0,0,0 }; }
		virtual uint8_t GetPearlColor() const { return NULL; }
		virtual uint8_t GetWheelColor() const { return NULL; }
		virtual uint8_t GetInteriorColor() const { return NULL; }
		virtual uint8_t GetDashboardColor() const { return NULL; }
		virtual bool IsTireSmokeColorCustom() const { return NULL; }
		virtual RGBA GetTireSmokeColor() const { return RGBA{ 0,0,0,0 };
		}
		virtual uint8_t GetWheelType() const { return NULL; }
		virtual uint8_t GetWheelVariation() const { return NULL; }
		virtual uint8_t GetRearWheelVariation() const { return NULL; }
		virtual bool GetCustomTires() const { return NULL; }
		virtual uint8_t GetSpecialDarkness() const { return NULL; }
		virtual uint32_t GetNumberplateIndex() const { return NULL; }
		virtual std::string GetNumberplateText() const { return ""; }
		virtual uint8_t GetWindowTint() const { return NULL; }
		virtual uint8_t GetDirtLevel() const { return NULL; }
		virtual bool IsExtraOn(uint8_t extraID) const { return NULL; }
		virtual bool IsNeonActive() const { return NULL; }
		virtual void GetNeonActive(bool* left, bool* right, bool* front, bool* back) const { }
		virtual RGBA GetNeonColor() const { return RGBA{ 0,0,0,0 };
		}
		virtual uint8_t GetLivery() const { return NULL; }
		virtual uint8_t GetRoofLivery() const { return NULL; }
		virtual std::string GetAppearanceDataBase64() {
			return "";
		}
		virtual bool IsEngineOn() const { return NULL; }
		virtual bool IsHandbrakeActive() const { return NULL; }
		virtual uint8_t GetHeadlightColor() const { return NULL; }
		virtual uint32_t GetRadioStationIndex() const { return NULL; }
		virtual bool IsSirenActive() const { return NULL; }
		// TODO document available values. Enum?
		virtual uint8_t GetLockState() const { return NULL; }
		// TODO document available values. Enum?
		virtual uint8_t GetDoorState(uint8_t doorId) const { return NULL; }
		virtual bool IsWindowOpened(uint8_t windowId) const { return NULL; }
		virtual bool IsDaylightOn() const { return NULL; }
		virtual bool IsNightlightOn() const { return NULL; }
		virtual uint8_t GetRoofState() const { return NULL; }
		virtual bool IsFlamethrowerActive() const { return NULL; }
		virtual float GetLightsMultiplier() const { return NULL; }
		virtual std::string GetGameStateBase64() { return ""; }
		virtual int32_t GetEngineHealth() const { return NULL; }
		virtual int32_t GetPetrolTankHealth() const { return NULL; }
		virtual uint8_t GetWheelsCount() const { return NULL; }
		virtual bool IsWheelBurst(uint8_t wheelId) { return NULL; }
		virtual bool DoesWheelHasTire(uint8_t wheelId) { return NULL; }
		virtual bool IsWheelDetached(uint8_t wheelId) { return NULL; }
		virtual bool IsWheelOnFire(uint8_t wheelId) { return NULL; }
		virtual float GetWheelHealth(uint8_t wheelId) { return NULL; }
		virtual uint8_t GetRepairsCount() const { return NULL; }
		virtual uint32_t GetBodyHealth() const { return NULL; }
		virtual uint32_t GetBodyAdditionalHealth() const { return NULL; }
		virtual std::string GetHealthDataBase64() override { return ""; }
		virtual uint8_t GetPartDamageLevel(uint8_t partId) { return NULL; }
		virtual uint8_t GetPartBulletHoles(uint8_t partId) { return NULL; }
		virtual bool IsLightDamaged(uint8_t lightId) { return NULL; }
		virtual bool IsWindowDamaged(uint8_t windowId) { return NULL; }
		virtual bool IsSpecialLightDamaged(uint8_t specialLightId) { return NULL; }
		virtual bool HasArmoredWindows() const { return NULL; }
		virtual float GetArmoredWindowHealth(uint8_t windowId) { return NULL; }
		virtual uint8_t GetArmoredWindowShootCount(uint8_t windowId) { return NULL; }
		virtual uint8_t GetBumperDamageLevel(uint8_t bumperId) { return NULL; }
		virtual std::string GetDamageDataBase64() { return ""; }
		virtual bool IsManualEngineControl() const { return NULL; }
		virtual std::string GetScriptDataBase64() { return ""; }
		virtual void ToggleExtra(uint8_t extraID, bool state) { }
		virtual Vector3f GetVelocity() const { return Vector3f{0.0,0.0,0.0}; }

#ifdef ALT_SERVER_API
		virtual void SetFixed() {  }
		virtual bool SetMod(uint8_t category, uint8_t id) { return NULL; }
		virtual bool SetModKit(uint8_t id) { return NULL; }
		virtual void SetPrimaryColor(uint8_t color) {  }
		virtual void SetPrimaryColorRGB(RGBA color) { }
		virtual void SetSecondaryColor(uint8_t color) {  }
		virtual void SetSecondaryColorRGB(RGBA color) { }
		virtual void SetPearlColor(uint8_t color) {  }
		virtual void SetWheelColor(uint8_t color) { }
		virtual void SetInteriorColor(uint8_t color) { }
		virtual void SetDashboardColor(uint8_t color) {  }
		virtual void SetTireSmokeColor(RGBA color) {  }
		virtual void SetWheels(uint8_t type, uint8_t variation) { }
		virtual void SetRearWheels(uint8_t variation) {  }
		virtual void SetCustomTires(bool state) { }
		virtual void SetSpecialDarkness(uint8_t value) {}
		virtual void SetNumberplateIndex(uint32_t index) {}
		virtual void SetNumberplateText(const std::string& text) {}
		virtual void SetWindowTint(uint8_t tint) {}
		virtual void SetDirtLevel(uint8_t level) {}
		virtual void SetNeonActive(bool left, bool right, bool front, bool back) {}
		virtual void SetNeonColor(RGBA color) {}
		virtual void SetLivery(uint8_t livery) {}
		virtual void SetRoofLivery(uint8_t roofLivery) {}
		virtual void LoadAppearanceDataFromBase64(const std::string& base64) {}
		virtual void SetEngineOn(bool state) {}
		virtual void SetHeadlightColor(uint8_t color) {}
		virtual void SetRadioStationIndex(uint32_t stationIndex) {}
		virtual void SetSirenActive(bool state) {}
		virtual void SetLockState(uint8_t state) {}
		virtual void SetDoorState(uint8_t doorId, uint8_t state) {}
		virtual void SetWindowOpened(uint8_t windowId, bool state) {}
		virtual void SetRoofState(uint8_t state) {}
		virtual void SetLightsMultiplier(float multiplier) {}
		virtual void SetEngineHealth(int32_t health) {}
		virtual void SetPetrolTankHealth(int32_t health) {}
		virtual void SetWheelBurst(uint8_t wheelId, bool state) {}
		virtual void SetWheelHasTire(uint8_t wheelId, bool state) {}
		virtual void SetWheelDetached(uint8_t wheelId, bool state) {}
		virtual void SetWheelOnFire(uint8_t wheelId, bool state) {}
		virtual void SetWheelHealth(uint8_t wheelId, float health) {}
		virtual void SetWheelFixed(uint8_t wheelId) {}
		virtual void SetBodyHealth(uint32_t health) {}
		virtual void SetBodyAdditionalHealth(uint32_t health) {}
		virtual void SetPartDamageLevel(uint8_t partId, uint8_t damage) {}
		virtual void SetPartBulletHoles(uint8_t partId, uint8_t shootsCount) {}
		virtual void SetLightDamaged(uint8_t lightId, bool isDamaged) {}
		virtual void SetWindowDamaged(uint8_t windowId, bool isDamaged) {}
		virtual void SetSpecialLightDamaged(uint8_t specialLightId, bool isDamaged) {}
		virtual void SetArmoredWindowHealth(uint8_t windowId, float health) {}
		virtual void SetArmoredWindowShootCount(uint8_t windowId, uint8_t count) {}
		virtual void SetBumperDamageLevel(uint8_t bumperId, uint8_t damageLevel) {}
		virtual void SetManualEngineControl(bool state) {}
		virtual void LoadDamageDataFromBase64(const std::string& base64) {}
		virtual void LoadScriptDataFromBase64(const std::string& base64) {}
		virtual void LoadGameStateFromBase64(const std::string& base64) {}
		virtual void LoadHealthDataFromBase64(const std::string& base64) {}
		virtual IVehicle* GetAttached() const { return NULL; }
		virtual IVehicle* GetAttachedTo() const { return NULL; }
		virtual bool IsDriftMode() const { return NULL; }
		virtual void SetDriftMode(bool state) {}

		virtual bool IsTrainMissionTrain() const { return NULL; }
		virtual void SetTrainMissionTrain(bool value) {}
		virtual int8_t GetTrainTrackId() const { return NULL; }
		virtual void SetTrainTrackId(int8_t trackId) {}
		virtual IVehicle* GetTrainEngineId() const { return NULL; }
		virtual void SetTrainEngineId(IVehicle* vehicle) { }
		virtual int8_t GetTrainConfigIndex() const { return NULL; }
		virtual void SetTrainConfigIndex(int8_t trainConfigIndex) {}
		virtual float GetTrainDistanceFromEngine() const { return NULL; }
		virtual void SetTrainDistanceFromEngine(float distanceFromEngine) {}
		virtual bool IsTrainEngine() const { return NULL; }
		virtual void SetTrainIsEngine(bool isEngine) {}
		virtual bool IsTrainCaboose() const { return NULL; }
		virtual void SetTrainIsCaboose(bool isCaboose) {}
		virtual bool GetTrainDirection() const { return NULL; }
		virtual void SetTrainDirection(bool direction) {}
		virtual bool HasTrainPassengerCarriages() const { return NULL; }
		virtual void SetTrainHasPassengerCarriages(bool hasPassengerCarriages) {}
		virtual bool GetTrainRenderDerailed() const { return NULL; }
		virtual void SetTrainRenderDerailed(bool renderDerailed) {}
		virtual bool GetTrainForceDoorsOpen() const { return NULL; }
		virtual void SetTrainForceDoorsOpen(bool forceDoorsOpen) {}
		virtual float GetTrainCruiseSpeed() const { return NULL; }
		virtual void SetTrainCruiseSpeed(float cruiseSpeed) {}
		virtual int8_t GetTrainCarriageConfigIndex() const { return NULL; }
		virtual void SetTrainCarriageConfigIndex(int8_t carriageConfigIndex) {}
		virtual IVehicle* GetTrainLinkedToBackwardId() const { return NULL; }
		virtual void SetTrainLinkedToBackwardId(IVehicle* vehicle) {}
		virtual IVehicle* GetTrainLinkedToForwardId() const { return NULL; }
		virtual void SetTrainLinkedToForwardId(IVehicle* vehicle) {}
		virtual void SetTrainUnk1(bool unk1) {}
		virtual bool GetTrainUnk1() const { return NULL; }
		virtual void SetTrainUnk2(bool unk2) {}
		virtual bool GetTrainUnk2() const { return NULL; }
		virtual void SetTrainUnk3(bool unk3) {}
		virtual bool GetTrainUnk3() const { return NULL; }

		virtual bool IsBoatAnchorActive() const { return NULL; }
		virtual void SetBoatAnchorActive(bool state) {}

		virtual bool SetSearchLight(bool state, IEntity* spottedEntity) { return NULL; }

		virtual uint8_t GetLightState() const { return NULL; }
		virtual void SetLightState(uint8_t state) { }

		virtual bool HasTimedExplosion() const { return NULL; }
		virtual IPlayer* GetTimedExplosionCulprit() const { return NULL; }
		virtual uint32_t GetTimedExplosionTime() const { return NULL; }
		virtual void SetTimedExplosion(bool state, IPlayer* culprit, uint32_t time) {  }

		virtual bool IsTowingDisabled() const { return NULL; }
		virtual void SetDisableTowing(bool state) {  }

		virtual float GetRocketRefuelSpeed() const { return NULL; }
		virtual void SetRocketRefuelSpeed(float rocketRefuelSpeed) {  }

		virtual uint32_t GetCounterMeasureCount() const { return NULL; }
		virtual void SetCounterMeasureCount(uint32_t counterMeasureCount) {  }

		virtual float GetScriptMaxSpeed() const { return NULL; }
		virtual void SetScriptMaxSpeed(float scriptMaxSpeed) {  }

		virtual int32_t GetWeaponCapacity(uint8_t index) const { return NULL; }
		virtual void SetWeaponCapacity(uint8_t index, int32_t state) { }

		virtual bool GetHybridExtraActive() const { return NULL; }
		virtual void SetHybridExtraActive(bool state) { }

		virtual uint8_t GetHybridExtraState() const { return NULL; }
		virtual void SetHybridExtraState(uint8_t state) { }

		//virtual Quaternion GetQuaternion() const { return NULL; }
		//virtual void SetQuaternion(Quaternion quaternion) { return NULL; }
#endif // ALT_SERVER_API

#ifdef ALT_CLIENT_API
		virtual float GetWheelSpeed() const { return NULL; }
		virtual uint16_t GetCurrentGear() const { return NULL; }
		virtual float GetCurrentRPM() const { return NULL; }
		virtual Vector3f GetSpeedVector() const { }
		virtual uint16_t GetMaxGear() const { return NULL; }

		virtual void SetCurrentGear(uint16_t currentGear) { }
		virtual void SetMaxGear(uint16_t gearMax) { }

		virtual bool IsHandlingModified() const { return NULL; }
		virtual std::shared_ptr<alt::IHandlingData> GetHandling() const { return NULL; }
		virtual void ResetHandling() { }
		virtual void ReplaceHandling() { }

		virtual uint8_t GetLightsIndicator() const { return NULL; }
		virtual void SetLightsIndicator(uint8_t lightsIndicatorFlag) { }

		virtual uint8_t GetSeatCount() const { return NULL; }
		virtual uint8_t GetOccupiedSeatsCount() const { return NULL; }

		virtual void ToggleTaxiLight(bool state) { }
		virtual bool IsTaxiLightOn() const { return NULL; }

		virtual float GetWheelCamber(uint8_t wheel) const { return NULL; }
		virtual void SetWheelCamber(uint8_t wheel, float value) { }
		virtual float GetWheelTrackWidth(uint8_t wheel) const { return NULL; }
		virtual void SetWheelTrackWidth(uint8_t wheel, float value) { }
		virtual float GetWheelHeight(uint8_t wheel) const { return NULL; }
		virtual void SetWheelHeight(uint8_t wheel, float value) { }
		virtual float GetWheelTyreRadius(uint8_t wheel) const { return NULL; }
		virtual void SetWheelTyreRadius(uint8_t wheel, float value) { }
		virtual float GetWheelRimRadius(uint8_t wheel) const { return NULL; }
		virtual void SetWheelRimRadius(uint8_t wheel, float value) { }
		virtual float GetWheelTyreWidth(uint8_t wheel) const { return NULL; }
		virtual void SetWheelTyreWidth(uint8_t wheel, float value) { }
		virtual uint32_t GetWheelSurfaceMaterial(uint8_t wheel) const { return NULL; }

		virtual float GetEngineTemperature() const { return NULL; }
		virtual void SetEngineTemperature(float value) { }
		virtual float GetFuelLevel() const { return NULL; }
		virtual void SetFuelLevel(float value) {  }
		virtual float GetOilLevel() const { return NULL; }
		virtual void SetOilLevel(float value) { }
		virtual bool GetEngineLightState() const { return NULL; }
		virtual void SetEngineLightState(bool state) { }
		virtual bool GetAbsLightState() const { return NULL; }
		virtual void SetAbsLightState(bool state) { }
		virtual bool GetPetrolLightState() const { return NULL; }
		virtual void SetPetrolLightState(bool state) { }
		virtual bool GetOilLightState() const { return NULL; }
		virtual void SetOilLightState(bool state) { }
		virtual bool GetBatteryLightState() const { return NULL; }
		virtual void SetBatteryLightState(bool state) { }
		virtual void ResetDashboardLights() { }
#endif // ALT_CLIENT_API

		int32_t dimension = 0;
		bool removed = false;
		alt::IBaseObject::Type type = alt::IBaseObject::Type::VEHICLE;
		int id;
		uint32_t model;
		Position pos;
		Rotation rot;
		IPlayer* netOwner = NULL;
	};
}
