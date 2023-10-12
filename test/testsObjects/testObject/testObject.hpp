#pragma once

#include "../../../lib/IE/component/IComponent/IScalable/IScalable.hpp"
#include "IE/component/IComponent/IComponentLayout/IComponentLayout.hpp"
#include <ctime>

class TestObject : public ie::IScalable, public ie::ILayout, public ie::IDrawable, public ie::IUpdatable {
public:
	struct Processed {
		struct Init {
			uint64_t time{0};
			sf::RenderTarget *renderTarget;
			ie::DrawManager *drawManager;
			ie::UpdateManager *updateManager;
			ie::InteractionManager *interactionManager;
			ie::InteractionStack *interactionStack;
			ie::IPanelManager *panelManager;
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
	
	struct Make : public ie::IScalable::Make, public ie::ILayout::Make {
		sf::Vector2f minSize = {};
		sf::Vector2f normalSize = {100, 100};
		bool updateInteractionsResult = true;
		
		Make(sf::Vector2f minSize = {}, sf::Vector2f normalSize = {100, 100}, bool updateInteractionsResult = true);
		
		TestObject* make(ie::InitInfo initInfo) override;
	};
	
	TestObject(Make&& make, ie::InitInfo initInfo);
	
	TestObject(sf::Vector2f minSize = {0, 0}, sf::Vector2f normalSize = {100, 100}, bool updateInteractionsResult = true);

	void init(ie::InitInfo initInfo) override;

	Processed getProcessed();

	sf::Vector2f getMinSize() const override;

	sf::Vector2f getNormalSize() const override;
	
	ie::LayoutData& getLayoutData() override;
	
	const ie::LayoutData& getLayoutData() const override;

	bool updateInteractions(sf::Vector2f mousePosition) override;

	void draw() override;

	void update() override;

	TestObject *copy() override;

	void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue = 0, uint hueOffset = 36) override;

protected:
	ie::LayoutData layoutData;
	Processed processed;
	bool updateInteractionsResult;
	sf::Vector2f minSize = {0, 0};
	sf::Vector2f normalSize = {100, 100};
};
