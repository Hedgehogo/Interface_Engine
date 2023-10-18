#include "create_test_program.hpp"

Program::Program(ie::Interface* interface, sf::Vector2u size, sf::Vector2f mouse_position) : interface(interface), render_texture() {
	if(size == sf::Vector2u{0, 0}) {
		size = sf::Vector2u(this->interface->get_normal_size());
		if(size == sf::Vector2u{0, 0})
			size = {1, 1};
	}
	render_texture.set_smooth(false);
	render_texture.create(size.x, size.y);
	this->interface->init(render_texture);
	this->interface->resize(sf::Vector2f(size), {0, 0});
	this->interface->update(mouse_position, true);
	this->interface->draw();
	render_texture.display();
}

Program::Program(ie::IScalable* object, sf::Vector2u size, sf::Vector2f mouse_position) : Program(new ie::Interface{object}, size, mouse_position) {
}

Program::Program(std::string path, sf::Vector2u size, sf::Vector2f mouse_position) : render_texture(), interface(ie::make_prt_interface(render_texture, path)) {
	if(size == sf::Vector2u{0, 0}) {
		size = sf::Vector2u(this->interface->get_normal_size());
		if(size == sf::Vector2u{0, 0})
			size = {1, 1};
	}
	render_texture.set_smooth(false);
	render_texture.create(size.x, size.y);
	this->interface->init(render_texture);
	this->interface->resize((sf::Vector2f)size, {0, 0});
	this->interface->update(mouse_position, true);
	this->interface->draw();
	render_texture.display();
}

Program::~Program() {
	delete interface;
}

bool operator==(const sf::Texture& texture1, const sf::Texture& texture2) {
	if(texture1.get_size() != texture2.get_size())
		return false;
	
	sf::Image image1{texture1.copyToImage()};
	sf::Image image2{texture2.copyToImage()};
	
	for(std::size_t x = 0; x < texture1.get_size().x; ++x) {
		for(std::size_t y = 0; y < texture1.get_size().y; ++y) {
			if(image1.get_pixel(x, y) != image2.get_pixel(x, y))
				return false;
		}
	}
	return true;
}