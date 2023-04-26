#pragma once
#include <SDK.h>
namespace alt {
	class VoiceChannel : public alt::IVoiceChannel
	{
	public:
		VoiceChannel(int id, bool spatial, float maxDistance): id(id), spatial(spatial), maxDistance(maxDistance) {}
		std::unordered_map<std::string, MValue>* metaData = new std::unordered_map<std::string, MValue>();
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

		virtual uint32_t GetID() const { return id; }

		virtual bool IsSpatial() const { return spatial; }
		virtual float GetMaxDistance() const { return maxDistance; }

		virtual bool HasPlayer(IPlayer* player) const { return 0; };
		virtual void AddPlayer(IPlayer* player) {}
		virtual void RemovePlayer(IPlayer* player) {}

		virtual bool IsPlayerMuted(IPlayer* player) const { return 0; }
		virtual void MutePlayer(IPlayer* player)  {}
		virtual void UnmutePlayer(IPlayer* player) {}

		virtual const std::vector<IPlayer*> GetPlayers() const { return std::vector<IPlayer*>(); }
		virtual size_t GetPlayerCount() const { return 0; }

		virtual uint32_t GetFilter() const { return 0; }
		virtual void SetFilter(uint32_t filter) {}

		virtual int32_t GetPriority() const {
			return 0;
		}
		virtual void SetPriority(int32_t priority) {}

		bool removed = false;
		alt::IBaseObject::Type type = alt::IBaseObject::Type::VOICE_CHANNEL;
		int id;
		bool spatial;
		float maxDistance;
	};
}