#include "Empty.hpp"

namespace ie {
	Empty* Empty::Make::make(InitInfo init_info) {
		return new Empty{std::move(*this), init_info};
	}
	
	Empty::Empty(Make&&, InitInfo init_info) : OnlyDrawable(init_info) {
	}
	
	Empty::Empty() {
	}
	
	void Empty::draw() {
	}
	
	void Empty::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
	}
	
	bool Empty::update_interactions(sf::Vector2f) {
		return false;
	}
	
	sf::Vector2f Empty::get_min_size() const {
		return {};
	}
	
	sf::Vector2f Empty::get_normal_size() const {
		return {};
	}
	
	Empty* Empty::copy() {
		return new Empty{*this};
	}
	
	void Empty::draw_debug(sf::RenderTarget&, int, int, uint, uint) {
	}
	
	LayoutData& Empty::layout_get_data() {
		return layout;
	}
	
	const LayoutData& Empty::layout_get_data() const {
		return layout;
	}
	
	bool DecodePointer<Empty>::decode_pointer(const YAML::Node&, Empty*& empty) {
		empty = new Empty{};
		return true;
	}
}
