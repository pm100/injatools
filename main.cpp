#include "cnhengine.h"

int main(int argc, char** argv) {
	if (argc != 2)
		exit(1);
	
	CnhEngine engine;
	auto templates = engine.FindTemplates(argv[1]);
	engine.LoadDataFile("data.json");
	engine.LoadDataValue("cnh_date", "Tue Mar 28 20:48:22 2023");
	engine.LoadDataValue("cnh_file", argv[1]);
	engine.LoadDataValue("cnh_name", "paulm");
	auto result = engine.RenderFile(std::get<0>(templates[0]).string());

	for (auto& line : result) {
		std::cout << line << "\n";
	}
}