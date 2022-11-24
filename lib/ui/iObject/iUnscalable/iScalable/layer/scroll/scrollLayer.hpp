#pragma once

#include "../view/iLayerWithView.hpp"

namespace ui {
	class ScrollLayer : public ILayerWithView{
	protected:
		IUnscalable* object;
		PSRVec2f normalObjectPosition;
		
	public:
		ScrollLayer(IUnscalable *object, const PSRVec2f &normalObjectPosition, const sf::Vector2f &minSize);

		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;

		sf::Vector2f getMinSize() override;

		sf::Vector2f getNormalSize() override;

	protected:
		sf::Vector2f getNewObjectPosition(sf::Vector2f normalObjectPosition);

	public:
		void resize(sf::Vector2f size, sf::Vector2f position) override;

		bool updateInteractions(sf::Vector2f mousePosition) override;

		ScrollLayer *copy() override;

		~ScrollLayer() override;
	};

	bool convertPointer(const YAML::Node &node, ScrollLayer *&scrollLayer);
} // ui