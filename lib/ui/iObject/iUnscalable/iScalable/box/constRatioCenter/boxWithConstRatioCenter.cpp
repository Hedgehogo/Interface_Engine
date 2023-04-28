#include "boxWithConstRatioCenter.hpp"

namespace ui {
	BoxWithConstRatioCenter::BoxWithConstRatioCenter(IScalable *object, IUninteractive *background, float aspectRatio, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObject(object), LayoutWithBackground(background), LayoutWithTwoObjects(new Empty, new Empty), aspectRatio(aspectRatio) {
	}
	
	BoxWithConstRatioCenter::BoxWithConstRatioCenter(IScalable *object, IScalable *firstObject, IScalable *secondObject, IUninteractive *background, float aspectRatio, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObject(object), LayoutWithBackground(background), LayoutWithTwoObjects(firstObject, secondObject), aspectRatio(aspectRatio) {
	}
	
	void BoxWithConstRatioCenter::init(InitInfo initInfo) {
		background->init(initInfo);
		object->init(initInfo);
		initInfo.drawManager.add(*this);
		firstObject->init(initInfo.copy(this->firstDrawManager));
		secondObject->init(initInfo.copy(this->secondDrawManager));
	}
	
	void BoxWithConstRatioCenter::setAspectRatio(float aspectRatio) {
		this->aspectRatio = aspectRatio;
		this->setPosition(position);
	}
	
	void BoxWithConstRatioCenter::draw() {
		if(renderFirst)
			firstDrawManager.draw();
		if(renderSecond)
			secondDrawManager.draw();
	}
	
	void BoxWithConstRatioCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		
		sf::Vector2f firstMinSize{firstObject->getMinSize()};
		sf::Vector2f secondMinSize{secondObject->getMinSize()};
		sf::Vector2f secondPosition{position};
		sf::Vector2f objectsSize{size};
		
		background->resize(size, position);
		float sizeAspectRatio = size.x / size.y;
		if(sizeAspectRatio > aspectRatio) {
			size.x = size.y * aspectRatio;
			objectsSize.x = (this->size.x - size.x) / 2.0f;
			secondPosition.x += objectsSize.x + size.x;
		} else {
			size.y = size.x / aspectRatio;
			objectsSize.y = (this->size.y - size.y) / 2.0f;
			secondPosition.y += objectsSize.y + size.y;
		}
		renderFirst = firstMinSize.x < objectsSize.x && firstMinSize.y < objectsSize.y;
		renderSecond = secondMinSize.x < objectsSize.x && secondMinSize.y < objectsSize.y;
		
		object->resize(size, position + (this->size - size) / 2.0f);
		
		if(renderFirst)
			firstObject->resize(objectsSize, position);
		if(renderSecond)
			secondObject->resize(objectsSize, secondPosition);
	}
	
	bool BoxWithConstRatioCenter::updateInteractions(sf::Vector2f mousePosition) {
		if(object->inArea(mousePosition)) {
			return object->updateInteractions(mousePosition);
		}
		if(renderFirst && firstObject->inArea(mousePosition)) {
			return firstObject->updateInteractions(mousePosition);
		}
		if(renderSecond && secondObject->inArea(mousePosition)) {
			return secondObject->updateInteractions(mousePosition);
		}
		return background->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxWithConstRatioCenter::getMinSize() {
		sf::Vector2f objectMinSize{object->getMinSize()};
		objectMinSize = sf::Vector2f{std::max(objectMinSize.x, objectMinSize.y * aspectRatio), std::max(objectMinSize.y, objectMinSize.x / aspectRatio)};
		return max(objectMinSize, background->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxWithConstRatioCenter::getNormalSize() {
		sf::Vector2f objectNormalSize{object->getNormalSize()};
		objectNormalSize = sf::Vector2f{std::max(objectNormalSize.x, objectNormalSize.y * aspectRatio), std::max(objectNormalSize.y, objectNormalSize.x / aspectRatio)};
		return max(objectNormalSize, background->getNormalSize());
	}
	
	BoxWithConstRatioCenter *BoxWithConstRatioCenter::copy() {
		BoxWithConstRatioCenter *boxWithConstRatioCenter{new BoxWithConstRatioCenter{object->copy(), firstObject->copy(), secondObject->copy(), background->copy(), aspectRatio, minimumSize}};
		Box::copy(boxWithConstRatioCenter);
		return boxWithConstRatioCenter;
	}
	
	
	bool DecodePointer<BoxWithConstRatioCenter>::decodePointer(const YAML::Node &node, BoxWithConstRatioCenter *&boxWithConstRatioCenter) {
		IScalable *object;
		IScalable *firstObject;
		IScalable *secondObject;
		float aspectRatio;
		IUninteractive *background{};
		sf::Vector2f minSize{};
		
		node["object"] >> object;
		if(node["first-object"]) {
			node["first-object"] >> firstObject;
		} else {
			firstObject = new Empty{};
		}
		if(node["second-object"]) {
			node["second-object"] >> secondObject;
		} else {
			secondObject = new Empty{};
		}
		node["aspect-ratio"] >> aspectRatio;
		if(node["background"]) {
			node["background"] >> background;
		} else {
			background = new Empty{};
		}
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		boxWithConstRatioCenter = new BoxWithConstRatioCenter{object, firstObject, secondObject, background, aspectRatio, minSize};
		return true;
	}
	
	void BoxWithConstRatioCenter::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
	
}
