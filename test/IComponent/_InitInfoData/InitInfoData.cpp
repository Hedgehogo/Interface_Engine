#include "InitInfoData.hpp"
#include "_image_difference/image_difference.hpp"

InitInfoData::InitInfoData(sf::Vector2u size) {
	render_target.create(size.x, size.y);
	render_target.clear(sf::Color::Transparent);
}

ie::InitInfo InitInfoData::make_init_info() {
	return ie::InitInfo{
		window,
		render_target,
		dyn_buffer,
		event_handler,
		draw_manager,
		update_manager,
		interaction_manager,
		panel_manager
	};
}

void InitInfoData::render_save(std::filesystem::path path) {
	render_target.getTexture().copyToImage().saveToFile(path.string());
}

bool InitInfoData::render_equal(std::filesystem::path path, float precision) {
	render_target.display();
	sf::Image second{};
	second.loadFromFile(path.make_preferred().lexically_normal().string());
	return image_equal(render_target.getTexture().copyToImage(), second, precision);
}

bool InitInfoData::render_equal_with_save(std::filesystem::path path, float precision) {
	render_target.display();
	
	auto file_path{path.make_preferred().lexically_normal()};
	sf::Image first{render_target.getTexture().copyToImage()};
	sf::Image second{};
	second.loadFromFile(file_path.string());
	
	if(!image_equal(first, second, precision)) {
		auto filename = path.filename();
		auto directory = path.remove_filename() / std::filesystem::path{"tmp"};
		std::filesystem::create_directories(directory);
		path = directory / filename;
		first.saveToFile(path.string());
		path = directory / std::filesystem::path{"_" + filename.string()};
		image_difference(first, second).saveToFile(path.string());
		return false;
	}
	return true;
}
