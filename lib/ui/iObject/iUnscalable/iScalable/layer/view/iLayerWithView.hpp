#pragma once

#include "../layer.hpp"
#include "../../../../../drawable/iDrawable/iDrawable.hpp"

namespace ui {
	class ILayerWithView : public Layer, public IDrawable {
	protected:
		sf::RenderTarget* renderTarget;
		DrawManager drawManager;
		sf::View view;

	public:
		ILayerWithView(sf::Vector2f minSize);

		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;

		void draw() override;

		void resize(sf::Vector2f size, sf::Vector2f position) override;

		ILayerWithView *copy() override;
	};
} // ui