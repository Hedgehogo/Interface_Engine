#include "createTestProgram.hpp"

Program::Program(ui::Interface *interface, sf::Vector2u size, sf::Vector2f mousePosition) : interface(interface), renderTexture() {
	if (size == sf::Vector2u{0, 0}) {
		size = sf::Vector2u(this->interface->getNormalSize());
		if (size == sf::Vector2u{0, 0})
			size = {1, 1};
	}
    renderTexture.setSmooth(false);
    renderTexture.create(size.x, size.y);
	this->interface->init(renderTexture);
	this->interface->resize(sf::Vector2f(size), {0, 0});
	this->interface->update(mousePosition, true);
	this->interface->draw();
    renderTexture.display();
}

Program::Program(ui::IScalable *object, sf::Vector2u size, sf::Vector2f mousePosition) : Program(new ui::Interface{object}, size, mousePosition) {}

Program::Program(std::string path, sf::Vector2u size, sf::Vector2f mousePosition) : renderTexture(), interface(ui::makePrtInterface(renderTexture, path)) {
	if (size == sf::Vector2u{0, 0}) {
		size = sf::Vector2u(this->interface->getNormalSize());
		if (size == sf::Vector2u{0, 0})
			size = {1, 1};
	}
	renderTexture.setSmooth(false);
	renderTexture.create(size.x, size.y);
	this->interface->init(renderTexture);
	this->interface->resize((sf::Vector2f)size, {0, 0});
	this->interface->update(mousePosition, true);
	this->interface->draw();
	renderTexture.display();
}

Program::~Program() {
	delete interface;
}

bool operator==(const sf::Texture &texture1, const sf::Texture &texture2) {
    if (texture1.getSize() != texture2.getSize()) return false;

    sf::Image image1{texture1.copyToImage()};
    sf::Image image2{texture2.copyToImage()};

    for (int x = 0; x < texture1.getSize().x; ++x) {
        for (int y = 0; y < texture1.getSize().y; ++y) {
            if (image1.getPixel(x, y) != image2.getPixel(x, y)) return false;
        }
    }
    return true;
}