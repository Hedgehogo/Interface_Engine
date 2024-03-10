#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "IE/shared/ISReadable/ISRanged/ISRanged.hpp"

namespace ie {
	class MovableBorder;
	
	class MovableBorderAction : public BasicBaseKeyAction<MovableBorder&> {
	public:
		struct Make : public virtual BasicKeyAction<MovableBorder&>::Make {
			ISMRFloat& value;
			
			Make(ISMRFloat& value);
			
			auto make(BasicActionInitInfo<MovableBorder&> init_info) -> MovableBorderAction* override;
		};
		
		MovableBorderAction(Make&& make, BasicActionInitInfo<MovableBorder&> init_info);
		
	protected:
		auto start_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		ISMRFloat& value_;
		MovableBorder* object_;
		float offset_;
	};
}


