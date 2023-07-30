#include "constPanel.hpp"
#include "../../manager/general/panelManager.hpp"
#include "../../../../drawable/manager/drawManager.hpp"

namespace ui {
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