#include "boxWithConstCenter.hpp"

namespace ui {
	BoxWithConstCenter::BoxWithConstCenter(BoxPtr<IScalable>&& constObject, BoxPtr<IScalable>&& background, const sf::Vector2f& constSize, const sf::Vector2f& minSize) :
		Box(minSize), constObject(std::move(constObject)), background(std::move(background)), constSize(constSize) {
		constObject->setSize(constSize);
	}
	
	void BoxWithConstCenter::init(InitInfo initInfo) {
		constObject->init(initInfo);
		background->init(initInfo);
	}
	
	void BoxWithConstCenter::setPosition(sf::Vector2f position) {
		ILayout::setPosition(position);
		constObject->setPosition(position + (layout.size / 2.f) - (constSize / 2.f));
		background->setPosition(position);
	}
	
	void BoxWithConstCenter::move(sf::Vector2f position) {
		ILayout::move(position);
		constObject->move(position);
		background->move(position);
	}
	
	void BoxWithConstCenter::setSize(sf::Vector2f size) {
		ILayout::setSize(size);
		background->setSize(size);
	}
	
	void BoxWithConstCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		constObject->setPosition(position + (size / 2.f) - (constSize / 2.f));
		background->resize(size, position);
	}
	
	sf::Vector2f BoxWithConstCenter::getMinSize() const {
		return max(ILayoutWithTwoObjects::getMinSize(), constSize);
	}
	
	sf::Vector2f BoxWithConstCenter::getNormalSize() const {
		return max(ILayoutWithTwoObjects::getNormalSize(), constSize);
	}
	
	IScalable& BoxWithConstCenter::getFirstObject() {
		return *constObject;
	}
	
	const IScalable& BoxWithConstCenter::getFirstObject() const {
		return *constObject;
	}
	
	IScalable& BoxWithConstCenter::getSecondObject() {
		return *background;
	}
	
	const IScalable& BoxWithConstCenter::getSecondObject() const {
		return *background;
	}
	
	bool BoxWithConstCenter::updateInteractions(sf::Vector2f) {
		return background->in(layout.position) ? background->updateInteractions(layout.position) : constObject->updateInteractions(layout.position);
	}
	
	BoxWithConstCenter* BoxWithConstCenter::copy() {
		return new BoxWithConstCenter{*this};
	}
	
	bool DecodePointer<BoxWithConstCenter>::decodePointer(const YAML::Node& node, BoxWithConstCenter*& boxWithConstCenter) {
		boxWithConstCenter = new BoxWithConstCenter{
			node["const-object"].as<BoxPtr<IScalable> >(),
			node["background"].as<BoxPtr<IScalable> >(),
			node["const-size"].as<sf::Vector2f>(),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}