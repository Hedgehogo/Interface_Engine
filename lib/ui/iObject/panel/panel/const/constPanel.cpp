#include "constPanel.hpp"
#include "../../manager/general/panelManager.hpp"
#include "../../../../drawable/manager/drawManager.hpp"

namespace ui {
	ConstPanel::ConstPanel(IScalable *object, ISizing2 *sizing, IPositioning2 *positioning, bool displayed) :
		BasePanel(object, sizing, positioning, displayed) {}
	
	void ConstPanel::init(InitInfo initInfo) {
		BasePanel::init(initInfo);
		object->init(initInfo.copy(this->drawManager).copy(this->updateManager));
		initInfo.panelManager.displayPanel(this);
	}
	
	bool ConstPanel::isIndependent() { return false; }
	
	bool ConstPanel::isFree() { return true; }
	
	ConstPanel *ConstPanel::copy() {
		ConstPanel* constPanel {new ConstPanel(object->copy(), sizing->copy(), positioning->copy(), displayed)};
		BasePanel::copy(constPanel);
		return constPanel;
	}
	
	bool convertPointer(const YAML::Node &node, ConstPanel *&constPanel) {
		IScalable *object;
		ISizing2 *sizing;
		IPositioning2 *positioning;
		bool displayed{false};
		
		node["object"] >> object;
		node["sizing"] >> sizing;
		node["positioning"] >> positioning;
		if(node["displayed"])
			node["displayed"] >> displayed;
		
		{ constPanel = new ConstPanel{object, sizing, positioning, displayed}; return true; }
	}
}