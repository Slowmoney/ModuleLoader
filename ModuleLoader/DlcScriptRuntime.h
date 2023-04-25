#pragma once
#include <SDK.h>

struct DlcFile {
	std::string fullPath;
	std::string fullName;
	std::string name;
	std::string ext;
};

uint64_t ntohl(uint64_t net) {
	uint8_t data[sizeof(net)] = {};
	memcpy(&data, &net, sizeof(data));

	return ((uint64_t)data[7] << 0)
		| ((uint64_t)data[6] << 8)
		| ((uint64_t)data[5] << 16)
		| ((uint64_t)data[4] << 24)
		| ((uint64_t)data[3] << 32)
		| ((uint64_t)data[2] << 40)
		| ((uint64_t)data[1] << 48)
		| ((uint64_t)data[0] << 56);
}
int64_t ntohl(int64_t net) {
	uint8_t data[sizeof(net)] = {};
	memcpy(&data, &net, sizeof(data));

	return ((int64_t)data[7] << 0)
		| ((int64_t)data[6] << 8)
		| ((int64_t)data[5] << 16)
		| ((int64_t)data[4] << 24)
		| ((int64_t)data[3] << 32)
		| ((int64_t)data[2] << 40)
		| ((int64_t)data[1] << 48)
		| ((int64_t)data[0] << 56);
}
int32_t ntohl(int32_t net) {
	uint8_t data[sizeof(net)] = {};
	memcpy(&data, &net, sizeof(data));

	return ((int32_t)data[3] << 0)
		| ((int32_t)data[2] << 8)
		| ((int32_t)data[1] << 16)
		| ((int32_t)data[0] << 24);
}
uint32_t ntohl(uint32_t net) {
	uint8_t data[sizeof(net)] = {};
	memcpy(&data, &net, sizeof(data));

	return ((uint32_t)data[3] << 0)
		| ((uint32_t)data[2] << 8)
		| ((uint32_t)data[1] << 16)
		| ((uint32_t)data[0] << 24);
}
int16_t ntohl(int16_t net) {
	uint8_t data[sizeof(net)] = {};
	memcpy(&data, &net, sizeof(data));
	return ((int16_t)data[1] << 0)
		| ((int16_t)data[0] << 8);
}

uint16_t ntohl(uint16_t net) {
	uint8_t data[sizeof(net)] = {};
	memcpy(&data, &net, sizeof(data));
	return ((uint16_t)data[1] << 0)
		| ((uint16_t)data[0] << 8);
}

struct ResourcePagesInfo {
	uint32_t Unknown_0h;
	uint32_t Unknown_4h;
	int8_t SystemPagesCount;
	int8_t GraphicsPagesCount;
	uint16_t Unknown_Ah;
	uint32_t Unknown_Ch;
	uint32_t Unknown_10h;

	void Read(std::ifstream* stream) {
		//stream->read((char*)&Unknown_0h, sizeof(Unknown_0h));
		//Unknown_0h = ntohl(Unknown_0h);
		//stream->read((char*)&Unknown_4h, sizeof(Unknown_4h));
		//Unknown_4h = ntohl(Unknown_4h);
		//stream->read((char*)&SystemPagesCount, sizeof(SystemPagesCount));
		//SystemPagesCount = ntohl(SystemPagesCount);
		//stream->read((char*)&GraphicsPagesCount, sizeof(GraphicsPagesCount));
		//GraphicsPagesCount = ntohl(GraphicsPagesCount);
		//stream->read((char*)&Unknown_Ah, sizeof(Unknown_Ah));
		//Unknown_Ah = ntohl(Unknown_Ah);
		//stream->read((char*)&Unknown_Ch, sizeof(Unknown_Ch));
		//Unknown_Ch = ntohl(Unknown_Ch);
		//stream->read((char*)&Unknown_10h, sizeof(Unknown_10h));
		//Unknown_10h = ntohl(Unknown_10h);
	}
};

struct ResourceFileBase {
    uint32_t FileVFT;
	uint32_t FileUnknown;
	uint64_t FilePagesInfoPointer;
	ResourcePagesInfo FilePagesInfo;

	void Read(std::ifstream* stream) {
		stream->read((char*)&FileVFT, sizeof(FileVFT));
		FileVFT = ntohl(FileVFT);

		stream->read((char*)&FileUnknown, sizeof(FileUnknown));
		FileUnknown = ntohl(FileUnknown);

		stream->read((char*)&FilePagesInfoPointer, sizeof(FilePagesInfoPointer));
		FilePagesInfoPointer = ntohl(FilePagesInfoPointer);
		this->FilePagesInfo.Read(stream);
	}
};


struct Meta: ResourceFileBase {
	int32_t Unknown_10h;
	int16_t Unknown_14h;
	int8_t HasEncryptedStrings;
	int8_t Unknown_17h;
	int32_t Unknown_18h;
	int32_t RootBlockIndex;
	int64_t StructureInfosPointer;
	int64_t EnumInfosPointer;
	int64_t DataBlocksPointer;
	int64_t NamePointer;
	int64_t EncryptedStringsPointer;
	int16_t StructureInfosCount;
	int16_t EnumInfosCount;
	int16_t DataBlocksCount;
	int16_t Unknown_4Eh;
	uint32_t Unknown_50h;
	uint32_t Unknown_54h;
	uint32_t Unknown_58h;
	uint32_t Unknown_5Ch;
	uint32_t Unknown_60h;
	uint32_t Unknown_64h;
	uint32_t Unknown_68h;
	uint32_t Unknown_6Ch;
	void Read(std::ifstream* stream) {
		ResourceFileBase::Read(stream);
		stream->read((char*)&Unknown_10h, sizeof(Unknown_10h));
		Unknown_10h = ntohl(Unknown_10h);
		stream->read((char*)&Unknown_14h, sizeof(Unknown_14h));
		Unknown_14h = ntohl(Unknown_14h);
		stream->read((char*)&HasEncryptedStrings, sizeof(HasEncryptedStrings));
		//meta.HasEncryptedStrings = ntohl(meta.HasEncryptedStrings);
		stream->read((char*)&Unknown_17h, sizeof(Unknown_17h));
		//meta.Unknown_17h = ntohl(meta.Unknown_17h);
		stream->read((char*)&Unknown_18h, sizeof(Unknown_18h));
		Unknown_18h = ntohl(Unknown_18h);

		stream->read((char*)&RootBlockIndex, sizeof(RootBlockIndex));
		RootBlockIndex = ntohl(RootBlockIndex);
		stream->read((char*)&StructureInfosPointer, sizeof(StructureInfosPointer));
		StructureInfosPointer = ntohl(StructureInfosPointer);
		stream->read((char*)&EnumInfosPointer, sizeof(EnumInfosPointer));
		EnumInfosPointer = ntohl(EnumInfosPointer);
		stream->read((char*)&DataBlocksPointer, sizeof(DataBlocksPointer));
		DataBlocksPointer = ntohl(DataBlocksPointer);
		stream->read((char*)&NamePointer, sizeof(NamePointer));
		NamePointer = ntohl(NamePointer);

		stream->read((char*)&EncryptedStringsPointer, sizeof(EncryptedStringsPointer));
		EncryptedStringsPointer = ntohl(EncryptedStringsPointer);
		stream->read((char*)&StructureInfosCount, sizeof(StructureInfosCount));
		StructureInfosCount = ntohl(StructureInfosCount);
		stream->read((char*)&EnumInfosCount, sizeof(EnumInfosCount));
		EnumInfosCount = ntohl(EnumInfosCount);
		stream->read((char*)&DataBlocksCount, sizeof(DataBlocksCount));
		DataBlocksCount = ntohl(DataBlocksCount);
		stream->read((char*)&Unknown_4Eh, sizeof(Unknown_4Eh));
		Unknown_4Eh = ntohl(Unknown_4Eh);
		stream->read((char*)&Unknown_50h, sizeof(Unknown_50h));
		Unknown_50h = ntohl(Unknown_50h);
		stream->read((char*)&Unknown_54h, sizeof(Unknown_54h));
		Unknown_54h = ntohl(Unknown_54h);
		stream->read((char*)&Unknown_58h, sizeof(Unknown_58h));
		Unknown_58h = ntohl(Unknown_58h);
		stream->read((char*)&Unknown_5Ch, sizeof(Unknown_5Ch));
		Unknown_5Ch = ntohl(Unknown_5Ch);
		stream->read((char*)&Unknown_60h, sizeof(Unknown_60h));
		Unknown_60h = ntohl(Unknown_60h);
		stream->read((char*)&Unknown_64h, sizeof(Unknown_64h));
		Unknown_64h = ntohl(Unknown_64h);
		stream->read((char*)&Unknown_68h, sizeof(Unknown_68h));
		Unknown_68h = ntohl(Unknown_68h);
		stream->read((char*)&Unknown_6Ch, sizeof(Unknown_6Ch));
		Unknown_6Ch = ntohl(Unknown_6Ch);
	}
};
struct MetaStructureInfo {
	uint16_t StructureNameHash;
	uint16_t StructureKey;
	uint16_t Unknown_8h;
	uint16_t Unknown_Ch;
	uint64_t EntriesPointer;
	int StructureSize;
	int16_t Unknown_1Ch;
	int16_t EntriesCount;
	void Read(std::ifstream* stream) {

	}
};
#define SWAP_INT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))
namespace alt {
	class DlcIResourceImpl : public IResource::Impl {
		const enum FileType : int
		{
			PSIN = 0x5053494E,
			PMAP = 0x504D4150,
			PSCH = 0x50534348,
			PSIG = 0x50534947,
			STRF = 0x53545246,
			STRS = 0x53545253,
			STRE = 0x53545245,
			CHKS = 0x43484B53,
			RSC7 = 0x52534337
		};
		std::vector<DlcFile> dlcFiles;
	public:
		DlcIResourceImpl(alt::IResource* resource) : resource(resource) {}
		virtual bool Start() {
			auto main = resource->GetMain();
			auto pkg = resource->GetPackage();
			auto mainFile = pkg->OpenFile(main);
			auto size = pkg->GetFileSize(mainFile);

			std::string src(pkg->GetFileSize(mainFile), '\0');
			pkg->ReadFile(mainFile, src.data(), src.size());
			pkg->CloseFile(mainFile);


			auto config = LoadConfig(src);
			auto files = config->Get("files")->AsList();

			for (auto& file : files) {
				auto fileName = file->AsString();
				std::replace(fileName.begin(), fileName.end(), '*', '\0');
				auto fn = resource->GetPath() + "\\" + fileName;

				auto path = std::filesystem::path(fn).lexically_normal();
				path = std::filesystem::canonical(path);
				auto di = std::filesystem::recursive_directory_iterator(path);

				for (auto& dir : di) {

					auto path = dir.path();
					auto fullName = path.filename();
					auto ext = fullName.extension();
					auto name = fullName.filename().replace_extension();
					std::cout << path << std::endl;

					dlcFiles.push_back({ path.string(), fullName.string(), name.string(), ext.string() });
				}
			}
			for (auto& dir : dlcFiles) {
				this->ReadFile(dir);
			}
			return true;
		}

		void ReadFile(DlcFile dlcFile) {
			std::ifstream* file = new std::ifstream();
			file->open(dlcFile.fullPath);

			auto size = GetFileSize(file);



			//std::vector<char> buffer;

			//buffer.insert(buffer.begin(),
				//std::istream_iterator<char>(*file),
				//std::istream_iterator<char>());
			
			
			//ReadFile(file, buffer.data(), size);


			FileType type;
			file->read((char*)&type, sizeof(FileType));
			type = static_cast<FileType>(ntohl(type));
			std::cout << "LOAD DLC: " << std::hex << (int)type << std::endl;
			if (type == FileType::RSC7) {
			
			    ((std::ofstream*)file)->seekp(0, std::ios::beg);
				Meta meta{};
				auto stream = file;
				//std::istream
				//std::istream stream(buffer.data(), buffer.size());
				meta.Read(stream);
				
				auto p = stream->tellg();
				std::cout << "LOAD DLC RSC7: " << std::hex << (int)type << std::endl;
			}
			file->close();


			//
			//auto PMAP = memchr(buffer, (int)FileType::PMAP, sizeof(int));
			//if (PMAP) {
			//
			//}
		}

		FileType ReadType(std::vector<char> buffer) {
			return static_cast<FileType>(buffer.at(0) << 24 | buffer.at(1) << 16 | buffer.at(2) << 8 | buffer.at(3) << 0);
		}

		uint64_t ReadFile(std::ifstream* file, void* buffer, uint64_t size) {
			auto _file = (std::ifstream*)file;
			if (!_file->is_open()) return 0;
			_file->read((char*)buffer, size);
			return 0;
		};

		uint64_t GetFileSize(std::ifstream* file) {
			auto _file = (std::ofstream*)file;

			if (!_file->is_open()) return 0;
			_file->seekp(0, std::ios::end);

			uint64_t size = _file->tellp();
			_file->seekp(0, std::ios::beg);
			return size;
		};

		Config::Value::ValuePtr LoadConfig(const std::string& cfgString) {
			std::string errr = "";
			auto cfg = Config::ConfigBase<TomlConfig>().Parse(cfgString, errr);
			if (errr.size()) {
				std::cout << errr;
			}
			return cfg;
		}
		alt::IResource* resource;
	};

	class DlcScriptRuntime : public alt::IScriptRuntime {
	public:
		DlcScriptRuntime() = default;
		std::unordered_set<DlcIResourceImpl*> resources;
		void OnTick() override {
			//std::cout << "TestScriptRuntime tick" << std::endl;
		};

		void DestroyImpl(alt::IResource::Impl* impl) override
		{
			auto res = static_cast<DlcIResourceImpl*>(impl);
			resources.erase(res);
			delete res;
		}

		void OnDispose() override {
			delete this;
		}

		alt::IResource::Impl* CreateImpl(alt::IResource* resource)
		{
			auto res = new DlcIResourceImpl(resource);
			resources.insert(res);
			return res;
		}

		static DlcScriptRuntime& Instance()
		{
			static DlcScriptRuntime _Instance;
			return _Instance;
		}
	};
}


