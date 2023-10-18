#pragma once

#include "../ILayout.hpp"
#include "IE/component/IComponent/IScalable/IScalable.hpp"

namespace ie {
	class ILayoutObjectsArray : public virtual ILayout {
	public:
		virtual std::size_t get_array_size() const = 0;
		
		virtual const IScalable& get_object_at(std::size_t index) const = 0;
	
	protected:
		virtual IScalable& get_object_at(std::size_t index) = 0;
	};
}
