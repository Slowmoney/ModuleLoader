#pragma once
#include <SDK.h>
namespace core {
	class Package : IPackage {
		Package(){}

		//virtual Mode GetMode() const override {
		//	return Mode::READ;
		//};
		//
		//virtual bool FileExists(const std::string& path) override {};
		//
		//virtual File* OpenFile(const std::string& path) override {
		//	return (File*)0;
		//};
		//virtual void CloseFile(File* file) override {};
		//
		//virtual uint64_t GetFileSize(File* file) override {
		//	return 0;
		//};
		//virtual void SeekFile(File* file, uint64_t offset, SeekOrigin origin) override {};
		//virtual uint64_t TellFile(File* file) override {
		//	return 0;
		//};
		//
		//virtual uint64_t ReadFile(File* file, void* buffer, uint64_t size) override {
		//	return 0;
		//};
		//virtual uint64_t WriteFile(File* file, void* buffer, uint64_t size) override {
		//	return 0;
		//};
	};
}

