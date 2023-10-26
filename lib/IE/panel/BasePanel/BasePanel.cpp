#include "BasePanel.hpp"
#include "../IPanelManager/PanelManager/PanelManager.hpp"

namespace ie {
	BasePanel::BasePanel(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<ISizing2::Make> sizing,
		BoxPtr<IPositioning2::Make> positioning,
		bool displayed,
		InitInfo object_init_info,
		InitInfo init_info
	) :
		object(object->make(object_init_info.copy(draw_manager).copy(update_manager))),
		sizing(sizing->make({init_info.render_target, this->object->get_normal_size()})),
		positioning(positioning->make({init_info.render_target})),
		displayed(displayed) {
		this->positioning->init(init_info.render_target);
		init_info.panel_manager.add_panel(this);
	}
	
	BasePanel::BasePanel(BoxPtr<IScalable>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed) :
		object(std::move(object)), sizing(std::move(sizing)), positioning(std::move(positioning)),
		parent_processed(false), old_displayed(false), displayed(displayed), active(false) {
	}
	
	BasePanel::BasePanel(const BasePanel& other) :
		layout_(other.layout_), object(other.object), sizing(other.sizing), positioning(other.positioning),
		parent_processed(other.parent_processed), old_displayed(other.old_displayed), displayed(other.displayed), active(false) {
	}
	
	void BasePanel::init(InitInfo init_info) {
		init_info.panel_manager.add_panel(this);
		sf::Vector2f object_normal_size = object->get_normal_size();
		sizing->init(init_info.render_target, object_normal_size);
		positioning->init(init_info.render_target);
	}
	
	void BasePanel::set_displayed() {
	}
	
	void BasePanel::set_parent_processed(bool parent_processed) {
		this->parent_processed = parent_processed;
	}
	
	bool BasePanel::get_parent_processed() {
		return this->parent_processed;
	}
	
	bool BasePanel::in_panel(sf::Vector2f point_position) {
		return active && in_area(point_position);
	}
	
	bool BasePanel::in_area(sf::Vector2f point_position) {
		return point_position.x > layout_.position.x && point_position.x < layout_.position.x + layout_.size.x &&
			   point_position.y > layout_.position.y && point_position.y < layout_.position.y + layout_.size.y;
	}
	
	bool BasePanel::in(sf::Vector2f point_position) {
		return in_area(point_position);
	}
	
	void BasePanel::draw() {
		draw_manager.draw();
	}
	
	void BasePanel::set_position(sf::Vector2f position) {
		layout_.set_position(position);
		object->set_position(position);
	}
	
	void BasePanel::move(sf::Vector2f offset) {
		layout_.move(offset);
		object->move(offset);
	}
	
	void BasePanel::resize(sf::Vector2f parent_size, sf::Vector2f parent_position) {
		sf::Vector2f size = (*sizing)(parent_size);
		sf::Vector2f position = (*positioning)(parent_position, parent_size, size);
		layout_.resize(size, position);
		object->resize(size, position);
	}
	
	void BasePanel::update() {
		old_displayed = displayed;
		displayed = false;
		update_manager.update();
	}
	
	bool BasePanel::update_interactions(sf::Vector2f mouse_position) {
		return in_panel(mouse_position) && object->update_interactions(mouse_position);
	}
	
	bool BasePanel::update_interactions(sf::Vector2f mouse_position, bool active) {
		displayed = true;
		this->active = active;
		return update_interactions(mouse_position);
	}
	
	sf::Vector2f BasePanel::get_area_position() const {
		return layout_.position;
	}
	
	sf::Vector2f BasePanel::get_area_size() const {
		return layout_.size;
	}
	
	sf::Vector2f BasePanel::get_min_size() const {
		return sizing->get_parent_size(object->get_min_size());
	}
	
	sf::Vector2f BasePanel::get_normal_size() const {
		return sizing->get_parent_size(object->get_normal_size());
	}
	
	IScalable& BasePanel::get_object() {
		return *object;
	}
	
	const IScalable& BasePanel::get_object() const {
		return *object;
	}
	
	bool BasePanel::full_debug = false;
	
	void BasePanel::set_full_debug(bool full_debug) {
		BasePanel::full_debug = full_debug;
	}
	
	void BasePanel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		if(full_debug || old_displayed) {
			object->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		}
	}
	
	LayoutData& BasePanel::layout_get_data() {
		return layout_;
	}
	
	const LayoutData& BasePanel::layout_get_data() const {
		return layout_;
	}
	}