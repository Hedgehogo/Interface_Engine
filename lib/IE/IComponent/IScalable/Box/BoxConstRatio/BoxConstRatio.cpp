#include "BoxConstRatio.hpp"

namespace ie {
	BoxConstRatio::Make::Make(
		BoxPtr<IScalable::Make>&& constObject,
		BoxPtr<IScalable::Make>&& secondObject,
		BoxPtr<IUninteractive::Make>&& background,
		float aspectRatio,
		Corner corner,
		sf::Vector2f minSize
	) :
		constObject(std::move(constObject)),
		secondObject(std::move(secondObject)),
		background(std::move(background)),
		aspectRatio(aspectRatio),
		corner(corner),
		minSize(minSize) {
	}
	
	BoxConstRatio* BoxConstRatio::Make::make(InitInfo initInfo) {
		return new BoxConstRatio{std::move(*this), initInfo};
	}
	
	BoxConstRatio::BoxConstRatio(Make&& make, InitInfo initInfo) :
		Box(make.minSize),
		background(make.background->make(initInfo)),
		constObject(make.constObject->make(initInfo)),
		secondObject(make.secondObject->make(initInfo.copy(secondDrawManager))),
		verticalSide(make.corner == Corner::UpLeft || make.corner == Corner::UpRight),
		horizontalSide(make.corner == Corner::UpLeft || make.corner == Corner::DownLeft),
		renderSecond(true),
		aspectRatio(make.aspectRatio) {
		initInfo.drawManager.add(*this);
	}
	
	BoxConstRatio::BoxConstRatio(
		BoxPtr<IScalable>&& constObject,
		BoxPtr<IScalable>&& secondObject,
		BoxPtr<IUninteractive>&& background,
		float aspectRatio,
		Corner corner,
		sf::Vector2f minSize
	) :
		Box(minSize),
		background(std::move(background)),
		constObject(std::move(constObject)),
		secondObject(std::move(secondObject)),
		verticalSide(corner == Corner::UpLeft || corner == Corner::UpRight),
		horizontalSide(corner == Corner::UpLeft || corner == Corner::DownLeft),
		renderSecond(true),
		aspectRatio(aspectRatio) {
	}
	
	BoxConstRatio::BoxConstRatio(const BoxConstRatio& other) :
		Box(other), background(other.background), constObject(other.constObject), secondObject(other.secondObject),
		verticalSide(other.verticalSide), horizontalSide(other.horizontalSide), renderSecond(other.renderSecond), aspectRatio(other.aspectRatio) {
	}
	
	void BoxConstRatio::init(InitInfo initInfo) {
		initInfo.drawManager.add(*this);
		background->init(initInfo);
		constObject->init(initInfo);
		secondObject->init(initInfo.copy(secondDrawManager));
	}
	
	Corner BoxConstRatio::getCorner() {
		if(verticalSide) {
			if(horizontalSide) {
				return Corner::UpLeft;
			}
			return Corner::UpRight;
		} else {
			if(horizontalSide) {
				return Corner::DownLeft;
			}
			return Corner::DownRight;
		}
	}
	
	void BoxConstRatio::draw() {
		if(renderSecond) {
			secondDrawManager.draw();
		}
	}
	
	void BoxConstRatio::setPosition(sf::Vector2f position) {
		BoxConstRatio::move(position - layout.position);
	}
	
	void BoxConstRatio::move(sf::Vector2f position) {
		layout.move(position);
		background->move(position);
		constObject->move(position);
		secondObject->move(position);
	}
	
	void BoxConstRatio::setSize(sf::Vector2f size) {
		resize(size, layout.position);
	}
	
	void BoxConstRatio::resize(sf::Vector2f size, sf::Vector2f position) {
		layout.resize(size, position);
		
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
	
	bool BoxConstRatio::updateInteractions(sf::Vector2f mousePosition) {
		if(renderSecond && secondObject->inArea(mousePosition)) {
			return secondObject->updateInteractions(mousePosition);
		}
		if(constObject->inArea(mousePosition)) {
			return constObject->updateInteractions(mousePosition);
		}
		return background->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxConstRatio::getMinSize() const {
		sf::Vector2f constMinSize{constObject->getMinSize()};
		constMinSize = sf::Vector2f{std::max(constMinSize.x, constMinSize.y * aspectRatio), std::max(constMinSize.y, constMinSize.x / aspectRatio)};
		return max(constMinSize, background->getMinSize(), minimumSize);
	}
	
	sf::Vector2f BoxConstRatio::getNormalSize() const {
		sf::Vector2f constNormalSize{constObject->getNormalSize()};
		sf::Vector2f secondNormalSize{secondObject->getNormalSize()};
		//sf::Vector2f normalSize{std::max(constNormalSize.x, constNormalSize.y * aspectRatio), std::max(constNormalSize.y, constNormalSize.x / aspectRatio)};
		sf::Vector2f normalSize{constNormalSize.x + secondNormalSize.x, std::max(constNormalSize.y, secondNormalSize.y)};
		return max(normalSize, background->getNormalSize());
	}
	
	IUninteractive& BoxConstRatio::getBackground() {
		return *background;
	}
	
	const IUninteractive& BoxConstRatio::getBackground() const {
		return *background;
	}
	
	IScalable& BoxConstRatio::getFirstObject() {
		return *constObject;
	}
	
	const IScalable& BoxConstRatio::getFirstObject() const {
		return *constObject;
	}
	
	IScalable& BoxConstRatio::getSecondObject() {
		return *secondObject;
	}
	
	const IScalable& BoxConstRatio::getSecondObject() const {
		return *secondObject;
	}
	
	BoxConstRatio* BoxConstRatio::copy() {
		return new BoxConstRatio{*this};
	}
	
	void BoxConstRatio::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		IComponent::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		constObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
		secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
	
	bool DecodePointer<BoxConstRatio>::decodePointer(const YAML::Node& node, BoxConstRatio*& boxWithConstRatio) {
		boxWithConstRatio = new BoxConstRatio{
			node["const-object"].as<BoxPtr<IScalable> >(),
			node["second-object"].as<BoxPtr<IScalable> >(),
			BoxPtr{convDefPtr<IUninteractive, Empty>(node["background"])},
			node["aspect-ratio"].as<float>(),
			convDef(node["corner"], Corner::UpLeft),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}
