#pragma once
#include <string>
#include <iostream>
#include <deps/ConfigBase.h>
#include <toml11-3.7.1/toml.hpp>
using namespace toml::literals::toml_literals;

class TomlConfig
{
public:
	static Config::Value::ValuePtr Parse(const std::string& input, std::string& error) {
		const char* str = input.c_str();
		std::size_t len = input.length();
		::toml::detail::location loc(
			std::string("TOML literal encoded in a C++ code"),
			std::vector<char>(str, str + len));
		auto value = toml::literals::toml_literals::literal_internal_impl(loc);
		TomlConfig* config = new TomlConfig(value);

		return config->rootValue;
	}

	TomlConfig(toml::value root): root(root) {
		rootValue = ParseTomlPrimitive(root);
	}

	Config::Value::ValuePtr ParseTomlDict(std::unordered_map<toml::key, toml::value> dict) {
		Config::Value::Dict* dict1 = new Config::Value::Dict();
		for (auto it = dict.begin(); it != dict.end(); ++it) {
			auto value = ParseTomlPrimitive(it->second);
			dict1->insert({ it->first, value });
		}
		return Config::internal::ValueWrapper<Config::Value>(*dict1);
	}

	Config::Value::ValuePtr ParseTomlArray(std::vector<toml::value> arr) {
		Config::Value::List* root = new Config::Value::List(arr.size());
		auto list = Config::Value(*root);
		for (std::vector<toml::value>::size_type i = 0; i != arr.size(); i++) {
			Config::Value::ValuePtr value = ParseTomlPrimitive(arr[i]);
			list.Set(i, value);
		}
		return list.AsList();
	}

	Config::Value::ValuePtr ParseTomlPrimitive(toml::value value) {
		if (value.type() == toml::value_t::string) {
			const std::string sadd(value.as_string().str);
			return Config::internal::ValueWrapper<Config::Value>(sadd);
		}
		else if (value.type() == toml::value_t::table) {
			return ParseTomlDict(value.as_table());
		}
		else if (value.type() == toml::value_t::array) {
			return ParseTomlArray(value.as_array());
		}
		throw "invalid parse";
	}
	toml::value root;
	Config::Value::ValuePtr rootValue;
};

