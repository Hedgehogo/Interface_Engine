#pragma once

#include "../../../lib/IE/component/IComponent/IScalable/IScalable.hpp"
#include "IE/component/IComponent/IComponentLayout/IComponentLayout.hpp"
#include <ctime>

class TestObject : public ie::IScalable, public ie::ILayout, public ie::IDrawable, public ie::IUpdatable {
public:
	struct Processed {
		struct Init {
			uint64_t time{0};
			sf::RenderTarget *render_target;
			ie::DrawManager *draw_manager;
			ie::UpdateManager *update_manager;
			ie::InteractionManager *interaction_manager;
			ie::InteractionStack *interaction_stack;
			ie::IPanelManager *panel_manager;
		} init;
		
		uint64_t update{0};

		struct UpdateInteractions {
			uint64_t time{0};
			sf::Vector2f mouse_position{0, 0};
		} update_interactions{};
		
		uint64_t draw{0};
		uint64_t copy{0};
		uint64_t draw_debug{0};
	};
	
	struct Make : public ie::IScalable::Make, public ie::ILayout::Make {
		sf::Vector2f min_size = {};
		sf::Vector2f normal_size = {100, 100};
		bool update_interactions_result = true;
		
		Make(sf::Vector2f min_size = {}, sf::Vector2f normal_size = {100, 100}, bool update_interactions_result = true);
		
		TestObject* make(ie::InitInfo init_info) override;
	};
	
	TestObject(Make&& make, ie::InitInfo init_info);
	
	TestObject(sf::Vector2f min_size = {0, 0}, sf::Vector2f normal_size = {100, 100}, bool update_interactions_result = true);

	void init(ie::InitInfo init_info) override;

	Processed get_processed();

	sf::Vector2f get_min_size() const override;

	sf::Vector2f get_normal_size() const override;
	
	ie::LayoutData& get_layout_data() override;
	
	const ie::LayoutData& get_layout_data() const override;

	bool update_interactions(sf::Vector2f mouse_position) override;

	void draw() override;

	void update() override;

	TestObject *copy() override;

	void draw_debug(sf::RenderTarget &render_target, int indent, int indent_addition, uint hue = 0, uint hue_offset = 36) override;

protected:
	ie::LayoutData layout_data;
	Processed processed;
	bool update_interactions_result;
	sf::Vector2f min_size = {0, 0};
	sf::Vector2f normal_size = {100, 100};
};
