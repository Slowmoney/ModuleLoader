#pragma once
#include <SDK.h>
#include "BaseCore.h"

namespace alt
{
	class BaseCore;
	class Player: public alt::IPlayer
	{
	public:
		std::unordered_map<std::string, MValue>* metaData = new std::unordered_map<std::string, MValue>();
		std::unordered_map<std::string, MValue>* streamSyncedMetaData = new std::unordered_map<std::string, MValue>();
		std::unordered_map<std::string, MValue>* syncedMetaData = new std::unordered_map<std::string, MValue>();
		int32_t dimension = 0;
		bool removed = false;
		alt::IBaseObject::Type type = alt::IBaseObject::Type::PLAYER;
		int id;
		uint32_t model;
		Position pos;
		Rotation rot;
		IPlayer* netOwner = NULL;
		alt::BaseCore* core = NULL;
		Player(alt::BaseCore* core, uint32_t id) : id(id), core(core) {
			//core->OnCreateBaseObject(this);
		}

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

		virtual std::string GetName() const {
			return "";
		}

		virtual uint16_t GetHealth() const {
			return 200;
		}
		virtual uint16_t GetMaxHealth() const {
			return 200;
		}
		virtual bool HasWeaponComponent(uint32_t weapon, uint32_t component) const {
			return false;
		}
		virtual std::vector<uint32_t> GetCurrentWeaponComponents() const {
			return std::vector<uint32_t>();
		}

		virtual uint8_t GetWeaponTintIndex(uint32_t weapon) const {
			return NULL;
		}
		virtual uint8_t GetCurrentWeaponTintIndex() const {
			return NULL;
		}

		virtual uint32_t GetCurrentWeapon() const {
			return NULL;
		}

		virtual bool IsDead() const {
			return NULL;
		}

		virtual bool IsJumping() const {
			return NULL;
		}
		virtual bool IsInRagdoll() const {
			return NULL;
		}
		virtual bool IsAiming() const {
			return NULL;
		}
		virtual bool IsShooting() const {
			return NULL;
		}
		virtual bool IsReloading() const {
			return NULL;
		}
		virtual bool IsEnteringVehicle() const {
			return NULL;
		}
		virtual bool IsLeavingVehicle() const {
			return NULL;
		}
		virtual bool IsOnLadder() const {
			return NULL;
		}
		virtual bool IsInMelee() const {
			return NULL;
		}
		virtual bool IsInCover() const {
			return NULL;
		}

		virtual uint16_t GetArmour() const {
			return NULL;
		}
		virtual uint16_t GetMaxArmour() const {
			return NULL;
		}

		virtual float GetMoveSpeed() const {
			return NULL;
		}

		virtual Position GetAimPos() const {
			return Position(.0,.0,.0);
		}
		virtual Rotation GetHeadRotation() const {
			return Rotation(.0, .0, .0);
		}

		virtual bool IsInVehicle() const {
			return NULL;
		}
		virtual IVehicle* GetVehicle() const {
			return NULL;
		}
		virtual uint8_t GetSeat() const {
			return NULL;
		}

		virtual IEntity* GetEntityAimingAt() const {
			return NULL;
		}
		virtual Position GetEntityAimOffset() const {
			return Rotation(.0, .0, .0);
		}

		virtual bool IsFlashlightActive() const {
			return NULL;
		}

		virtual bool IsSuperJumpEnabled() const {
			return NULL;
		}
		virtual bool IsCrouching() const {
			return NULL;
		}
		virtual bool IsStealthy() const {
			return NULL;
		}

		virtual uint32_t GetCurrentAnimationDict() const {
			return NULL;
		}
		virtual uint32_t GetCurrentAnimationName() const {
			return NULL;
		}

		virtual bool IsSpawned() const {
			return NULL;
		}

		virtual float GetForwardSpeed() const {
			return NULL;
		}
		virtual float GetStrafeSpeed() const {
			return NULL;
		}

#ifdef ALT_SERVER_API
		std::unordered_map<std::string, MValue>* localMetaData = new std::unordered_map<std::string, MValue>();
		virtual bool IsConnected() const {
			return NULL;
		}
		virtual uint32_t GetPing() const {
			return NULL;
		}
		virtual std::string GetIP() const {
			return NULL;
		}
		virtual uint64_t GetSocialID() const {
			return NULL;
		}
		virtual std::string GetSocialClubName() const {
			return NULL;
		}
		virtual uint64_t GetHwidHash() const {
			return NULL;
		}
		virtual uint64_t GetHwidExHash() const {
			return NULL;
		}
		virtual std::string GetAuthToken() const {
			return NULL;
		}
		virtual int64_t GetDiscordId() const {
			return NULL;
		}

		virtual void Spawn(Position pos, uint32_t delayMs) {
			this->pos = pos;
			//core->OnPlayerSpawn(this);
		}
		virtual void Despawn() {
		}
		virtual void SetModel(uint32_t model) {
			this->model = model;
		}
		virtual void SetArmour(uint16_t armor) {
			
		}
		virtual void SetMaxArmour(uint16_t armor) {
			
		}
		virtual void SetCurrentWeapon(uint32_t weapon) {
			
		}
		virtual void SetWeaponTintIndex(uint32_t weapon, uint8_t tintIndex) {
			
		}
		virtual void AddWeaponComponent(uint32_t weapon, uint32_t component) {
			
		}
		virtual void RemoveWeaponComponent(uint32_t weapon, uint32_t component) {
			
		}
		virtual void ClearBloodDamage() {
			
		}
		virtual void SetHealth(uint16_t health) {
			
		}
		virtual void SetMaxHealth(uint16_t health) {
			
		}
		virtual void GiveWeapon(uint32_t weapon, int32_t ammo, bool selectWeapon) {
			
		}
		virtual bool RemoveWeapon(uint32_t weapon) {
			return NULL;
		}
		virtual void RemoveAllWeapons() {
			
		}
		virtual void SetDateTime(int day, int month, int year, int hour, int minute, int second) {
			
		}
		virtual void SetWeather(uint32_t weather) {
			
		}
		virtual void Kick(const std::string& reason = "Kicked") {
			
		}
		virtual alt::Cloth GetClothes(uint8_t component) const {
			return alt::Cloth{0,0,0};
		}
		virtual bool SetClothes(uint8_t component, uint16_t drawable, uint8_t texture, uint8_t palette) {
			return NULL;
		}
		virtual alt::DlcCloth GetDlcClothes(uint8_t component) const {
			return alt::DlcCloth{ 0,0,0,0 };
		}
		virtual bool SetDlcClothes(uint8_t component, uint16_t drawable, uint8_t texture, uint8_t palette, uint32_t dlc) {
			return NULL;
		}
		virtual alt::Prop GetProps(uint8_t component) const {
			return alt::Prop(0,0);
		}
		virtual bool SetProps(uint8_t component, uint16_t drawable, uint8_t texture) {
			return NULL;
		}
		virtual alt::DlcProp GetDlcProps(uint8_t component) const {
			return alt::DlcProp( 0,0,0);
		}
		virtual bool SetDlcProps(uint8_t component, uint8_t drawable, uint8_t texture, uint32_t dlc) {
			return NULL;
		}
		virtual void ClearProps(uint8_t component) {
			
		}
		virtual bool IsEntityInStreamingRange(uint16_t entityId) {
			return NULL;
		}
		virtual void SetInvincible(bool toggle) {
			
		}
		virtual bool GetInvincible() const {
			return NULL;
		}
		virtual void SetIntoVehicle(IVehicle* vehicle, uint8_t seat) {
			
		}
		virtual void PlayAmbientSpeech(const std::string& speechName, const std::string& speechParam, uint32_t speechDictHash) {
			
		}
		virtual bool SetHeadOverlay(uint8_t overlayID, uint8_t index, float opacity) {
			return NULL;
		}
		virtual bool RemoveHeadOverlay(uint8_t overlayID) {
			return NULL;
		}
		virtual bool SetHeadOverlayColor(uint8_t overlayID, uint8_t colorType, uint8_t colorIndex, uint8_t secondColorIndex) {
			return NULL;
		}
		virtual HeadOverlay GetHeadOverlay(uint8_t overlayID) const {
			return HeadOverlay{ 0,.0,0,0,0 };
		}
		virtual bool SetFaceFeature(uint8_t index, float scale) {
			return NULL;
		}
		virtual float GetFaceFeatureScale(uint8_t index) const {
			return NULL;
		}
		virtual bool RemoveFaceFeature(uint8_t index) {
			return NULL;
		}
		virtual bool SetHeadBlendPaletteColor(uint8_t id, uint8_t red, uint8_t green, uint8_t blue) {
			return NULL;
		}
		virtual RGBA GetHeadBlendPaletteColor(uint8_t id) const {
			return RGBA(0,0,0,0);
		}
		virtual void SetHeadBlendData(uint32_t shapeFirstID, uint32_t shapeSecondID, uint32_t shapeThirdID,
			uint32_t skinFirstID, uint32_t skinSecondID, uint32_t skinThirdID,
			float shapeMix, float skinMix, float thirdMix) {
		}
		virtual HeadBlendData GetHeadBlendData() const {
			return HeadBlendData{ 0,0,0,0,0,0,.0,.0,.0 };
		}
		virtual bool SetEyeColor(int16_t eyeColor) {
			return NULL;
		}
		virtual int16_t GetEyeColor() const {
			return NULL;
		}
		virtual void SetHairColor(uint8_t hairColor) {
			
		}
		virtual uint8_t GetHairColor() const {
			return NULL;
		}
		virtual void SetHairHighlightColor(uint8_t hairHighlightColor) {
			
		}
		virtual uint8_t GetHairHighlightColor() const {
			return NULL;
		}
		virtual std::vector<Weapon> GetWeapons() const {
			return std::vector<Weapon>();
		}

		virtual bool HasLocalMetaData(const std::string& key) const {
			return localMetaData->contains(key);
		}
		virtual void SetLocalMetaData(const std::string& key, MValue val) {
			localMetaData->insert({ key, val });
		}
		virtual MValue GetLocalMetaData(const std::string& key) const {
			auto it = localMetaData->find(key);
			if (it == localMetaData->end()) return MValue(MValueNone());
			auto data = localMetaData->at(key);

			return data;
		}
		virtual void DeleteLocalMetaData(const std::string& key) {
			metaData->erase(key);
		}
		virtual std::vector<std::string> GetLocalMetaDataKeys() const {
			std::vector<std::string> keys;
			for (auto& i : *localMetaData) keys.push_back(i.first);
			return keys;
		}

		virtual uint32_t GetInteriorLocation() const {
			return NULL;
		}

		virtual uint32_t GetLastDamagedBodyPart() const {
			return NULL;
		}
		virtual void SetLastDamagedBodyPart(uint32_t bodyPart) {
			
		}
		virtual void SetSendNames(bool state) {
			
		}
		virtual bool GetSendNames() const {
			return NULL;
		}

		virtual void PlayAnimation(const std::string& animDict, const std::string& animName, float blendInSpeed, float blendOutSpeed, int duration, int flags, float playbackRate, bool lockX, bool lockY, bool lockZ) {
			
		}
		virtual void ClearTasks() {
			
		}

		virtual std::string GetCloudAuthHash() const {
			return "NULL";
		}
#endif // ALT_SERVER_API

#ifdef ALT_CLIENT_API
		virtual bool IsTalking() const {
			return NULL;
		}
		virtual float GetMicLevel() const {
			return 0.0;
		}

		virtual float GetSpatialVolume() const {
			return 0.0;
		}
		virtual void SetSpatialVolume(float volume) {
			
		}
		virtual float GetNonSpatialVolume() const {
			return NULL;
		}
		virtual void SetNonSpatialVolume(float volume) {
			;
		}
#endif // ALT_CLIENT_API

#ifdef ALT_CLIENT_API
		virtual int32_t GetScriptGuid() const {
			return 0;
		}
#endif // ALT_CLIENT_API
	};

}