#include "../test/createTestProgram/createTestProgram.hpp"
/*
uint64_t getTime(){
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
*/

TEST(Animation, yaml) {
/*
	ui::yamlBuilderInit();
*/
	try {
		Program testProgram{"../test/tests/4-stage-animation/yaml/src/test.yaml", {200, 200}};
	} catch (...){
		ASSERT_TRUE(false);
	}
/*

	uint64_t startTime{getTime()};


	for (size_t i = 0; i < 20; ++i){
		while (static_cast<double>(getTime() - startTime)/1000 < 0.5) {}
		startTime = getTime();
		testProgram.renderTexture.clear();
		testProgram.interface->resize({200, 200}, {0, 0});
		testProgram.interface->update({0, 0}, true);
		testProgram.interface->draw();
		testProgram.renderTexture.display();

		testProgram.renderTexture.getTexture().copyToImage().saveToFile(std::to_string(i) + ".png");
		std::cout << "[=======]\n";
	}
*/
}
