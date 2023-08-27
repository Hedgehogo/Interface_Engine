#include "InitInfoData.hpp"

InitInfoData::InitInfoData(sf::Vector2u size) {
	renderTarget.create(size.x, size.y);
	renderTarget.clear(sf::Color::Transparent);
}

ie::InitInfo InitInfoData::makeInitInfo() {
	return ie::InitInfo{
		window,
		renderTarget,
		drawManager,
		updateManager,
		interactionManager,
		interactionStack,
		panelManager
	};
}

void InitInfoData::renderSave(std::filesystem::path path) {
	renderTarget.getTexture().copyToImage().saveToFile(path.string());
}

bool InitInfoData::renderEqual(std::filesystem::path path) {
	renderTarget.display();
	sf::Image second{};
	second.loadFromFile(path.make_preferred().lexically_normal().string());
	return imageEqual(renderTarget.getTexture().copyToImage(), second);
}

bool InitInfoData::renderEqualWithSave(std::filesystem::path path) {
	renderTarget.display();
	
	auto filePath{path.make_preferred().lexically_normal()};
	sf::Image first{renderTarget.getTexture().copyToImage()};
	sf::Image second{};
	second.loadFromFile(filePath.string());
	
	if(!imageEqual(first, second)) {
		auto filename = path.filename();
		auto directory = path.remove_filename() / std::filesystem::path{"tmp"};
		std::filesystem::create_directories(directory);
		path = directory / filename;
		first.saveToFile(path.string());
		return false;
	}
	return true;
}
