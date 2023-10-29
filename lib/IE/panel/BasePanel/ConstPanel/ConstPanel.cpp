#include "ConstPanel.hpp"
#include "../../IPanelManager/PanelManager/PanelManager.hpp"
#include "IE/component/IDrawable/DrawManager/DrawManager.hpp"

namespace ie {
	ConstPanel::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<ISizing2::Make> sizing, BoxPtr<IPositioning2::Make> positioning, bool displayed) :
		object(std::move(object)), sizing(std::move(sizing)), positioning(std::move(positioning)), displayed(displayed) {
	}
	
	ConstPanel* ConstPanel::Make::make(InitInfo init_info) {
		return new ConstPanel{std::move(*this), init_info};
	}
	
	ConstPanel::ConstPanel(Make&& make, InitInfo init_info) :
		BasePanel(
			std::move(make.object),
			std::move(make.sizing),
			std::move(make.positioning),
			make.displayed,
			init_info,
			init_info
		) {
		init_info.panel_manager.display_panel(this);
	}
	
	ConstPanel::ConstPanel(BoxPtr<IScalable>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed) :
		BasePanel(std::move(object), std::move(sizing), std::move(positioning), displayed) {
	}
	
	void ConstPanel::init(InitInfo init_info) {
		BasePanel::init(init_info);
		object_->init(init_info.copy(this->draw_manager_).copy(this->update_manager_));
		init_info.panel_manager.display_panel(this);
	}
	
	bool ConstPanel::is_independent() {
		return false;
	}
	
	bool ConstPanel::is_free() {
		return true;
	}
	
	ConstPanel* ConstPanel::copy() {
		return new ConstPanel{*this};
	}
	
	bool DecodePointer<ConstPanel>::decode_pointer(const YAML::Node& node, ConstPanel*& const_panel) {
		const_panel = new ConstPanel{
			node["object"].as<BoxPtr<IScalable> >(),
			node["sizing"].as<BoxPtr<ISizing2> >(),
			node["positioning"].as<BoxPtr<IPositioning2> >(),
			conv_def(node["displayed"], false)
		};
		return true;
	}
}