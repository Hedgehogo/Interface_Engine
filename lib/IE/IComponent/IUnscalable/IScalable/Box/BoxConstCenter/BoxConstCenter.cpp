#include "BoxConstCenter.hpp"

namespace ie {
	BoxConstCenter::Make::Make(BoxPtr<IScalable::Make>&& constObject, BoxPtr<IScalable::Make>&& background, sf::Vector2f constSize, sf::Vector2f minSize) :
		constObject(std::move(constObject)), background(std::move(background)), constSize(constSize), minSize(minSize) {
	}
	
	BoxConstCenter* BoxConstCenter::Make::make(InitInfo initInfo) {
		return new BoxConstCenter{std::move(*this), initInfo};
	}
	
	BoxConstCenter::BoxConstCenter(Make&& make, InitInfo initInfo) :
		Box(make.minSize), constObject(make.constObject->make(initInfo)), background(make.background->make(initInfo)), constSize(make.constSize) {
	}
	
	BoxConstCenter::BoxConstCenter(BoxPtr<IScalable>&& constObject, BoxPtr<IScalable>&& background, const sf::Vector2f& constSize, const sf::Vector2f& minSize) :
		Box(minSize), constObject(std::move(constObject)), background(std::move(background)), constSize(constSize) {
	}
	
	void BoxConstCenter::init(InitInfo initInfo) {
		constObject->init(initInfo);
		background->init(initInfo);
	}
	
	void BoxConstCenter::setPosition(sf::Vector2f position) {
		Box::setPosition(position);
		if(resized) {
			constObject->move(constSize);
		} else {
			resized = true;
			constObject->resize(constSize, layout.position + position);
		}
		constObject->setPosition(position + (layout.size / 2.f) - (constSize / 2.f));
		background->setPosition(position);
	}
	
	void BoxConstCenter::move(sf::Vector2f position) {
		Box::move(position);
		if(resized) {
			constObject->move(constSize);
		} else {
			resized = true;
			constObject->resize(constSize, layout.position + position);
		}
		background->move(position);
	}
	
	void BoxConstCenter::setSize(sf::Vector2f size) {
		Box::setSize(size);
		if(!resized) {
			resized = true;
			constObject->setSize(constSize);
		}
		background->setSize(size);
	}
	
	void BoxConstCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		if(resized) {
			constObject->setPosition(position + (size / 2.f) - (constSize / 2.f));
		} else {
			resized = true;
			constObject->resize(constSize, position + (size / 2.f) - (constSize / 2.f));
		}
		background->resize(size, position);
	}
	
	sf::Vector2f BoxConstCenter::getMinSize() const {
		return max(ILayoutTwoObjects::getMinSize(), constSize);
	}
	
	sf::Vector2f BoxConstCenter::getNormalSize() const {
		return max(ILayoutTwoObjects::getNormalSize(), constSize);
	}
	
	IScalable& BoxConstCenter::getFirstObject() {
		return *constObject;
	}
	
	const IScalable& BoxConstCenter::getFirstObject() const {
		return *constObject;
	}
	
	IScalable& BoxConstCenter::getSecondObject() {
		return *background;
	}
	
	const IScalable& BoxConstCenter::getSecondObject() const {
		return *background;
	}
	
	bool BoxConstCenter::updateInteractions(sf::Vector2f) {
		return background->in(layout.position) ? background->updateInteractions(layout.position) : constObject->updateInteractions(layout.position);
	}
	
	BoxConstCenter* BoxConstCenter::copy() {
		return new BoxConstCenter{*this};
	}
	
	bool DecodePointer<BoxConstCenter>::decodePointer(const YAML::Node& node, BoxConstCenter*& boxWithConstCenter) {
		boxWithConstCenter = new BoxConstCenter{
			node["const-object"].as<BoxPtr<IScalable> >(),
			node["background"].as<BoxPtr<IScalable> >(),
			node["const-size"].as<sf::Vector2f>(),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}