#pragma once

#include "../ILayoutObjectsArray/ILayoutObjectsArray.hpp"
#include "IE/component/IComponent/IScalable/IScalable.hpp"

namespace ie {
	class ILayoutTwoObjects : public virtual ILayoutObjectsArray {
	public:
		auto get_array_size() const -> size_t override;
		
		auto get_object_at(size_t index) const -> IScalable const& override;
		
		virtual auto get_first_object() const -> IScalable const& = 0;
		
		virtual auto get_second_object() const -> IScalable const& = 0;
	
	protected:
		auto get_object_at(size_t index) -> IScalable& override;
		
		virtual auto get_first_object() -> IScalable& = 0;
		
		virtual auto get_second_object() -> IScalable& = 0;
	};
}
