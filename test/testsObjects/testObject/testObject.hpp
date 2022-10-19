#pragma once

#include "../../../lib/ui/iObject/iUnscalable/iScalable/iScalable.hpp"
#include "../../../lib/ui/iObject/layout/layout.hpp"
#include <ctime>

class TestObject : public ui::IScalable, public ui::Layout, public ui::IDrawable, public ui::IUpdatable{
public:
	struct Processed{
		struct Init{
			uint64_t time{0};
			sf::RenderTarget *renderTarget;
			ui::DrawManager *drawManager;
			ui::UpdateManager *updateManager;
			ui::InteractionManager *interactionManager;
			ui::InteractionStack *interactionStack;
			ui::IPanelManager *panelManager;
		}init;
		uint64_t update{0};

		struct UpdateInteractions{
			uint64_t time{0};
			sf::Vector2f mousePosition{0, 0};
		}updateInteractions;
		uint64_t draw{0};
		uint64_t copy{0};
		uint64_t drawDebug{0};
	};
protected:
	Processed processed;
	bool updateInteractionsResult;
	sf::Vector2f minSize = {0, 0};
	sf::Vector2f normalSize = {100, 100};
public:
	TestObject(sf::Vector2f minSize = {0, 0}, sf::Vector2f normalSize = {100, 100}, bool updateInteractionsResult = true);

	void init(sf::RenderTarget &renderTarget, ui::DrawManager &drawManager, ui::UpdateManager &updateManager, ui::InteractionManager &interactionManager, ui::InteractionStack &interactionStack, ui::IPanelManager &panelManager) override;

	Processed getProcessed();

	sf::Vector2f getMinSize() override;

	sf::Vector2f getNormalSize() override;

	bool updateInteractions(sf::Vector2f mousePosition) override;

	void draw() override;

	void update() override;

	TestObject *copy() override;

	void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue = 0, uint hueOffset = 36) override;
};
