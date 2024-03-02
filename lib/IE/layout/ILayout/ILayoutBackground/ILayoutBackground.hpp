#pragma once

#include "../ILayout.hpp"
#include "IE/component/IComponent/IScalable/INonInteractive/INonInteractive.hpp"

namespace ie {
	class ILayoutBackground : public virtual ILayout {
	public:
		virtual auto get_background() const -> INonInteractive const& = 0;
	
	protected:
		virtual auto get_background() -> INonInteractive& = 0;
	};
}
