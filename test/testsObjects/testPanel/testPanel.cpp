#include "test_panel.hpp"
#include "../../../lib/IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/Empty/Empty.hpp"

#include "../processor_time.hpp"

TestPanel::Make::Make(
	bool displayed,
	sf::Vector2f min_size,
	sf::Vector2f normal_size,
	bool is_independent_result,
	bool is_free_result,
	bool in_panel_result,
	bool update_interactions_result,
	ie::BoxPtr<ie::ISizing2> sizing,
	ie::BoxPtr<ie::IPositioning2> positioning
) :
	displayed(displayed),
	min_size(min_size),
	normal_size(normal_size),
	is_independent_result(is_independent_result),
	is_free_result(is_free_result),
	in_panel_result(in_panel_result),
	update_interactions_result(update_interactions_result),
	sizing(std::move(sizing)),
	positioning(std::move(positioning)) {
}

TestPanel* TestPanel::Make::make(ie::InitInfo init_info) {
	return new TestPanel{std::move(*this), init_info};
}

TestPanel::TestPanel(Make&& make, ie::InitInfo init_info) :
	BasePanel(
		ie::BoxPtr < ie::IScalable::Make > {new ie::Empty::Make{}},
		std::move(make.sizing),
		std::move(make.positioning),
		make.displayed,
		init_info,
		init_info
	),
	processed(
		{
			{
				get_processor_time(),
				&init_info.render_target,
				&init_info.draw_manager,
				&init_info.update_manager,
				&init_info.interaction_manager,
				&init_info.interaction_stack,
				&init_info.panel_manager
			}
		}
	),
	min_size(make.min_size),
	normal_size(make.normal_size),
	is_independent_result(make.is_independent_result),
	is_free_result(make.is_free_result),
	in_panel_result(make.in_panel_result),
	update_interactions_result(make.update_interactions_result) {
}

TestPanel::TestPanel(
	bool displayed,
	sf::Vector2f min_size,
	sf::Vector2f normal_size,
	bool is_independent_result,
	bool is_free_result,
	bool in_panel_result,
	bool update_interactions_result,
	ie::BoxPtr<ie::ISizing2> sizing,
	ie::BoxPtr<ie::IPositioning2> positioning
) : BasePanel(ie::BoxPtr < ie::IScalable > {new ie::Empty{}}, std::move(sizing), std::move(positioning), displayed), min_size(min_size), normal_size(normal_size),
	is_independent_result(is_independent_result), is_free_result(is_free_result), in_panel_result(in_panel_result), update_interactions_result(update_interactions_result) {
}

const TestPanel::Processed& TestPanel::get_processed() const {
	return processed;
}

void TestPanel::init(ie::InitInfo init_info) {
	BasePanel::init(init_info);
	
	processed.init.time = get_processor_time();
	processed.init.render_target = &init_info.render_target;
	processed.init.draw_manager = &init_info.draw_manager;
	processed.init.update_manager = &init_info.update_manager;
	processed.init.interaction_manager = &init_info.interaction_manager;
	processed.init.interaction_stack = &init_info.interaction_stack;
	processed.init.panel_manager = &init_info.panel_manager;
}

bool TestPanel::is_independent() {
	return is_independent_result;
}

bool TestPanel::is_free() {
	return is_free_result;
}

void TestPanel::set_displayed() {
	BasePanel::set_displayed();
	processed.set_displayed = get_processor_time();
}

void TestPanel::set_parent_processed(bool parent_processed) {
	BasePanel::set_parent_processed(parent_processed);
}

bool TestPanel::get_parent_processed() {
	return BasePanel::get_parent_processed();
}

bool TestPanel::in_panel(sf::Vector2f point_position) {
	return in_panel_result;
}

void TestPanel::set_position(sf::Vector2f position) {
	BasePanel::set_position(position);
}

void TestPanel::move(sf::Vector2f position) {
	BasePanel::move(position);
}

void TestPanel::set_size(sf::Vector2f size) {
	BasePanel::set_size(size);
}

void TestPanel::draw() {
	processed.draw = get_processor_time();
}

void TestPanel::resize(sf::Vector2f size, sf::Vector2f position) {
	BasePanel::resize(size, position);
}

void TestPanel::update() {
	processed.update = get_processor_time();
}

bool TestPanel::update_interactions(sf::Vector2f mouse_position) {
	BasePanel::update_interactions(mouse_position);
	processed.update_interactions.time = get_processor_time();
	processed.update_interactions.mouse_position = mouse_position;
	return update_interactions_result;
}

bool TestPanel::update_interactions(sf::Vector2f mouse_position, bool active) {
	BasePanel::update_interactions(mouse_position, active);
	processed.update_interactions_with_active.time = get_processor_time();
	processed.update_interactions_with_active.mouse_position = mouse_position;
	processed.update_interactions_with_active.active = active;
	return update_interactions_result;
}

sf::Vector2f TestPanel::get_min_size() const {
	return min_size;
}

sf::Vector2f TestPanel::get_normal_size() const {
	return normal_size;
}

TestPanel* TestPanel::copy() {
	return new TestPanel{*this};
}

void TestPanel::set_is_independent_result(bool is_independent_result) {
	TestPanel::is_independent_result = is_independent_result;
}

void TestPanel::set_is_free_result(bool is_free_result) {
	TestPanel::is_free_result = is_free_result;
}

void TestPanel::set_in_panel_result(bool in_panel_result) {
	TestPanel::in_panel_result = in_panel_result;
}

void TestPanel::set_update_interactions_result(bool update_interactions_result) {
	TestPanel::update_interactions_result = update_interactions_result;
}
