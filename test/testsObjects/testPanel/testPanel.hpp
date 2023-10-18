#pragma once

#include "IE/Panel/BasePanel/BasePanel.hpp"
#include "IE/sizing-positioning/sizing/const/ConstSizing.hpp"
#include <ctime>

class TestPanel : public ie::BasePanel {
public:
	struct Processed {
		struct Init {
			uint64_t time{0};
			sf::RenderTarget* render_target;
			ie::DrawManager* draw_manager;
			ie::UpdateManager* update_manager;
			ie::InteractionManager* interaction_manager;
			ie::InteractionStack* interaction_stack;
			ie::IPanelManager* panel_manager;
		} init;
		uint64_t set_displayed{0};
		uint64_t draw{0};
		uint64_t update{0};
		struct UpdateInteractions {
			uint64_t time{0};
			sf::Vector2f mouse_position{0, 0};
		} update_interactions{};
		struct UpdateInteractionsWithActive {
			uint64_t time{0};
			sf::Vector2f mouse_position{0, 0};
			bool active{false};
		} update_interactions_with_active{};
		uint64_t copy{0};
	};
	
	struct Make : public ie::BasePanel::Make {
		bool displayed = false;
		sf::Vector2f min_size = {};
		sf::Vector2f normal_size = {100, 100};
		bool is_independent_result = true;
		bool is_free_result = true;
		bool in_panel_result = true;
		bool update_interactions_result = true;
		ie::BoxPtr<ie::ISizing2> sizing = ie::BoxPtr<ie::ISizing2>{new ie::Sizing2{sf::Vector2f{0.5f, 0.5f}}};
		ie::BoxPtr<ie::IPositioning2> positioning = ie::BoxPtr<ie::IPositioning2>{new ie::Positioning2{sf::Vector2f{}, sf::Vector2f{}}};
		
		Make(
			bool displayed = false,
			sf::Vector2f min_size = {},
			sf::Vector2f normal_size = {100, 100},
			bool is_independent_result = true,
			bool is_free_result = true,
			bool in_panel_result = true,
			bool update_interactions_result = true,
			ie::BoxPtr<ie::ISizing2> sizing = ie::BoxPtr<ie::ISizing2>{new ie::Sizing2{sf::Vector2f{0.5f, 0.5f}}},
			ie::BoxPtr<ie::IPositioning2> positioning = ie::BoxPtr<ie::IPositioning2>{new ie::Positioning2{sf::Vector2f{}, sf::Vector2f{}}}
		);
		
		TestPanel* make(ie::InitInfo init_info) override;
	};
	
	TestPanel(Make&& make, ie::InitInfo init_info);
	
	TestPanel(
		bool displayed = false,
		sf::Vector2f min_size = {},
		sf::Vector2f normal_size = {100, 100},
		bool is_independent_result = true,
		bool is_free_result = true,
		bool in_panel_result = true,
		bool update_interactions_result = true,
		ie::BoxPtr<ie::ISizing2> sizing = ie::BoxPtr<ie::ISizing2>{new ie::Sizing2{sf::Vector2f{0.5f, 0.5f}}},
		ie::BoxPtr<ie::IPositioning2> positioning = ie::BoxPtr<ie::IPositioning2>{new ie::Positioning2{sf::Vector2f{}, sf::Vector2f{}}}
	);
	
	const Processed& get_processed() const;
	
	void set_is_independent_result(bool is_independent_result);
	
	void set_is_free_result(bool is_free_result);
	
	void set_in_panel_result(bool in_panel_result);
	
	void set_update_interactions_result(bool update_interactions_result);
	
	void init(ie::InitInfo init_info) override;
	
	bool is_independent() override;
	
	bool is_free() override;
	
	void set_displayed() override;
	
	void set_parent_processed(bool parent_processed) override;
	
	bool get_parent_processed() override;
	
	bool in_panel(sf::Vector2f point_position) override;
	
	void set_position(sf::Vector2f position) override;
	
	void move(sf::Vector2f position) override;
	
	void set_size(sf::Vector2f size) override;
	
	void draw() override;
	
	void resize(sf::Vector2f size, sf::Vector2f position) override;
	
	void update() override;
	
	bool update_interactions(sf::Vector2f mouse_position) override;
	
	bool update_interactions(sf::Vector2f mouse_position, bool active) override;
	
	sf::Vector2f get_min_size() const override;
	
	sf::Vector2f get_normal_size() const override;
	
	TestPanel* copy() override;

protected:
	Processed processed;
	
	sf::Vector2f min_size;
	sf::Vector2f normal_size;
	
	bool is_independent_result;
	bool is_free_result;
	bool in_panel_result;
	bool update_interactions_result;
};
