#include "sizing2.h"

namespace ui {
	Sizing2::Sizing2(Sizing *horizontal, Sizing *vertical) :
		horizontal(horizontal), vertical(vertical) {}
	
	Sizing2::Sizing2() :
		horizontal(new NormalSizeSizing{}), vertical(new NormalSizeSizing{}) {}
	
	Sizing2::Sizing2(sf::Vector2f constSize) :
		horizontal(new ConstSizing{constSize.x}), vertical(new ConstSizing{constSize.y}) {}
	
	Sizing2::Sizing2(sf::Vector2f coefficient, sf::Vector2f addition) :
		horizontal(new ParentCoefficientSizing{coefficient.x, addition.x}), vertical(new ParentCoefficientSizing{coefficient.y, addition.y}) {}
	
	Sizing2::~Sizing2() {
		delete horizontal;
		delete vertical;
	}
	
	void Sizing2::init(sf::RenderTarget &renderTarget, sf::Vector2f normalSize) {
		horizontal->init(renderTarget, normalSize.x);
		vertical->init(renderTarget, normalSize.y);
	}
	
	sf::Vector2f Sizing2::findSize(sf::Vector2f parentSize) {
		return {horizontal->findSize(parentSize.x), vertical->findSize(parentSize.y)};
	}
	
	sf::Vector2f Sizing2::operator()(sf::Vector2f parentSize) {
		return this->findSize(parentSize);
	}
	
	Sizing2 *Sizing2::copy() {
		return new Sizing2{horizontal->copy(), vertical->copy()};
	}
}