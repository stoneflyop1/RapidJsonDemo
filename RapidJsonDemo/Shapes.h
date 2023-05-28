#pragma once

#include "RapidJsonUtils.h"

struct Point {
	double X;
	double Y;
	bool Deserialize(rapidjson::Value& json) {
		if (!json.IsObject()) return false;
		rapidjsonutils::GetPropDouble(json, "X", X);
		rapidjsonutils::GetPropDouble(json, "Y", Y);
		return true;
	}
	rapidjson::Value ToJson(rapidjson::Document& doc) const {
		rapidjson::Value val(rapidjson::kObjectType);
		val.AddMember("X", X, doc.GetAllocator());
		val.AddMember("Y", Y, doc.GetAllocator());
		return val;
	}
	template <typename JsonWriter>
	void Serialize(JsonWriter& writer) const {
		writer.StartObject();
		writer.String("X");
		writer.Double(X);
		writer.String("Y");
		writer.Double(Y);
		writer.EndObject();
	}
};

static const char* ShapeTypeNameKey = "Type";

class Shape {
public:
	virtual const char* GetTypeName() const = 0;
	virtual bool Deserialize(rapidjson::Value& json) {
		if (!json.IsObject()) return false;
		std::string typeName;
		if (FindTypeFromJson(json, typeName)) {
			return typeName == GetTypeName();
		}
		return false;
	}
	static const char* ParseTypeName(rapidjson::Value& json) {
		if (json.HasMember(ShapeTypeNameKey) && json[ShapeTypeNameKey].IsString()) {
			return json[ShapeTypeNameKey].GetString();
		}
		return nullptr;
	}
protected:
	bool FindTypeFromJson(rapidjson::Value& json, std::string& typeName) {
		if (!json.HasMember(ShapeTypeNameKey)) return false;
		typeName = json[ShapeTypeNameKey].GetString();
		return true;
	}
	template <typename JsonWriter>
	void SerializeTypeName(JsonWriter& writer) const {
		writer.String(ShapeTypeNameKey);
		writer.String(GetTypeName());
	}
	void AddTypeNameToJsonValue(rapidjson::Value& val, rapidjson::Document& doc) const {
		rapidjson::Value tVal;
		tVal.SetString(rapidjson::StringRef(GetTypeName()));
		val.AddMember(rapidjson::StringRef(ShapeTypeNameKey), tVal, doc.GetAllocator());
	}
public:
	virtual rapidjson::Value ToJson(rapidjson::Document& doc) const = 0;
};

static const char* ShapeTypeNameCircle = "Circle";

class Circle : public Shape {
public:
	const char* GetTypeName() const override {
		return ShapeTypeNameCircle;
	}
	const Point& GetCenter() const {
		return m_center;
	}
	void SetCenter(const Point& p) {
		m_center = p;
	}
	double GetRadius() const {
		return m_radius;
	}
	void SetRadius(double r) {
		m_radius = r;
	}
	bool Deserialize(rapidjson::Value& json) override {
		if (!Shape::Deserialize(json)) return false;
		rapidjsonutils::GetPropObject(json, "center", m_center);
		rapidjsonutils::GetPropDouble(json, "radius", m_radius);
		return true;
	}
	template <typename JsonWriter>
	void Serialize(JsonWriter& writer) const {
		writer.StartObject();
		Shape::SerializeTypeName(writer);
		writer.String("center");
		m_center.Serialize(writer);
		writer.String("radius");
		writer.Double(m_radius);
		writer.EndObject();
	}
	rapidjson::Value ToJson(rapidjson::Document& doc) const override {
		rapidjson::Value val(rapidjson::kObjectType);
		AddTypeNameToJsonValue(val, doc);
		val.AddMember("center", m_center.ToJson(doc), doc.GetAllocator());
		val.AddMember("radius", m_radius, doc.GetAllocator());
		return val;
	}
private:
	Point m_center;
	double m_radius;
};

static const char* ShapeTypeNameSquare = "Square";

class Square : public Shape {
public:
	const char* GetTypeName() const override {
		return "Square";
	}
	const Point& GetCenter() const {
		return m_center;
	}
	void SetCenter(const Point& p) {
		m_center = p;
	}
	double GetSide() const {
		return m_side;
	}
	void SetSide(double s) {
		m_side = s;
	}
	bool Deserialize(rapidjson::Value& json) override {
		if (!Shape::Deserialize(json)) return false;
		rapidjsonutils::GetPropObject(json, "center", m_center);
		rapidjsonutils::GetPropDouble(json, "side", m_side);
		return true;
	}
	template <typename JsonWriter>
	void Serialize(JsonWriter& writer) const {
		writer.StartObject();
		Shape::SerializeTypeName(writer);
		writer.String("center");
		m_center.Serialize(writer);
		writer.String("side");
		writer.Double(m_side);
		writer.EndObject();
	}
	rapidjson::Value ToJson(rapidjson::Document& doc) const override {
		rapidjson::Value val(rapidjson::kObjectType);
		AddTypeNameToJsonValue(val, doc);
		val.AddMember("center", m_center.ToJson(doc), doc.GetAllocator());
		val.AddMember("side", m_side, doc.GetAllocator());
		return val;
	}
private:
	Point m_center;
	double m_side;
};