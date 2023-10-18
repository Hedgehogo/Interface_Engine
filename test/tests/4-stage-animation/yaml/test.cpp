#include "../test/create_test_program/create_test_program.hpp"
/*
uint64_t get_time(){
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
*/

TEST(Animation, yaml) {
/*
	ie::yaml_builder_init();
*/
	try {
		Program test_program{"../test/tests/4-stage-Animation/yaml/src/test.yaml", {200, 200}};
	} catch (...){
		ASSERT_TRUE(false);
	}
/*

	uint64_t start_time{get_time()};


	for (size_t i = 0; i < 20; ++i){
		while (static_cast<double>(get_time() - start_time)/1000 < 0.5) {}
		start_time = get_time();
		test_program.render_texture.clear();
		test_program.interface->resize({200, 200}, {0, 0});
		test_program.interface->update({0, 0}, true);
		test_program.interface->draw();
		test_program.render_texture.display();

		test_program.render_texture.getTexture().copyToImage().saveToFile(std::to_string(i) + ".png");
		std::cout << "[=======]\n";
	}
*/
}
