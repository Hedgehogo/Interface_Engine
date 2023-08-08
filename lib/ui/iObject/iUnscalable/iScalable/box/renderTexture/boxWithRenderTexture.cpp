#include "boxWithRenderTexture.hpp"

namespace ui {
	BoxWithRenderTexture::Make::Make(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f minSize) :
		object(std::move(object)), optimize(optimize), minSize(minSize) {
	}
	
	BoxWithRenderTexture* BoxWithRenderTexture::Make::make(InitInfo initInfo) {
		return new BoxWithRenderTexture{std::move(*this), initInfo};
	}
	
	BoxWithRenderTexture::BoxWithRenderTexture(Make&& make, InitInfo initInfo) :
		BoxWithRenderTexture(std::move(make.object), make.optimize, make.minSize, initInfo) {
	}
	
	BoxWithRenderTexture::BoxWithRenderTexture(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f minSize, InitInfo initInfo) :
		Box(minSize),
		sprite(renderTexture.getTexture()),
		object(object->make(initInfo.copy(renderTexture).copy(drawManager))),
		interactionManager(&initInfo.interactionManager),
		renderTarget(&initInfo.renderTarget),
		optimize(optimize),
		active(true) {
		initInfo.drawManager.add(*this);
	}
	
	BoxWithRenderTexture::BoxWithRenderTexture(BoxPtr<IScalable>&& object, bool optimize, sf::Vector2f minSize) :
		Box(minSize), object(std::move(object)), interactionManager(nullptr), renderTarget(nullptr), optimize(optimize), active(true) {
		sprite.setTexture(renderTexture.getTexture());
	}
	
	BoxWithRenderTexture::BoxWithRenderTexture(const BoxWithRenderTexture& other) :
		Box(other), object(other.object), renderTarget(other.renderTarget), optimize(other.optimize), active(true) {
		sf::Vector2u size = this->renderTexture.getSize();
		renderTexture.create(size.x, size.y);
	}
	
	void BoxWithRenderTexture::init(InitInfo initInfo) {
		this->renderTarget = &initInfo.renderTarget;
		this->interactionManager = &initInfo.interactionManager;
		initInfo.drawManager.add(*this);
		object->init(initInfo.copy(renderTexture).copy(this->drawManager));
	}
	
	void BoxWithRenderTexture::draw() {
		if(!optimize || active || interactionManager->isBlocked()) {
			renderTexture.clear(sf::Color(0, 0, 0, 0));
			drawManager.draw();
			renderTexture.display();
			active = false;
		}
		renderTarget->draw(sprite);
	}
	
	void BoxWithRenderTexture::resize(sf::Vector2f size, sf::Vector2f position) {
		ILayoutWithObject::resize(size, position);
		sf::Vector2f start{std::floor(position.x), std::ceil(position.y)};
		sf::Vector2f end{std::floor(position.x + size.x), std::ceil(position.y + size.y)};
		sf::Vector2i textureSize{end - start};
		
		view.reset({start, end - start});
		
		renderTexture.create(textureSize.x, textureSize.y);
		renderTexture.setView(view);
		
		sprite.setTexture(renderTexture.getTexture());
		sprite.setTextureRect({{0, 0}, textureSize});
		sprite.setPosition(start);
		
		active = true;
	}
	
	bool BoxWithRenderTexture::updateInteractions(sf::Vector2f mousePosition) {
		active = true;
		return object->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxWithRenderTexture::getMinSize() const {
		return max(object->getMinSize(), minimumSize, {1, 1});
	}
	
	IScalable& BoxWithRenderTexture::getObject() {
		return *object;
	}
	
	const IScalable& BoxWithRenderTexture::getObject() const {
		return *object;
	}
	
	BoxWithRenderTexture* BoxWithRenderTexture::copy() {
		return new BoxWithRenderTexture{*this};
	}
	
	void BoxWithRenderTexture::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	bool DecodePointer<BoxWithRenderTexture>::decodePointer(const YAML::Node& node, BoxWithRenderTexture*& boxWithRenderTexture) {
		boxWithRenderTexture = new BoxWithRenderTexture{
			node["object"].as<BoxPtr<IScalable> >(),
			convDef(node["optimize"], true),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}