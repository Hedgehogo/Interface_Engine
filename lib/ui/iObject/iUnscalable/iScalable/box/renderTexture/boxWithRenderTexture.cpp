#include "boxWithRenderTexture.hpp"

namespace ui {
	void BoxWithRenderTexture::init(InitInfo initInfo) {
		this->renderTarget = &initInfo.renderTarget;
		this->interactionManager = &initInfo.interactionManager;
		initInfo.drawManager.add(*this);
		object->init(initInfo.copy(renderTexture).copy(this->drawManager));
	}
	
	BoxWithRenderTexture::BoxWithRenderTexture(IScalable* object, bool optimize, sf::Vector2f minSize) :
		Box(minSize), LayoutWithObject(object), optimize(optimize), active(true), renderTarget(nullptr), interactionManager(nullptr) {
		sprite.setTexture(renderTexture.getTexture());
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
		LayoutWithObject::resize(size, position);
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
	
	void BoxWithRenderTexture::copy(BoxWithRenderTexture* boxWithRenderTexture) {
		boxWithRenderTexture->renderTarget = this->renderTarget;
		sf::Vector2u size = this->renderTexture.getSize();
		boxWithRenderTexture->renderTexture.create(size.x, size.y);
	}
	
	BoxWithRenderTexture* BoxWithRenderTexture::copy() {
		BoxWithRenderTexture* boxWithRenderTexture{new BoxWithRenderTexture{object->copy(), optimize}};
		BoxWithRenderTexture::copy(boxWithRenderTexture);
		return boxWithRenderTexture;
	}
	
	void BoxWithRenderTexture::drawDebug(sf::RenderTarget& renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
		object->drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
	}
	
	
	bool DecodePointer<BoxWithRenderTexture>::decodePointer(const YAML::Node& node, BoxWithRenderTexture*& boxWithRenderTexture) {
		boxWithRenderTexture = new BoxWithRenderTexture{
			node["object"].as<IScalable*>(),
			convDef(node["optimize"], true),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}