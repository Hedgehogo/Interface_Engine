#pragma once

#include "../BasePanel.hpp"

namespace ie {
	class ConstPanel : public BasePanel {
	public:
		struct Make : public virtual BasePanel::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<ISizing2::Make> sizing;
			BoxPtr<IPositioning2::Make> positioning;
			bool displayed = false;
			
			Make(BoxPtr<IScalable::Make>&& object, BoxPtr<ISizing2::Make> sizing, BoxPtr<IPositioning2::Make> positioning, bool displayed = false);
			
			ConstPanel* make(InitInfo init_info) override;
		};
		
		ConstPanel(Make&& make, InitInfo init_info);
		
		ConstPanel(BoxPtr<IScalable>&& object, BoxPtr<ISizing2> sizing, BoxPtr<IPositioning2> positioning, bool displayed = false);
		
		void init(InitInfo init_info) override;
		
		bool is_independent() override;
		
		bool is_free() override;
		
		ConstPanel* copy() override;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<ConstPanel> {
		static bool decode_pointer(const YAML::Node& node, ConstPanel*& const_panel);
	};
	*/
}
