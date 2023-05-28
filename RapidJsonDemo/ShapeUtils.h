#pragma once

#include <vector>
#include <memory>
#include "Shapes.h"

inline bool ParseShapes(rapidjson::Value& json, std::vector<std::unique_ptr<Shape>>& shapes) {
	if (!json.IsArray()) return false;
	for (rapidjson::SizeType i = 0; i < json.Size(); i++) {
		auto& item = json[i];
		const char* typeNameStr = Shape::ParseTypeName(item);
		if (typeNameStr == nullptr) continue;
		std::string typeName = typeNameStr;
		if (typeName == ShapeTypeNameCircle) {
			auto c = std::make_unique<Circle>();
			if (c->Deserialize(item)) {
				shapes.push_back(std::move(c));
			}
		}
		else if (typeName == ShapeTypeNameSquare) {
			auto s = std::make_unique<Square>();
			if (s->Deserialize(item)) {
				shapes.push_back(std::move(s));
			}
		}
	}
	return true;
}

template <typename JsonWriter>
inline void SerializeShape(const Shape* shape, JsonWriter& writer) {
	if (shape == nullptr) {
		writer.Null();
		return;
	}
	std::string typeName = shape->GetTypeName();
	if (typeName == ShapeTypeNameCircle) {
		dynamic_cast<const Circle*>(shape)->Serialize(writer);
	}
	else if (typeName == ShapeTypeNameSquare) {
		dynamic_cast<const Square*>(shape)->Serialize(writer);
	}
}