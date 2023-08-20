#include "constPanel.hpp"
#include "../../manager/general/panelManager.hpp"
#include "../../../../IDrawable/DrawManager/DrawManager.hpp"

namespace ui {
	ConstPanel::Make::Make(BoxPtr<IScalable::Make>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed) :
		object(std::move(object)), sizing(std::move(sizing)), positioning(std::move(positioning)), displayed(displayed) {
	}
	
	ConstPanel* ConstPanel::Make::make(InitInfo initInfo) {
		return new ConstPanel{std::move(*this), initInfo};
	}
	
	ConstPanel::ConstPanel(Make&& make, InitInfo initInfo) :
		BasePanel(
			std::move(make.object),
			std::move(make.sizing),
			std::move(make.positioning),
			make.displayed,
			initInfo,
			initInfo
		) {
		initInfo.panelManager.displayPanel(this);
	}
	
	ConstPanel::ConstPanel(BoxPtr<IScalable>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed) :
		BasePanel(std::move(object), std::move(sizing), std::move(positioning), displayed) {
	}
	
	void ConstPanel::init(InitInfo initInfo) {
		BasePanel::init(initInfo);
		object->init(initInfo.copy(this->drawManager).copy(this->updateManager));
		initInfo.panelManager.displayPanel(this);
	}
	
	bool ConstPanel::isIndependent() {
		return false;
	}
	
	bool ConstPanel::isFree() {
		return true;
	}
	
	ConstPanel* ConstPanel::copy() {
		return new ConstPanel{*this};
	}
	
	bool DecodePointer<ConstPanel>::decodePointer(const YAML::Node& node, ConstPanel*& constPanel) {
		constPanel = new ConstPanel{
			node["object"].as<BoxPtr<IScalable> >(),
			node["sizing"].as<BoxPtr<ISizing2> >(),
			node["positioning"].as<BoxPtr<IPositioning2> >(),
			convDef(node["displayed"], false)
		};
		return true;
	}
}