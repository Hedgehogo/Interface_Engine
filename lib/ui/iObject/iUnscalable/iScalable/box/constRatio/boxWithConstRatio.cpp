#include "boxWithConstRatio.hpp"

namespace ui {
	BoxWithConstRatio::BoxWithConstRatio(
		BoxPtr<IScalable>&& constObject,
		BoxPtr<IScalable>&& secondObject,
		BoxPtr<IUninteractive>&& background,
		float aspectRatio,
		Corner corner,
		sf::Vector2f minSize
	) : Box(minSize),
		background(std::move(background)),
		constObject(std::move(constObject)),
		secondObject(std::move(secondObject)),
		verticalSide(corner == Corner::upLeft || corner == Corner::upRight),
		horizontalSide(corner == Corner::upLeft || corner == Corner::downLeft),
		renderSecond(true),
		aspectRatio(aspectRatio) {
	}
	
	BoxWithConstRatio::BoxWithConstRatio(const BoxWithConstRatio& other) :
		Box(other), background(other.background), constObject(other.constObject), secondObject(other.secondObject),
		verticalSide(other.verticalSide), horizontalSide(other.horizontalSide), renderSecond(other.renderSecond), aspectRatio(other.aspectRatio) {
	}
	
	void BoxWithConstRatio::init(InitInfo initInfo) {
		initInfo.drawManager.add(*this);
		background->init(initInfo);
		constObject->init(initInfo);
		secondObject->init(initInfo.copy(secondDrawManager));
	}
	
	Corner BoxWithConstRatio::getCorner() {
		if(verticalSide) {
			if(horizontalSide) {
				return Corner::upLeft;
			}
			return Corner::upRight;
		} else {
			if(horizontalSide) {
				return Corner::downLeft;
			}
			return Corner::downRight;
		}
	}
	
	void BoxWithConstRatio::draw() {
		if(renderSecond) {
			secondDrawManager.draw();
		}
	}
	
	void BoxWithConstRatio::resize(sf::Vector2f size, sf::Vector2f position) {
		Box::resize(size, position);
		
		sf::Vector2f constSize = sf::Vector2f(size.x / size.y > aspectRatio ? sf::Vector2f{size.y * aspectRatio, size.y} : sf::Vector2f{size.x, size.x / aspectRatio});
		sf::Vector2f secondSize = sf::Vector2f(size.x / size.y > aspectRatio ? sf::Vector2f{size.x - constSize.x, size.y} : sf::Vector2f{size.x, size.y - constSize.y});
		
		sf::Vector2f constPosition = sf::Vector2f{0, 0};
		sf::Vector2f secondPosition = sf::Vector2f{0, 0};
		
		sf::Vector2f secondMinSize = secondObject->getMinSize();
		renderSecond = secondSize.x > secondMinSize.x && secondSize.y > secondMinSize.y;
		if(renderSecond) {
			if(size.x / size.y > aspectRatio) {
				if(horizontalSide) {
					secondPosition.x = constSize.x;
				} else {
					constPosition.x = secondSize.x;
				}
			} else {
				if(verticalSide) {
					secondPosition.y = constSize.y;
				} else {
					constPosition.y = secondSize.y;
				}
			}
		} else {
			constPosition = (layout.size - constSize) / 2.0f;
		}
		
		constPosition += position;
		secondPosition += position;
		
		constObject->resize(constSize, constPosition);
		secondObject->resize(secondSize, secondPosition);
		background->resize(size, position);
	}
	
	bool BoxWithConstRatio::updateInteractions(sf::Vector2f mousePosition) {
		if(renderSecond && secondObject->inArea(mousePosition)) {
			return secondObject->updateInteractions(mousePosition);
		}
		if(constObject->inArea(mousePosition)) {
			return constObject->updateInteractions(mousePosition);
		}
		return background->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxWithConstRatio::getMinSize() const {
		sf::Vector2f constMinSize{constObject->getMinSize()};
		constMinSize = sf::Vector2f{std::max(constMinSize.x, constMinSize.y * aspectRatio), std::max(constMinSize.y, constMinSize.x / aspectRatio)};
		return max(constMinSize, background->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxWithConstRatio::getNormalSize() const {
		sf::Vector2f constNormalSize{constObject->getNormalSize()};
		sf::Vector2f secondNormalSize{secondObject->getNormalSize()};
		//sf::Vector2f normalSize{std::max(constNormalSize.x, constNormalSize.y * aspectRatio), std::max(constNormalSize.y, constNormalSize.x / aspectRatio)};
		sf::Vector2f normalSize{constNormalSize.x + secondNormalSize.x, std::max(constNormalSize.y, secondNormalSize.y)};
		return max(normalSize, background->getNormalSize());
	}
	
	IUninteractive& BoxWithConstRatio::getBackground() {
		return *background;
	}
	
	const IUninteractive& BoxWithConstRatio::getBackground() const {
		return *background;
	}
	
	IScalable& BoxWithConstRatio::getFirstObject() {
		return *constObject;
	}
	
	const IScalable& BoxWithConstRatio::getFirstObject() const {
		return *constObject;
	}
	
	IScalable& BoxWithConstRatio::getSecondObject() {
		return *secondObject;
	}
	
	const IScalable& BoxWithConstRatio::getSecondObject() const {
		return *secondObject;
	}
	
	BoxWithConstRatio* BoxWithConstRatio::copy() {
		return new BoxWithConstRatio{*this};
	}
	
	bool DecodePointer<BoxWithConstRatio>::decodePointer(const YAML::Node& node, BoxWithConstRatio*& boxWithConstRatio) {
		boxWithConstRatio = new BoxWithConstRatio{
			node["const-object"].as < BoxPtr < IScalable > > (),
			node["second-object"].as < BoxPtr < IScalable > > (),
			BoxPtr{convDefPtr<IUninteractive, Empty>(node["background"])},
			node["aspect-ratio"].as<float>(),
			convDef(node["corner"], Corner::upLeft),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
	
	void BoxWithConstRatio::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		constObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}
