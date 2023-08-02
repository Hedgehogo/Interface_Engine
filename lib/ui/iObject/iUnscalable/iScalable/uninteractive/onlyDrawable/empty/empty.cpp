#include "empty.hpp"

namespace ui {
	Empty::Empty() {
	}
	
	void Empty::draw() {
	}
	
	void Empty::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayout::resize(size, position);
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
	
	void Empty::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
	}
	
	LayoutData& Empty::getLayoutData() {
		return layout;
	}
	
	const LayoutData& Empty::getLayoutData() const {
		return layout;
	}
	
	bool DecodePointer<Empty>::decodePointer(const YAML::Node& node, Empty*& empty) {
		empty = new Empty{};
		return true;
	}
}
