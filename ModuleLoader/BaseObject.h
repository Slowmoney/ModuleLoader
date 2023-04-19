#pragma once
#include <SDK.h>
namespace alt {
	class BaseObject: public alt::IBaseObject
	{
	public:
		std::unordered_map<std::string, MValue>* metaData = new std::unordered_map<std::string, MValue>();
		BaseObject(alt::IBaseObject::Type type, int id) : type(type), id(id) {};
		BaseObject() : type(alt::IBaseObject::Type::OBJECT) {};
		BaseObject(const BaseObject& rhs) {};
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
			metaData->insert({key, val});
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
		alt::IBaseObject::Type type;
		int id;
	};
}


