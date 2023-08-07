#pragma once

#include "../../../lib/ui/iObject/iUnscalable/iScalable/iScalable.hpp"
#include "ui/iObject/iLayout/iLayout.hpp"
#include <ctime>

class TestObject : public ui::IScalable, public ui::ILayout, public ui::IDrawable, public ui::IUpdatable {
public:
	struct Processed {
		struct Init {
			uint64_t time{0};
			sf::RenderTarget *renderTarget;
			ui::DrawManager *drawManager;
			ui::UpdateManager *updateManager;
			ui::InteractionManager *interactionManager;
			ui::InteractionStack *interactionStack;
			ui::IPanelManager *panelManager;
		} init;
		
		uint64_t update{0};

		struct UpdateInteractions {
			uint64_t time{0};
			sf::Vector2f mousePosition{0, 0};
		} updateInteractions{};
		
		uint64_t draw{0};
		uint64_t copy{0};
		uint64_t drawDebug{0};
	};
	
	struct Make : public ui::IScalable::Make, public ui::ILayout::Make {
		sf::Vector2f minSize = {};
		sf::Vector2f normalSize = {100, 100};
		bool updateInteractionsResult = true;
		
		Make(sf::Vector2f minSize = {}, sf::Vector2f normalSize = {100, 100}, bool updateInteractionsResult = true);
		
		TestObject* make(ui::InitInfo initInfo) override;
	};
	
	TestObject(Make&& make, ui::InitInfo initInfo);
	
	TestObject(sf::Vector2f minSize = {0, 0}, sf::Vector2f normalSize = {100, 100}, bool updateInteractionsResult = true);

	void init(ui::InitInfo initInfo) override;

	Processed getProcessed();

	sf::Vector2f getMinSize() const override;

	sf::Vector2f getNormalSize() const override;
	
	ui::LayoutData& getLayoutData() override;
	
	const ui::LayoutData& getLayoutData() const override;

	bool updateInteractions(sf::Vector2f mousePosition) override;

	void draw() override;

	void update() override;

	TestObject *copy() override;

	void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue = 0, uint hueOffset = 36) override;

protected:
	ui::LayoutData layoutData;
	Processed processed;
	bool updateInteractionsResult;
	sf::Vector2f minSize = {0, 0};
	sf::Vector2f normalSize = {100, 100};
};
