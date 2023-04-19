#pragma once
#include <SDK.h>
namespace alt {
	class ColShape : public alt::IColShape
	{
		std::unordered_map<std::string, MValue>* metaData = new std::unordered_map<std::string, MValue>();
	public:
		ColShape(int id, alt::IColShape::ColShapeType colshapeType) : id(id), colshapeType(colshapeType) {}
		virtual alt::IBaseObject::Type GetType() const override {
			return alt::IBaseObject::Type::COLSHAPE;
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

		bool removed = false;
		alt::IBaseObject::Type type = alt::IBaseObject::Type::COLSHAPE;
		int id;


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
		Position pos;
		int32_t dimension = 0;


		virtual ColShapeType GetColshapeType() const {
			return colshapeType;
		}

		virtual bool IsEntityIn(IEntity* ent) const {
			return false;
		}
		virtual bool IsEntityIdIn(uint16_t id) const {
			return false;
		}
		virtual bool IsPointIn(Position p) const {
			return false;
		}
		virtual void SetPlayersOnly(bool state) {
		
		}
		virtual bool IsPlayersOnly() const {
			return false;
		}

		alt::IColShape::ColShapeType colshapeType;
	};
}