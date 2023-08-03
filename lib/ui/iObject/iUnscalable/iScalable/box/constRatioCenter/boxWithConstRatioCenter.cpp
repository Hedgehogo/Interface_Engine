#include "boxWithConstRatioCenter.hpp"

namespace ui {
	BoxWithConstRatioCenter::BoxWithConstRatioCenter(
		BoxPtr<IScalable>&& object,
		BoxPtr<IUninteractive>&& background,
		float aspectRatio,
		sf::Vector2f minSize
	) : Box(minSize), background(std::move(background)), object(std::move(object)), firstObject(new Empty), secondObject(new Empty), aspectRatio(aspectRatio) {
	}
	
	BoxWithConstRatioCenter::BoxWithConstRatioCenter(
		BoxPtr<IScalable>&& object,
		BoxPtr<IScalable>&& firstObject,
		BoxPtr<IScalable>&& secondObject,
		BoxPtr<IUninteractive>&& background,
		float aspectRatio,
		sf::Vector2f minSize
	) : Box(minSize), background(std::move(background)), object(std::move(object)), firstObject(std::move(firstObject)), secondObject(std::move(secondObject)), aspectRatio(aspectRatio) {
	}
	
	BoxWithConstRatioCenter::BoxWithConstRatioCenter(const BoxWithConstRatioCenter& other) :
		Box(other), background(other.background), object(other.object), firstObject(other.firstObject), secondObject(other.secondObject), aspectRatio(other.aspectRatio) {
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
		this->setPosition(layout.position);
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
			objectsSize.x = (layout.size.x - size.x) / 2.0f;
			secondPosition.x += objectsSize.x + size.x;
		} else {
			size.y = size.x / aspectRatio;
			objectsSize.y = (layout.size.y - size.y) / 2.0f;
			secondPosition.y += objectsSize.y + size.y;
		}
		renderFirst = firstMinSize.x < objectsSize.x && firstMinSize.y < objectsSize.y;
		renderSecond = secondMinSize.x < objectsSize.x && secondMinSize.y < objectsSize.y;
		
		object->resize(size, position + (layout.size - size) / 2.0f);
		
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
	
	sf::Vector2f BoxWithConstRatioCenter::getMinSize() const {
		sf::Vector2f objectMinSize{object->getMinSize()};
		objectMinSize = sf::Vector2f{std::max(objectMinSize.x, objectMinSize.y * aspectRatio), std::max(objectMinSize.y, objectMinSize.x / aspectRatio)};
		return max(objectMinSize, background->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxWithConstRatioCenter::getNormalSize() const {
		sf::Vector2f objectNormalSize{object->getNormalSize()};
		objectNormalSize = sf::Vector2f{std::max(objectNormalSize.x, objectNormalSize.y * aspectRatio), std::max(objectNormalSize.y, objectNormalSize.x / aspectRatio)};
		return max(objectNormalSize, background->getNormalSize());
	}
	
	IUninteractive& BoxWithConstRatioCenter::getBackground() {
		return *background;
	}
	
	const IUninteractive& BoxWithConstRatioCenter::getBackground() const {
		return *background;
	}
	
	IScalable& BoxWithConstRatioCenter::getObject() {
		return *object;
	}
	
	const IScalable& BoxWithConstRatioCenter::getObject() const {
		return *object;
	}
	
	IScalable& BoxWithConstRatioCenter::getFirstObject() {
		return *firstObject;
	}
	
	const IScalable& BoxWithConstRatioCenter::getFirstObject() const {
		return *firstObject;
	}
	
	IScalable& BoxWithConstRatioCenter::getSecondObject() {
		return *secondObject;
	}
	
	const IScalable& BoxWithConstRatioCenter::getSecondObject() const {
		return *secondObject;
	}
	
	BoxWithConstRatioCenter* BoxWithConstRatioCenter::copy() {
		return new BoxWithConstRatioCenter{*this};
	}
	
	bool DecodePointer<BoxWithConstRatioCenter>::decodePointer(const YAML::Node& node, BoxWithConstRatioCenter*& boxWithConstRatioCenter) {
		boxWithConstRatioCenter = new BoxWithConstRatioCenter{
			node["object"].as<BoxPtr<IScalable> >(),
			BoxPtr{convDefPtr<IScalable, Empty>(node["first-object"])},
			BoxPtr{convDefPtr<IScalable, Empty>(node["second-object"])},
			BoxPtr{convDefPtr<IUninteractive, Empty>(node["background"])},
			node["aspect-ratio"].as<float>(),
			node["min-size"].as<sf::Vector2f>(),
		};
		return true;
	}
	
	void BoxWithConstRatioCenter::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}
