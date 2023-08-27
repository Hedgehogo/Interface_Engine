#pragma once

#include "../../../lib/IE/IComponent/Panel/BasePanel/BasePanel.hpp"
#include "../../../lib/IE/SizingAndPositioning/sizing/const/ConstSizing.hpp"
#include <ctime>

class TestPanel : public ie::BasePanel {
public:
	struct Processed {
		struct Init {
			uint64_t time{0};
			sf::RenderTarget* renderTarget;
			ie::DrawManager* drawManager;
			ie::UpdateManager* updateManager;
			ie::InteractionManager* interactionManager;
			ie::InteractionStack* interactionStack;
			ie::IPanelManager* panelManager;
		} init;
		uint64_t setDisplayed{0};
		uint64_t draw{0};
		uint64_t update{0};
		struct UpdateInteractions {
			uint64_t time{0};
			sf::Vector2f mousePosition{0, 0};
		} updateInteractions{};
		struct UpdateInteractionsWithActive {
			uint64_t time{0};
			sf::Vector2f mousePosition{0, 0};
			bool active{false};
		} updateInteractionsWithActive{};
		uint64_t copy{0};
	};
	
	struct Make : public ie::BasePanel::Make {
		bool displayed = false;
		sf::Vector2f minSize = {};
		sf::Vector2f normalSize = {100, 100};
		bool isIndependentResult = true;
		bool isFreeResult = true;
		bool inPanelResult = true;
		bool updateInteractionsResult = true;
		ie::BoxPtr<ie::ISizing2> sizing = ie::BoxPtr<ie::ISizing2>{new ie::Sizing2{sf::Vector2f{0.5f, 0.5f}}};
		ie::BoxPtr<ie::IPositioning2> positioning = ie::BoxPtr<ie::IPositioning2>{new ie::Positioning2{sf::Vector2f{}, sf::Vector2f{}}};
		
		Make(
			bool displayed = false,
			sf::Vector2f minSize = {},
			sf::Vector2f normalSize = {100, 100},
			bool isIndependentResult = true,
			bool isFreeResult = true,
			bool inPanelResult = true,
			bool updateInteractionsResult = true,
			ie::BoxPtr<ie::ISizing2> sizing = ie::BoxPtr<ie::ISizing2>{new ie::Sizing2{sf::Vector2f{0.5f, 0.5f}}},
			ie::BoxPtr<ie::IPositioning2> positioning = ie::BoxPtr<ie::IPositioning2>{new ie::Positioning2{sf::Vector2f{}, sf::Vector2f{}}}
		);
		
		TestPanel* make(ie::InitInfo initInfo) override;
	};
	
	TestPanel(Make&& make, ie::InitInfo initInfo);
	
	TestPanel(
		bool displayed = false,
		sf::Vector2f minSize = {},
		sf::Vector2f normalSize = {100, 100},
		bool isIndependentResult = true,
		bool isFreeResult = true,
		bool inPanelResult = true,
		bool updateInteractionsResult = true,
		ie::BoxPtr<ie::ISizing2> sizing = ie::BoxPtr<ie::ISizing2>{new ie::Sizing2{sf::Vector2f{0.5f, 0.5f}}},
		ie::BoxPtr<ie::IPositioning2> positioning = ie::BoxPtr<ie::IPositioning2>{new ie::Positioning2{sf::Vector2f{}, sf::Vector2f{}}}
	);
	
	const Processed& getProcessed() const;
	
	void setIsIndependentResult(bool isIndependentResult);
	
	void setIsFreeResult(bool isFreeResult);
	
	void setInPanelResult(bool inPanelResult);
	
	void setUpdateInteractionsResult(bool updateInteractionsResult);
	
	void init(ie::InitInfo initInfo) override;
	
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

protected:
	Processed processed;
	
	sf::Vector2f minSize;
	sf::Vector2f normalSize;
	
	bool isIndependentResult;
	bool isFreeResult;
	bool inPanelResult;
	bool updateInteractionsResult;
};
