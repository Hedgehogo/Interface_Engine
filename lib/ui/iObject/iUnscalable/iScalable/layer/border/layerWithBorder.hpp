#pragma once

#include "../layer.hpp"
#include "../../../../../interaction/interactionStack/interactionStack.hpp"

namespace ui {
	class LayerWithBorder : public Layer {
	protected:
		std::vector<std::vector<IScalable *>> objects;
		std::vector<float> boundsVertical;
		std::vector<float> boundsHorizontal;
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;
	
	public:
		LayerWithBorder(std::vector<std::vector<IScalable *>> objects, std::vector<float> boundsHorizontal, std::vector<float> boundsVertical, sf::Vector2f minSize = {0, 0});
		
		LayerWithBorder(std::vector<std::vector<IScalable *>> objects, sf::Vector2f minSize = {0, 0});
		
		~LayerWithBorder() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithBorder* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, LayerWithBorder *&layerWithBorder);
	
	typedef LayerWithBorder LayerWBorder;
	typedef LayerWithBorder LWB;
}

