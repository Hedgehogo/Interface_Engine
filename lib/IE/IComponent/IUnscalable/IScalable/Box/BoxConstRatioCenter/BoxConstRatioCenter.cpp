#include "BoxConstRatioCenter.hpp"

namespace ie {
	BoxConstRatioCenter::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<IUninteractive::Make>&& background, float aspectRatio, sf::Vector2f minSize) :
		object(std::move(object)),
		firstObject(new Empty::Make),
		secondObject(new Empty::Make),
		background(std::move(background)),
		aspectRatio(aspectRatio),
		minSize(minSize) {
	}
	
	BoxConstRatioCenter::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<IScalable::Make>&& firstObject,
		BoxPtr<IScalable::Make>&& secondObject,
		BoxPtr<IUninteractive::Make>&& background,
		float aspectRatio,
		sf::Vector2f minSize
	) :
		object(std::move(object)),
		firstObject(std::move(firstObject)),
		secondObject(std::move(secondObject)),
		background(std::move(background)),
		aspectRatio(aspectRatio),
		minSize(minSize) {
	}
	
	BoxConstRatioCenter* BoxConstRatioCenter::Make::make(InitInfo initInfo) {
		return new BoxConstRatioCenter{std::move(*this), initInfo};
	}
	
	BoxConstRatioCenter::BoxConstRatioCenter(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		background(make.background->make(initInfo)),
		object(make.object->make(initInfo)),
		firstObject(make.firstObject->make(initInfo.copy(firstDrawManager))),
		secondObject(make.secondObject->make(initInfo.copy(secondDrawManager))),
		aspectRatio(make.aspectRatio) {
		initInfo.drawManager.add(*this);
	}
	
	BoxConstRatioCenter::BoxConstRatioCenter(
		BoxPtr<IScalable>&& object,
		BoxPtr<IUninteractive>&& background,
		float aspectRatio,
		sf::Vector2f minSize
	) : Box(minSize), background(std::move(background)), object(std::move(object)), firstObject(new Empty), secondObject(new Empty), aspectRatio(aspectRatio) {
	}
	
	BoxConstRatioCenter::BoxConstRatioCenter(
		BoxPtr<IScalable>&& object,
		BoxPtr<IScalable>&& firstObject,
		BoxPtr<IScalable>&& secondObject,
		BoxPtr<IUninteractive>&& background,
		float aspectRatio,
		sf::Vector2f minSize
	) : Box(minSize), background(std::move(background)), object(std::move(object)), firstObject(std::move(firstObject)), secondObject(std::move(secondObject)), aspectRatio(aspectRatio) {
	}
	
	BoxConstRatioCenter::BoxConstRatioCenter(const BoxConstRatioCenter& other) :
		Box(other), background(other.background), object(other.object), firstObject(other.firstObject), secondObject(other.secondObject), aspectRatio(other.aspectRatio) {
	}
	
	void BoxConstRatioCenter::init(InitInfo initInfo) {
		background->init(initInfo);
		object->init(initInfo);
		initInfo.drawManager.add(*this);
		firstObject->init(initInfo.copy(this->firstDrawManager));
		secondObject->init(initInfo.copy(this->secondDrawManager));
	}
	
	void BoxConstRatioCenter::setAspectRatio(float aspectRatio) {
		this->aspectRatio = aspectRatio;
		this->setPosition(layout.position);
	}
	
	void BoxConstRatioCenter::setPosition(sf::Vector2f position) {
		BoxConstRatioCenter::move(position - layout.position);
	}
	
	void BoxConstRatioCenter::move(sf::Vector2f position) {
		layout.move(position);
		object->move(position);
		background->move(position);
		firstObject->move(position);
		secondObject->move(position);
	}
	
	void BoxConstRatioCenter::setSize(sf::Vector2f size) {
		resize(size, layout.position);
	}
	
	void BoxConstRatioCenter::draw() {
		if(renderFirst) {
			firstDrawManager.draw();
		}
		if(renderSecond) {
			secondDrawManager.draw();
		}
	}
	
	void BoxConstRatioCenter::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		
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
	
	bool BoxConstRatioCenter::updateInteractions(sf::Vector2f mousePosition) {
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
	
	sf::Vector2f BoxConstRatioCenter::getMinSize() const {
		sf::Vector2f objectMinSize{object->getMinSize()};
		objectMinSize = sf::Vector2f{std::max(objectMinSize.x, objectMinSize.y * aspectRatio), std::max(objectMinSize.y, objectMinSize.x / aspectRatio)};
		return max(objectMinSize, background->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxConstRatioCenter::getNormalSize() const {
		sf::Vector2f objectNormalSize{object->getNormalSize()};
		objectNormalSize = sf::Vector2f{std::max(objectNormalSize.x, objectNormalSize.y * aspectRatio), std::max(objectNormalSize.y, objectNormalSize.x / aspectRatio)};
		return max(objectNormalSize, background->getNormalSize());
	}
	
	IUninteractive& BoxConstRatioCenter::getBackground() {
		return *background;
	}
	
	const IUninteractive& BoxConstRatioCenter::getBackground() const {
		return *background;
	}
	
	IScalable& BoxConstRatioCenter::getObject() {
		return *object;
	}
	
	const IScalable& BoxConstRatioCenter::getObject() const {
		return *object;
	}
	
	IScalable& BoxConstRatioCenter::getFirstObject() {
		return *firstObject;
	}
	
	const IScalable& BoxConstRatioCenter::getFirstObject() const {
		return *firstObject;
	}
	
	IScalable& BoxConstRatioCenter::getSecondObject() {
		return *secondObject;
	}
	
	const IScalable& BoxConstRatioCenter::getSecondObject() const {
		return *secondObject;
	}
	
	BoxConstRatioCenter* BoxConstRatioCenter::copy() {
		return new BoxConstRatioCenter{*this};
	}
	
	void BoxConstRatioCenter::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		background->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		object->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
	
	bool DecodePointer<BoxConstRatioCenter>::decodePointer(const YAML::Node& node, BoxConstRatioCenter*& boxWithConstRatioCenter) {
		boxWithConstRatioCenter = new BoxConstRatioCenter{
			node["object"].as<BoxPtr<IScalable> >(),
			BoxPtr{convDefPtr<IScalable, Empty>(node["first-object"])},
			BoxPtr{convDefPtr<IScalable, Empty>(node["second-object"])},
			BoxPtr{convDefPtr<IUninteractive, Empty>(node["background"])},
			node["aspect-ratio"].as<float>(),
			node["min-size"].as<sf::Vector2f>(),
		};
		return true;
	}
}
