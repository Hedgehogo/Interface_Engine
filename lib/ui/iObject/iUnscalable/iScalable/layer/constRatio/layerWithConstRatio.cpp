#include "layerWithConstRatio.hpp"

namespace ui {
	void LayerWithConstRatio::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) {
		drawManager.add(*this);
		background->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		firstObject->init(renderTarget, drawManager, updateManager, interactionManager, interactionStack, panelManager);
		secondObject->init(renderTarget, secondDrawManager, updateManager, interactionManager, interactionStack, panelManager);
	}
	
	LayerWithConstRatio::LayerWithConstRatio(IScalable *constObject, IScalable *secondObject, IUninteractive* background, float aspectRatio, Corner corner, sf::Vector2f minSize) :
		Layer(minSize), LayoutWithTwoObjects(constObject, secondObject), LayoutWithBackground(background),
		verticalSide(corner == Corner::upLeft || corner == Corner::upRight), horizontalSide(corner == Corner::upLeft || corner == Corner::downLeft), aspectRatio(aspectRatio), renderSecond(true) {}

    Corner LayerWithConstRatio::getCorner() {
            if (verticalSide){
                if (horizontalSide){
                    return Corner::upLeft;
                }
                return Corner::upRight;
            }
            else{
                if (horizontalSide){
                    return Corner::downLeft;
                }
                return Corner::downRight;
            }
	}
	
	void LayerWithConstRatio::draw(){
		if(renderSecond) {
			secondDrawManager.draw();
		}
	}
	
	void LayerWithConstRatio::resize(sf::Vector2f size, sf::Vector2f position) {
		Layer::resize(size, position);
		
		sf::Vector2f constSize = sf::Vector2f(size.x / size.y > aspectRatio ? sf::Vector2f{size.y * aspectRatio, size.y} : sf::Vector2f{size.x, size.x / aspectRatio});
		sf::Vector2f secondSize = sf::Vector2f(size.x / size.y > aspectRatio ? sf::Vector2f{size.x - constSize.x, size.y} : sf::Vector2f{size.x, size.y - constSize.y} );
		
		sf::Vector2f constPosition = sf::Vector2f{0,0};
		sf::Vector2f secondPosition = sf::Vector2f{0,0};
		
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
			constPosition = (this->size - constSize) / 2.0f;
		}

        constPosition += position;
        secondPosition += position;
		
		firstObject->resize(constSize, constPosition);
		secondObject->resize(secondSize, secondPosition);
		background->resize(size, position);
	}
	
	bool LayerWithConstRatio::updateInteractions(sf::Vector2f mousePosition) {
		if(renderSecond && secondObject->inArea(mousePosition)) {
			return secondObject->updateInteractions(mousePosition);
		}
		if(firstObject->inArea(mousePosition)) {
			return firstObject->updateInteractions(mousePosition);
		}
		return background->updateInteractions(mousePosition);
	}
	
	sf::Vector2f LayerWithConstRatio::getMinSize() {
		sf::Vector2f constMinSize {firstObject->getMinSize()};
		constMinSize = sf::Vector2f{std::max(constMinSize.x, constMinSize.y * aspectRatio), std::max(constMinSize.y, constMinSize.x / aspectRatio)};
		return max(constMinSize, background->getMinSize(), minimumSize);
	}
	
	sf::Vector2f LayerWithConstRatio::getNormalSize() {
		sf::Vector2f constNormalSize {firstObject->getNormalSize()};
		sf::Vector2f secondNormalSize {secondObject->getNormalSize()};
		sf::Vector2f normalSize{std::max(constNormalSize.x, constNormalSize.y * aspectRatio), std::max(constNormalSize.y, constNormalSize.x / aspectRatio)};
		normalSize = {constNormalSize.x + secondNormalSize.x, std::max(constNormalSize.y, secondNormalSize.y)};
		return max(normalSize, background->getNormalSize());
	}
	
	void LayerWithConstRatio::copy(LayerWithConstRatio *layerWithConstRatio) {
		Layer::copy(layerWithConstRatio);
		layerWithConstRatio->renderSecond = this->renderSecond;
	}
	
	LayerWithConstRatio *LayerWithConstRatio::copy() {
		LayerWithConstRatio* layerWithConstRatio{new LayerWithConstRatio{firstObject->copy(), secondObject->copy(), background->copy(), aspectRatio, getCorner(), minimumSize}};
		LayerWithConstRatio::copy(layerWithConstRatio);
		return layerWithConstRatio;
	}
	
	bool convertPointer(const YAML::Node &node, LayerWithConstRatio *&layerWithConstRatio) {
		IScalable *constObject;
		IScalable *secondObject;
		float aspectRatio;
		IUninteractive* background{};
		Corner corner{Corner::upLeft};
		sf::Vector2f minSize{};
		
		node["const-object"] >> constObject;
		node["second-object"] >> secondObject;
		node["aspect-ratio"] >> aspectRatio;
		if(node["background"]) {
			node["background"] >> background;
		} else {
			background = new Empty{};
		}
		if(node["corner"])
			node["corner"] >> corner;
		if(node["min-size"])
			node["min-size"] >> minSize;
		
		{ layerWithConstRatio = new LayerWithConstRatio{constObject, secondObject, background, aspectRatio, corner, minSize}; return true; }
	}
	
	void LayerWithConstRatio::drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) {
        IObject::drawDebug(renderTarget, indent, indentAddition, hue, hueOffset);
		firstObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
        secondObject->drawDebug(renderTarget, indent + indentAddition, indentAddition, hue + hueOffset, hueOffset);
	}
}
