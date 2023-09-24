#pragma once

#include "../ILayout.hpp"
#include "IE/IComponent/IScalable/IScalable.hpp"

namespace ie {
	class ILayoutObject : public virtual ILayout {
	public:
		virtual const IScalable& getObject() const = 0;
	
	protected:
		virtual IScalable& getObject() = 0;
	};
}
