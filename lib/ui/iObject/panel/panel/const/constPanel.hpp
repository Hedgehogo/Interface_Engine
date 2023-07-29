#pragma once

#include "../basePanel.hpp"

namespace ui {
	class ConstPanel : public BasePanel {
	public:
		ConstPanel(BoxPtr<IScalable>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed = false);
		
		void init(InitInfo initInfo) override;
		
		bool isIndependent() override;
		
		bool isFree() override;
		
		ConstPanel* copy() override;
	};
	
	template<>
	struct DecodePointer<ConstPanel> {
		static bool decodePointer(const YAML::Node& node, ConstPanel*& constPanel);
	};
}
