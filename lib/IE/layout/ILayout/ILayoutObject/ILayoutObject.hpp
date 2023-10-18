#pragma once

#include "../ILayout.hpp"
#include "IE/component/IComponent/IScalable/IScalable.hpp"

namespace ie {
	class ILayoutObject : public virtual ILayout {
	public:
		virtual const IScalable& get_object() const = 0;
	
	protected:
		virtual IScalable& get_object() = 0;
	};
}
