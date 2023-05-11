#pragma once

#include "../../../lib/ui/iObject/panel/panel/basePanel.hpp"
#include "../../../lib/ui/sizingAndPositioning/sizing/const/constSizing.hpp"
#include <ctime>

class TestPanel : public ui::BasePanel{
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
		uint64_t setDisplayed{0};
		uint64_t draw{0};
		uint64_t update{0};
		struct UpdateInteractions{
			uint64_t time{0};
			sf::Vector2f mousePosition{0, 0};
		}updateInteractions;
		struct UpdateInteractionsWithActive{
			uint64_t time{0};
			sf::Vector2f mousePosition{0, 0};
			bool active{false};
		}updateInteractionsWithActive;
		uint64_t copy{0};
	};

protected:
	Processed processed;

	sf::Vector2f minSize;
	sf::Vector2f normalSize;

	bool isIndependentResult;
	bool isFreeResult;
	bool inPanelResult;
	bool updateInteractionsResult;
public:
	TestPanel(bool displayed = false, const sf::Vector2f &minSize = {0, 0}, const sf::Vector2f &normalSize = {100, 100}, bool isIndependentResult = true, bool isFreeResult = true, bool inPanelResult = true, bool updateInteractionsResult = true,
			  ui::ISizing2 *sizing = new ui::Sizing2{new ui::ConstSizing{0.5f}, new ui::ConstSizing{0.5f}},
	          ui::IPositioning2 *positioning = new ui::Positioning2{new ui::InternalPositioning{0, 0}, new ui::InternalPositioning{0, 0}});

	const Processed &getProcessed() const;

	void setIsIndependentResult(bool isIndependentResult);

	void setIsFreeResult(bool isFreeResult);

	void setInPanelResult(bool inPanelResult);

	void setUpdateInteractionsResult(bool updateInteractionsResult);

	void init(ui::InitInfo initInfo) override;

	bool isIndependent() override;

	bool isFree() override;

	void setDisplayed() override;

	void setParentProcessed(bool parentProcessed) override;

	bool getParentProcessed() override;

	bool inPanel(sf::Vector2f pointPosition) override;

	void setPosition(sf::Vector2f position) override;

	void move(sf::Vector2f position) override;

	void setSize(sf::Vector2f size) override;

	void draw() override;

	void resize(sf::Vector2f size, sf::Vector2f position) override;

	void update() override;

	bool updateInteractions(sf::Vector2f mousePosition) override;

	bool updateInteractions(sf::Vector2f mousePosition, bool active) override;

	sf::Vector2f getMinSize() const override;

	sf::Vector2f getNormalSize() const override;

	TestPanel* copy() override;

};
