#pragma once
#include <string>
#include <string_view>
#include "inja.hpp"
using json = nlohmann::json;
//using namespace inja;
using std::string;
using std::string_view;
class InjaWrap {
	inja::Environment _env;
	json _data;

public:
	InjaWrap();
	void LoadJson(string_view fileName);
	void SetValue(string_view naem, string value);
	string RenderFile(const string& file);

};
