#include "BoxRenderTexture.hpp"

namespace ie {
	BoxRenderTexture::Make::Make(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f minSize) :
		object(std::move(object)), optimize(optimize), minSize(minSize) {
	}
	
	BoxRenderTexture* BoxRenderTexture::Make::make(InitInfo initInfo) {
		return new BoxRenderTexture{std::move(*this), initInfo};
	}
	
	BoxRenderTexture::BoxRenderTexture(Make&& make, InitInfo initInfo) :
		BoxRenderTexture(std::move(make.object), make.optimize, make.minSize, initInfo) {
	}
	
	BoxRenderTexture::BoxRenderTexture(BoxPtr<IScalable::Make>&& object, bool optimize, sf::Vector2f minSize, InitInfo initInfo) :
		Box(minSize),
		sprite(renderTexture.getTexture()),
		object(object->make(initInfo.copy(renderTexture).copy(drawManager))),
		interactionManager(&initInfo.interactionManager),
		renderTarget(&initInfo.renderTarget),
		optimize(optimize),
		active(true) {
		initInfo.drawManager.add(*this);
	}
	
	BoxRenderTexture::BoxRenderTexture(BoxPtr<IScalable>&& object, bool optimize, sf::Vector2f minSize) :
		Box(minSize), object(std::move(object)), interactionManager(nullptr), renderTarget(nullptr), optimize(optimize), active(true) {
		sprite.setTexture(renderTexture.getTexture());
	}
	
	BoxRenderTexture::BoxRenderTexture(const BoxRenderTexture& other) :
		Box(other), object(other.object), renderTarget(other.renderTarget), optimize(other.optimize), active(true) {
		sf::Vector2u size = this->renderTexture.getSize();
		renderTexture.create(size.x, size.y);
	}
	
	void BoxRenderTexture::init(InitInfo initInfo) {
		this->renderTarget = &initInfo.renderTarget;
		this->interactionManager = &initInfo.interactionManager;
		initInfo.drawManager.add(*this);
		object->init(initInfo.copy(renderTexture).copy(this->drawManager));
	}
	
	void BoxRenderTexture::draw() {
		if(!optimize || active || interactionManager->isBlocked()) {
			renderTexture.clear(sf::Color(0, 0, 0, 0));
			drawManager.draw();
			renderTexture.display();
			active = false;
		}
		renderTarget->draw(sprite);
	}
	
	void BoxRenderTexture::resize(sf::Vector2f size, sf::Vector2f position) {
		IComponentObject::resize(size, position);
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
	
	bool BoxRenderTexture::updateInteractions(sf::Vector2f mousePosition) {
		active = true;
		return object->updateInteractions(mousePosition);
	}
	
	sf::Vector2f BoxRenderTexture::getMinSize() const {
		return max(object->getMinSize(), minimumSize, sf::Vector2f{1, 1});
	}
	
	sf::Vector2f BoxRenderTexture::getNormalSize() const {
		return max(object->getNormalSize(), minimumSize, sf::Vector2f{1, 1});
	}
	
	IScalable& BoxRenderTexture::getObject() {
		return *object;
	}
	
	const IScalable& BoxRenderTexture::getObject() const {
		return *object;
	}
	
	BoxRenderTexture* BoxRenderTexture::copy() {
		return new BoxRenderTexture{*this};
	}
	
	void BoxRenderTexture::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	bool DecodePointer<BoxRenderTexture>::decodePointer(const YAML::Node& node, BoxRenderTexture*& boxWithRenderTexture) {
		boxWithRenderTexture = new BoxRenderTexture{
			node["object"].as<BoxPtr<IScalable> >(),
			convDef(node["optimize"], true),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}