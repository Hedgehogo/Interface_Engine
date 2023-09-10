#pragma once

#include "../ILayout.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IUninteractive/IUninteractive.hpp"

namespace ie {
	class ILayoutBackground : public virtual ILayout {
	public:
		virtual const IUninteractive& getBackground() const = 0;
	
	protected:
		virtual IUninteractive& getBackground() = 0;
	};
}
