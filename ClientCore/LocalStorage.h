#pragma once
//#include <SDK.h>
//#include <iostream>
//#include <map>
//namespace core {
//	class LocalStorage : public ILocalStorage {
//	public:
//		LocalStorage() {};
//		std::map<std::string, std::string>* storage = new std::map < std::string, std::string>();
//		virtual std::string Get(const std::string& key) override {
//			std::cout << "get" << std::endl;
//
//			try
//			{
//				return storage->at(key);
//			}
//			catch (const std::exception&)
//			{
//				return "none";
//			}
//		};
//		virtual void Set(const std::string& key, std::string value)override {
//			std::cout << "Set" << std::endl;
//			storage->insert(std::pair<std::string, std::string>(key, value));
//		};
//		virtual void Delete(const std::string& key) override {
//			std::cout << "Delete" << std::endl;
//			storage->erase(key);
//		};
//		virtual void Clear() override {
//			std::cout << "Clear" << std::endl;
//			storage->clear();
//		};
//		virtual bool Save() override {
//			std::cout << "Save";
//			std::cout << std::endl;
//			for (auto it = storage->begin(); it != storage->end(); ++it)
//				std::cout << it->first << " => " << it->second << '\n';
//
//			return true;
//		};
//		virtual ~LocalStorage() override {
//			std::cout << "~LocalStorage" << std::endl;
//		};
//	};
//};

