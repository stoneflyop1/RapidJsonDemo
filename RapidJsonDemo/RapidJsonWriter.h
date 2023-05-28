// RapidJsonDemo.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <rapidjson/prettywriter.h>

template <typename TObject>
std::string SerializeObject(const TObject& obj) {
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	obj.Serialize(writer);
	return buffer.GetString();
}

template <typename TObject>
std::string SerializeObjectPretty(const TObject& obj) {
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	obj.Serialize(writer);
	return buffer.GetString();
}