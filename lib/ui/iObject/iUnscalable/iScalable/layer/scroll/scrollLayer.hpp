#pragma once

#include "../view/iLayerWithView.hpp"

namespace ui {
	class ScrollLayer : public ILayerWithView{
	protected:
		IUnscalable* object;
		sf::Vector2f oldNormalObjectPosition;
		PSCoefficientVec2 normalObjectPosition;

	public:
		ScrollLayer(IUnscalable *object, const PSCoefficientVec2 &normalObjectPosition, const sf::Vector2f &minSize);

		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;

		sf::Vector2f getMinSize() override;

		sf::Vector2f getNormalSize() override;

	protected:
		sf::Vector2f getNewObjectPosition();

	public:

		void draw() override;

		void resize(sf::Vector2f size, sf::Vector2f position) override;

		bool updateInteractions(sf::Vector2f mousePosition) override;

		ScrollLayer *copy() override;

		~ScrollLayer() override;
	};

	bool convertPointer(const YAML::Node &node, ScrollLayer *&scrollLayer);
} // ui