﻿// RapidJsonDemo.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "Shapes.h"
#include "ShapeUtils.h"
#include "RapidJsonWriter.h"

using namespace std;

void TestPnt() {
	std::string pntJson = "{\"pnt\":{\"X\":1,\"Y\":2.0}}";
	rapidjson::Document doc;
	if (doc.Parse(pntJson).HasParseError()) {
		return;
	}
	Point p;
	rapidjsonutils::GetPropObject(doc, "pnt", p);

	std::cout << SerializeObject(p) << std::endl;

	std::cout << SerializeObjectPretty(p) << std::endl;
}

void TestShapes() {
	std::vector<std::unique_ptr<Shape>> shapes;
	auto c = std::make_unique<Circle>();
	c->SetCenter(Point{ 0.0, 0 });
	c->SetRadius(100);
	shapes.push_back(std::move(c));
	auto s = std::make_unique<Square>();
	s->SetCenter(Point{ 100.0,100 });
	s->SetSide(10);
	shapes.push_back(std::move(s));

	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	writer.StartArray();
	for (auto& s : shapes) {
		SerializeShape(s.get(), writer);
	}
	writer.EndArray();
	std::string json = buffer.GetString();
	std::cout << json << std::endl;
	shapes.clear();


	rapidjson::Document doc;
	doc.Parse(json);

	ParseShapes(doc, shapes);
	std::cout << shapes.size() << std::endl;
}

int main()
{
	cout << "Hello CMake." << endl;
	TestPnt();
	TestShapes();
	return 0;
}
