#pragma once

#include "../ILayout.hpp"
#include "IE/component/IComponent/IScalable/IScalable.hpp"

namespace ie {
	class ILayoutObject : public virtual ILayout {
	public:
		virtual auto get_object() const -> IScalable const& = 0;
	
	protected:
		virtual auto get_object() -> IScalable& = 0;
	};
}
