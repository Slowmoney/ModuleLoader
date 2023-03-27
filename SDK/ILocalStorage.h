#pragma once

namespace core {

	class ILocalStorage
	{
    protected:
        virtual ~ILocalStorage() = default;

    public:
        virtual std::string Get(const std::string& key) = 0;
        virtual void Set(const std::string& key, std::string value) = 0;
        virtual void Delete(const std::string& key) = 0;
        virtual void Clear() = 0;
        virtual bool Save() = 0;
	};
}


