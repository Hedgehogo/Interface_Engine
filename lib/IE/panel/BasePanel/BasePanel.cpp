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
		init_info.panel_manager.add_panel(this);
	}
	
	auto BasePanel::set_displayed() -> void {
	}
	
	auto BasePanel::set_parent_processed(bool parent_processed) -> void {
		this->parent_processed_ = parent_processed;
	}
	
	auto BasePanel::get_parent_processed() -> bool {
		return this->parent_processed_;
	}
	
	auto BasePanel::in_panel(sf::Vector2f point_position) -> bool {
		return active_ && in_area(point_position);
	}
	
	auto BasePanel::in_area(sf::Vector2f point_position) -> bool {
		return point_position.x > layout_.position.x && point_position.x < layout_.position.x + layout_.size.x &&
			   point_position.y > layout_.position.y && point_position.y < layout_.position.y + layout_.size.y;
	}
	
	auto BasePanel::in(sf::Vector2f point_position) -> bool {
		return in_area(point_position);
	}
	
	auto BasePanel::draw() -> void {
		draw_manager_.draw();
	}
	
	auto BasePanel::set_position(sf::Vector2f position) -> void {
		layout_.set_position(position);
		object_->set_position(position);
	}
	
	auto BasePanel::move(sf::Vector2f offset) -> void {
		layout_.move(offset);
		object_->move(offset);
	}
	
	auto BasePanel::resize(sf::Vector2f parent_size, sf::Vector2f parent_position) -> void {
		sf::Vector2f size = (*sizing_)(parent_size);
		sf::Vector2f position = (*positioning_)(parent_position, parent_size, size);
		layout_.resize(size, position);
		object_->resize(size, position);
	}
	
	auto BasePanel::update() -> void {
		old_displayed_ = displayed_;
		displayed_ = false;
		update_manager_.update();
	}
	
	auto BasePanel::update_interactions(sf::Vector2f mouse_position) -> bool {
		return in_panel(mouse_position) && object_->update_interactions(mouse_position);
	}
	
	auto BasePanel::update_interactions(sf::Vector2f mouse_position, bool active) -> bool {
		displayed_ = true;
		this->active_ = active;
		return update_interactions(mouse_position);
	}
	
	auto BasePanel::get_area_position() const -> sf::Vector2f {
		return layout_.position;
	}
	
	auto BasePanel::get_area_size() const -> sf::Vector2f {
		return layout_.size;
	}
	
	auto BasePanel::get_min_size() const -> sf::Vector2f {
		return sizing_->get_parent_size(object_->get_min_size());
	}
	
	auto BasePanel::get_normal_size() const -> sf::Vector2f {
		return sizing_->get_parent_size(object_->get_normal_size());
	}
	
	auto BasePanel::get_object() -> IScalable& {
		return *object_;
	}
	
	auto BasePanel::get_object() const -> IScalable const& {
		return *object_;
	}
	
	bool BasePanel::full_debug_ = false;
	
	auto BasePanel::set_full_debug(bool full_debug) -> void {
		BasePanel::full_debug_ = full_debug;
	}
	
	auto BasePanel::draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void {
		if(full_debug_ || old_displayed_) {
			object_->draw_debug(render_target, indent, indent_addition, hue, hue_offset);
		}
	}
	
	auto BasePanel::layout_get_data() -> LayoutData& {
		return layout_;
	}
	
	auto BasePanel::layout_get_data() const -> LayoutData const& {
		return layout_;
	}
}