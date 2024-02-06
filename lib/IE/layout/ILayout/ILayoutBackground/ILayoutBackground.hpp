#pragma once

#include "../ILayout.hpp"
#include "IE/component/IComponent/IScalable/INonInteractive/INonInteractive.hpp"

namespace ie {
	class ILayoutBackground : public virtual ILayout {
	public:
		virtual const INonInteractive& get_background() const = 0;
	
	protected:
		virtual INonInteractive& get_background() = 0;
	};
}
