#pragma once

#include "../ILayout.hpp"
#include "IE/component/IComponent/IScalable/IUninteractive/IUninteractive.hpp"

namespace ie {
	class ILayoutBackground : public virtual ILayout {
	public:
		virtual const IUninteractive& get_background() const = 0;
	
	protected:
		virtual IUninteractive& get_background() = 0;
	};
}
