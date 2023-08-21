#pragma once

#include "../BasePanel.hpp"

namespace ui {
	class ConstPanel : public BasePanel {
	public:
		struct Make : public BasePanel::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<ISizing2> sizing;
			BoxPtr<IPositioning2> positioning;
			bool displayed = false;
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed = false);
			
			ConstPanel* make(InitInfo initInfo) override;
		};
		
		ConstPanel(Make&& make, InitInfo initInfo);
		
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
