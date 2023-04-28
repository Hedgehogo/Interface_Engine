#pragma once
#include "../basePanel.hpp"

namespace ui {
	class ConstPanel : public BasePanel {
	public:
		void init(InitInfo initInfo) override;
		
		ConstPanel(IScalable *object, ISizing2 *sizing, IPositioning2 *positioning, bool displayed = false);
		
		bool isIndependent() override;
		
		bool isFree() override;
		
		ConstPanel* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, ConstPanel *&constPanel);
	
	template<>
	struct DecodePointer<ConstPanel> {
		static bool decodePointer(const YAML::Node &node, ConstPanel *&constPanel);
	};
}
