#pragma once

#include <string>
#include <rapidjson/document.h>

template <typename T> 
concept DeserializableObject = requires (T t, rapidjson::Value& json) {
	t.Deserialize(json);
};

namespace rapidjsonutils {

	inline bool GetPropString(rapidjson::Value& json, const char* propName, std::string& val) {
		if (!json.HasMember(propName) || json[propName].IsString()) return false;
		val = json[propName].GetString();
		return true;
	}

	inline bool GetPropDouble(rapidjson::Value& json, const char* propName, double& val) {
		if (!json.HasMember(propName)) return false;
		if (json[propName].IsDouble() || json[propName].IsInt64()) {
			val = json[propName].GetDouble();
			return true;
		}
		return false;
	}

	template <typename TObject> requires DeserializableObject<TObject>
	bool GetPropObject(rapidjson::Value& json, const char* propName, TObject& obj) {
		if (!json.HasMember(propName)) return false;
		return obj.Deserialize(json[propName]);
	}
}

