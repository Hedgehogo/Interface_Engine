#include "Panel.hpp"
#include "../../IPanelInteraction/IMovePanelInteraction/DontMovePanelInteraction/DontMovePanelInteraction.hpp"

namespace ie {
	Panel::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<IHidePanelInteraction::Make> hide_interaction,
		BoxPtr<IMovePanelInteraction::Make> move_interaction,
		BoxPtr<ISizing2::Make> sizing,
		BoxPtr<IPositioning2::Make> positioning,
		bool displayed
	) :
		object(std::move(object)),
		hide_interaction(std::move(hide_interaction)),
		move_interaction(std::move(move_interaction)),
		sizing(std::move(sizing)),
		positioning(std::move(positioning)),
		displayed(displayed) {
	}
	
	Panel::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		BoxPtr<IHidePanelInteraction::Make> hide_interaction,
		BoxPtr<ISizing2::Make> sizing,
		BoxPtr<IPositioning2::Make> positioning,
		bool displayed
	) :
		object(std::move(object)),
		hide_interaction(std::move(hide_interaction)),
		move_interaction(make_box_ptr<DontMovePanelInteraction::Make>()),
		sizing(std::move(sizing)),
		positioning(std::move(positioning)),
		displayed(displayed) {
	}
	
	Panel* Panel::Make::make(InitInfo init_info) {
		return new Panel{std::move(*this), init_info};
	}
	
	Panel::Panel(Make&& make, InitInfo init_info) :
		BasePanel(
			std::move(make.object),
			std::move(make.sizing),
			std::move(make.positioning),
			make.displayed,
			init_info.copy(panel_manager_),
			init_info
		),
		interaction_manager_(&init_info.interaction_manager),
		hide_interaction_(make.hide_interaction->make({init_info, *this})),
		move_interaction_(make.move_interaction->make({init_info, *this})) {
	}
	
	Panel::Panel(
		BoxPtr<IScalable>&& object,
		BoxPtr<IHidePanelInteraction> hide_interaction,
		BoxPtr<IMovePanelInteraction> move_interaction,
		BoxPtr<ISizing2> sizing,
		BoxPtr<IPositioning2> positioning,
		bool displayed
	) : BasePanel(std::move(object), std::move(sizing), std::move(positioning), displayed),
		interaction_manager_(nullptr), hide_interaction_(std::move(hide_interaction)), move_interaction_(std::move(move_interaction)) {
	}
	
	Panel::Panel(
		BoxPtr<IScalable>&& object,
		BoxPtr<IHidePanelInteraction> hide_interaction,
		BoxPtr<ISizing2> sizing,
		BoxPtr<IPositioning2> positioning,
		bool displayed
	) : BasePanel(std::move(object), std::move(sizing), std::move(positioning), displayed),
		interaction_manager_(nullptr), hide_interaction_(std::move(hide_interaction)), move_interaction_(new DontMovePanelInteraction{}) {
	}
	
	Panel::Panel(const Panel& other) :
		BasePanel(other),
		interaction_manager_(other.interaction_manager_),
		hide_interaction_(other.hide_interaction_),
		move_interaction_(other.move_interaction_) {
		hide_interaction_->set_panel(*this);
	}
	
	void Panel::init(InitInfo init_info) {
		BasePanel::init(init_info);
		InitInfo new_init_info{
			init_info.window,
			init_info.render_target,
			init_info.dyn_buffer,
			this->draw_manager_,
			this->update_manager_,
			init_info.interaction_manager,
			init_info.interaction_stack,
			this->panel_manager_
		};
		object_->init(new_init_info);
		hide_interaction_->init({init_info, *this});
		move_interaction_->init({init_info, *this});
		this->interaction_manager_ = &init_info.interaction_manager;
	}
	
	void Panel::set_displayed() {
		displayed_ = true;
	}
	
	bool Panel::is_independent() {
		return true;
	}
	
	bool Panel::is_free() {
		return panel_manager_.is_free();
	}
	
	bool Panel::in_const_panels(sf::Vector2f point_position) {
		return panel_manager_.in_const_panels(point_position);
	}
	
	void Panel::draw() {
		BasePanel::draw();
		panel_manager_.draw();
	}
	
	void Panel::update() {
		panel_manager_.update();
		if(old_displayed_ != displayed_) {
			if(displayed_) {
				interaction_manager_->add_interaction(*hide_interaction_);
				interaction_manager_->add_interaction(*move_interaction_);
			} else {
				interaction_manager_->delete_interaction(*hide_interaction_);
				interaction_manager_->delete_interaction(*move_interaction_);
			}
		}
		BasePanel::update();
	}
	
	bool Panel::update_interactions(sf::Vector2f mouse_position, bool active) {
		displayed_ = true;
		this->active_ = active;
		if(panel_manager_.update_interactions(mouse_position, active))
			return true;
		return BasePanel::update_interactions(mouse_position);
	}
	
	Panel* Panel::copy() {
		return new Panel{*this};
	}
}

orl::Option<ie::Panel::Make> ieml::Decode<char, ie::Panel::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::Panel::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		map.at("hide-interaction").except().as<ie::BoxPtr<ie::IHidePanelInteraction::Make> >().move_except(),
		[&]{
			if(auto move_interaction{map.at("move-interaction")}) {
				return move_interaction.ok().as<ie::BoxPtr<ie::IMovePanelInteraction::Make> >().move_except();
			}
			return ie::make_box_ptr<ie::IMovePanelInteraction::Make, ie::DontMovePanelInteraction::Make>();
		}(),
		map.at("sizing").except().as<ie::BoxPtr<ie::ISizing2::Make> >().move_except(),
		map.at("positioning").except().as<ie::BoxPtr<ie::IPositioning2::Make> >().move_except(),
		map.get_as<bool>("displayed").ok_or(false),
	};
}
