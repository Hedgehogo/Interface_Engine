#pragma once

#include "../ILayout.hpp"
#include "IE/component/IComponent/IScalable/IScalable.hpp"

namespace ie {
	class ILayoutObjectsArray : public virtual ILayout {
	public:
		virtual auto get_array_size() const -> size_t = 0;
		
		virtual auto get_object_at(size_t index) const -> IScalable const& = 0;
	
	protected:
		virtual auto get_object_at(size_t index) -> IScalable& = 0;
	};
}
