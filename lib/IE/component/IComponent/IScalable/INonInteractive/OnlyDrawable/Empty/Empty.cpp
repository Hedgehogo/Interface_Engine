#include "Empty.hpp"

namespace ie {
	auto Empty::Make::make(InitInfo init_info) -> Empty* {
		return new Empty{std::move(*this), init_info};
	}
	
	Empty::Empty(Make&&, InitInfo init_info) : OnlyDrawable(init_info) {
	}
	
	Empty::Empty() {
	}
	
	auto Empty::draw() -> void {
	}
	
	auto Empty::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
	}
	
	auto Empty::update_interactions(sf::Vector2f) -> bool {
		return false;
	}
	
	auto Empty::get_min_size() const -> sf::Vector2f {
		return {};
	}
	
	auto Empty::get_normal_size() const -> sf::Vector2f {
		return {};
	}
	
	auto Empty::draw_debug(sf::RenderTarget&, int, int, size_t, size_t) -> void {
	}
	
	auto Empty::layout_get_data() -> LayoutData& {
		return layout_;
	}
	
	auto Empty::layout_get_data() const -> LayoutData const& {
		return layout_;
	}
}

auto ieml::Decode<char, ie::Empty::Make>::decode(ieml::Node const&) -> orl::Option<ie::Empty::Make> {
	return {{}};
}
