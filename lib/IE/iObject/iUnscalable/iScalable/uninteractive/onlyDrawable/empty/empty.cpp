#include "empty.hpp"

namespace ui {
	Empty* Empty::Make::make(InitInfo initInfo) {
		return new Empty{std::move(*this), initInfo};
	}
	
	Empty::Empty(Make&&, InitInfo initInfo) : OnlyDrawable(initInfo) {
	}
	
	Empty::Empty() {
	}
	
	void Empty::draw() {
	}
	
	void Empty::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
	}
	
	bool Empty::updateInteractions(sf::Vector2f) {
		return false;
	}
	
	sf::Vector2f Empty::getMinSize() const {
		return {};
	}
	
	sf::Vector2f Empty::getNormalSize() const {
		return {};
	}
	
	Empty* Empty::copy() {
		return new Empty{*this};
	}
	
	void Empty::drawDebug(sf::RenderTarget&, int, int, uint, uint) {
	}
	
	LayoutData& Empty::layoutGetData() {
		return layout;
	}
	
	const LayoutData& Empty::layoutGetData() const {
		return layout;
	}
	
	bool DecodePointer<Empty>::decodePointer(const YAML::Node&, Empty*& empty) {
		empty = new Empty{};
		return true;
	}
}
