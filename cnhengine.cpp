#include <locale> 

#include "cnhengine.h"


void CnhEngine::LoadDataValue(string_view name, string value){
	_inja.SetValue(name, value);
}
void CnhEngine::LoadDataFile(string_view file) {
	_inja.LoadJson(file);
}
vector<string> CnhEngine::RenderFile(const string& name) {

	string rendered;
	try {
		rendered = _inja.RenderFile(name);
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
	auto ss = std::stringstream(rendered);
	string line;
	getline(ss, line);
	vector<string> reply;
	while (ss) {
		std::getline(ss, line);
		reply.push_back(line);
	}
	return reply;
}

vector<tuple<fs::path, string>> CnhEngine::FindTemplates(string_view fileName) {
//	auto templateDir = fs::path("c:/work/codenowhere/extdata/");
	auto templateDir = fs::path(".");

	auto templates = vector<tuple<fs::path, string>>{};
	
	// extract file type suffix

	auto off = fileName.rfind('.');
	string suffix;
	if (off != string::npos) {
		suffix = fileName.substr(off + 1);
		for (int i = 0; i < suffix.length(); i++) {
			suffix[i] = std::tolower(suffix[i]);
		}
	}
	if (suffix.empty())
		return templates;

	for (auto const& dir_entry : fs::directory_iterator{ templateDir })
	{
		if (!dir_entry.path().string().ends_with(".tpl"))
			continue;
		//std::cout << dir_entry.path() << ":";
		auto tf = std::ifstream(dir_entry.path());

		if (tf) {
			string header;
			std::getline(tf, header);
			// quick check
			if (header.find(suffix) == string::npos || !header.starts_with("!!cnh"))
				continue;
				// parse header line
				// !!cnh {"suffix":[
				auto parsed = json::parse(header.substr(6));
				if (parsed.contains("suffix")) {
					auto head_suff = parsed["suffix"];
					if (head_suff.is_array()) {
						for (auto& sf : head_suff) {
							if (sf == suffix) {
								{
									templates.push_back({ dir_entry.path() ,"" });
								}
							}
						}
					}
					else {
						if (head_suff == suffix) {
							templates.push_back({ dir_entry.path() ,"" });
						}
					}
			}
			//std::cout << header << '\n';
		}
	}
	
	return templates;
}
