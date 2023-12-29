#include "test_object.hpp"

#include "../processor_time.hpp"

TestObject::Make::Make(sf::Vector2f min_size, sf::Vector2f normal_size, bool update_interactions_result) :
	min_size(min_size), normal_size(normal_size), update_interactions_result(update_interactions_result) {
}

TestObject* TestObject::Make::make(ie::InitInfo init_info) {
	return new TestObject{std::move(*this), init_info};
}

TestObject::TestObject(Make&& make, ie::InitInfo init_info) :
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
	update_interactions_result(make.update_interactions_result),
	min_size(make.min_size),
	normal_size(make.normal_size) {
	init_info.draw_manager.add(*this);
	init_info.update_manager.add(*this);
}

TestObject::TestObject(sf::Vector2f min_size, sf::Vector2f normal_size, bool update_interactions_result) :
	update_interactions_result(update_interactions_result), min_size(min_size), normal_size(normal_size) {
}

void TestObject::init(ie::InitInfo init_info) {
	processed.init.time = get_processor_time();
	processed.init.render_target = &init_info.render_target;
	processed.init.draw_manager = &init_info.draw_manager;
	processed.init.update_manager = &init_info.update_manager;
	processed.init.interaction_manager = &init_info.interaction_manager;
	processed.init.interaction_stack = &init_info.interaction_stack;
	processed.init.panel_manager = &init_info.panel_manager;
	
	init_info.draw_manager.add(*this);
	init_info.update_manager.add(*this);
}

TestObject::Processed TestObject::get_processed() {
	return processed;
}

sf::Vector2f TestObject::get_min_size() const {
	return min_size;
}

sf::Vector2f TestObject::get_normal_size() const {
	return normal_size;
}

ie::LayoutData& TestObject::get_layout_data() {
	return layout_data;
}

const ie::LayoutData& TestObject::get_layout_data() const {
	return layout_data;
}

bool TestObject::update_interactions(sf::Vector2f mouse_position) {
	processed.update_interactions.time = get_processor_time();
	processed.update_interactions.mouse_position = mouse_position;
	return update_interactions_result;
}

void TestObject::draw() {
	processed.draw = get_processor_time();
}

void TestObject::update() {
	processed.update = get_processor_time();
}

TestObject* TestObject::copy() {
	processed.copy = get_processor_time();
	return new TestObject{*this};
}

void TestObject::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
	processed.draw_debug = get_processor_time();
}
