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
			init_info.copy(panel_manager),
			init_info
		),
		interaction_manager(&init_info.interaction_manager),
		hide_interaction(make.hide_interaction->make({init_info, *this})),
		move_interaction(make.move_interaction->make({init_info, *this})) {
	}
	
	Panel::Panel(
		BoxPtr<IScalable>&& object,
		BoxPtr<IHidePanelInteraction> hide_interaction,
		BoxPtr<IMovePanelInteraction> move_interaction,
		BoxPtr<ISizing2> sizing,
		BoxPtr<IPositioning2> positioning,
		bool displayed
	) : BasePanel(std::move(object), std::move(sizing), std::move(positioning), displayed),
		interaction_manager(nullptr), hide_interaction(std::move(hide_interaction)), move_interaction(std::move(move_interaction)) {
	}
	
	Panel::Panel(
		BoxPtr<IScalable>&& object,
		BoxPtr<IHidePanelInteraction> hide_interaction,
		BoxPtr<ISizing2> sizing,
		BoxPtr<IPositioning2> positioning,
		bool displayed
	) : BasePanel(std::move(object), std::move(sizing), std::move(positioning), displayed),
		interaction_manager(nullptr), hide_interaction(std::move(hide_interaction)), move_interaction(new DontMovePanelInteraction{}) {
	}
	
	Panel::Panel(const Panel& other) :
		BasePanel(other), interaction_manager(other.interaction_manager), hide_interaction(other.hide_interaction), move_interaction(other.move_interaction) {
		hide_interaction->set_panel(*this);
	}
	
	void Panel::init(InitInfo init_info) {
		BasePanel::init(init_info);
		InitInfo new_init_info{init_info.window, init_info.render_target, this->draw_manager, this->update_manager, init_info.interaction_manager, init_info.interaction_stack, this->panel_manager};
		object->init(new_init_info);
		hide_interaction->init({init_info, *this});
		move_interaction->init({init_info, *this});
		this->interaction_manager = &init_info.interaction_manager;
	}
	
	void Panel::set_displayed() {
		displayed = true;
	}
	
	bool Panel::is_independent() {
		return true;
	}
	
	bool Panel::is_free() {
		return panel_manager.is_free();
	}
	
	bool Panel::in_const_panels(sf::Vector2f point_position) {
		return panel_manager.in_const_panels(point_position);
	}
	
	void Panel::draw() {
		BasePanel::draw();
		panel_manager.draw();
	}
	
	void Panel::update() {
		panel_manager.update();
		if(old_displayed != displayed) {
			if(displayed) {
				interaction_manager->add_interaction(*hide_interaction);
				interaction_manager->add_interaction(*move_interaction);
			} else {
				interaction_manager->delete_interaction(*hide_interaction);
				interaction_manager->delete_interaction(*move_interaction);
			}
		}
		BasePanel::update();
	}
	
	bool Panel::update_interactions(sf::Vector2f mouse_position, bool active) {
		displayed = true;
		this->active = active;
		if(panel_manager.update_interactions(mouse_position, active))
			return true;
		return BasePanel::update_interactions(mouse_position);
	}
	
	Panel* Panel::copy() {
		return new Panel{*this};
	}
	
	bool DecodePointer<Panel>::decode_pointer(const YAML::Node& node, Panel*& panel) {
		panel = new Panel{
			node["object"].as<BoxPtr<IScalable> >(),
			node["hide-interaction"].as<BoxPtr<IHidePanelInteraction> >(),
			BoxPtr{conv_def_ptr<IMovePanelInteraction, DontMovePanelInteraction>(node["move-interaction"])},
			node["sizing"].as<BoxPtr<ISizing2> >(),
			node["positioning"].as<BoxPtr<IPositioning2> >(),
			conv_def(node["displayed"], false)
		};
		return true;
	}
}
