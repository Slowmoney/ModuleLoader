#pragma once
#include <SDK.h>
#include <fstream>
#include <filesystem>

namespace core {
	class Package : IPackage {
	public:
		Package(std::string root, Mode mode): root(root), mode(mode) {}

		virtual Mode GetMode() const override {
			return mode;
		};

		virtual bool FileExists(const std::string& path) override {
			const std::filesystem::path name(root + path);
			return std::filesystem::exists(name);
		};
		
		virtual File* OpenFile(const std::string& path) override {
			std::ifstream* file = new std::ifstream();
			std::string name = root + path;
			file->open(name, std::ios::binary | std::ios::ate);
			if(file->bad()) return 0;
			if (!file->is_open()) return 0;

			return (File*)file;
		};
		virtual void CloseFile(File* file) override {
			std::ifstream* fstream = (std::ifstream*)file;
			fstream->close();
		};
		
		virtual uint64_t GetFileSize(File* file) override {
			auto _file = (std::ofstream*)file;
			
			if (!_file->is_open()) return 0;
			_file->seekp(0, std::ios::end);
			
			uint64_t size = _file->tellp();
			_file->seekp(0, std::ios::beg);
			return size;
		};
		//virtual void SeekFile(File* file, uint64_t offset, SeekOrigin origin) override {};
		//virtual uint64_t TellFile(File* file) override {
		//	return 0;
		//};
		//
		virtual uint64_t ReadFile(File* file, void* buffer, uint64_t size) override {
			auto _file = (std::ifstream*)file;
			if (!_file->is_open()) return 0;
			_file->read((char *)buffer, size);
			char* saad = (char*)buffer;
			return 0;
		};
		//virtual uint64_t WriteFile(File* file, void* buffer, uint64_t size) override {
		//	return 0;
		//};

		std::string ReadConfig() {
			core::IPackage::File* file = OpenFile("resource.toml");
			std::string src(GetFileSize(file), '\0');
			ReadFile(file, src.data(), src.size());
			CloseFile(file);
			return src;
		}

		Mode mode;
		std::string root;
	};
}

