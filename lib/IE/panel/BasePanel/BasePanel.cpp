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
		object_(object->make(object_init_info.copy(draw_manager_).copy(update_manager_))),
		sizing_(sizing->make({init_info.render_target, this->object_->get_normal_size()})),
		positioning_(positioning->make({init_info.render_target})),
		displayed_(displayed) {
		this->positioning_->init(init_info.render_target);
		init_info.panel_manager.add_panel(this);
	}
	
	BasePanel::BasePanel(BoxPtr<IScalable>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed) :
		object_(std::move(object)), sizing_(std::move(sizing)), positioning_(std::move(positioning)),
		parent_processed_(false), old_displayed_(false), displayed_(displayed), active_(false) {
	}
	
	BasePanel::BasePanel(const BasePanel& other) :
		layout_(other.layout_), object_(other.object_), sizing_(other.sizing_), positioning_(other.positioning_),
		parent_processed_(other.parent_processed_), old_displayed_(other.old_displayed_), displayed_(other.displayed_), active_(false) {
	}
	
	void BasePanel::init(InitInfo init_info) {
		init_info.panel_manager.add_panel(this);
		sf::Vector2f object_normal_size = object_->get_normal_size();
		sizing_->init(init_info.render_target, object_normal_size);
		positioning_->init(init_info.render_target);
	}
	
	void BasePanel::set_displayed() {
	}
	
	void BasePanel::set_parent_processed(bool parent_processed) {
		this->parent_processed_ = parent_processed;
	}
	
	bool BasePanel::get_parent_processed() {
		return this->parent_processed_;
	}
	
	bool BasePanel::in_panel(sf::Vector2f point_position) {
		return active_ && in_area(point_position);
	}
	
	bool BasePanel::in_area(sf::Vector2f point_position) {
		return point_position.x > layout_.position.x && point_position.x < layout_.position.x + layout_.size.x &&
			   point_position.y > layout_.position.y && point_position.y < layout_.position.y + layout_.size.y;
	}
	
	bool BasePanel::in(sf::Vector2f point_position) {
		return in_area(point_position);
	}
	
	void BasePanel::draw() {
		draw_manager_.draw();
	}
	
	void BasePanel::set_position(sf::Vector2f position) {
		layout_.set_position(position);
		object_->set_position(position);
	}
	
	void BasePanel::move(sf::Vector2f offset) {
		layout_.move(offset);
		object_->move(offset);
	}
	
	void BasePanel::resize(sf::Vector2f parent_size, sf::Vector2f parent_position) {
		sf::Vector2f size = (*sizing_)(parent_size);
		sf::Vector2f position = (*positioning_)(parent_position, parent_size, size);
		layout_.resize(size, position);
		object_->resize(size, position);
	}
	
	void BasePanel::update() {
		old_displayed_ = displayed_;
		displayed_ = false;
		update_manager_.update();
	}
	
	bool BasePanel::update_interactions(sf::Vector2f mouse_position) {
		return in_panel(mouse_position) && object_->update_interactions(mouse_position);
	}
	
	bool BasePanel::update_interactions(sf::Vector2f mouse_position, bool active) {
		displayed_ = true;
		this->active_ = active;
		return update_interactions(mouse_position);
	}
	
	sf::Vector2f BasePanel::get_area_position() const {
		return layout_.position;
	}
	
	sf::Vector2f BasePanel::get_area_size() const {
		return layout_.size;
	}
	
	sf::Vector2f BasePanel::get_min_size() const {
		return sizing_->get_parent_size(object_->get_min_size());
	}
	
	sf::Vector2f BasePanel::get_normal_size() const {
		return sizing_->get_parent_size(object_->get_normal_size());
	}
	
	IScalable& BasePanel::get_object() {
		return *object_;
	}
	
	const IScalable& BasePanel::get_object() const {
		return *object_;
	}
	
	bool BasePanel::full_debug_ = false;
	
	void BasePanel::set_full_debug(bool full_debug) {
		BasePanel::full_debug_ = full_debug;
	}
	
	void BasePanel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) {
		if(full_debug_ || old_displayed_) {
			object_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		}
	}
	
	LayoutData& BasePanel::layout_get_data() {
		return layout_;
	}
	
	const LayoutData& BasePanel::layout_get_data() const {
		return layout_;
	}
	}