#pragma once

#include "../ILayoutObjectsArray/ILayoutObjectsArray.hpp"
#include "IE/component/IComponent/IScalable/IScalable.hpp"

namespace ie {
	class ILayoutTwoObjects : public virtual ILayoutObjectsArray {
	public:
		size_t get_array_size() const override;
		
		const IScalable& get_object_at(size_t index) const override;
		
		virtual const IScalable& get_first_object() const = 0;
		
		virtual const IScalable& get_second_object() const = 0;
	
	protected:
		IScalable& get_object_at(size_t index) override;
		
		virtual IScalable& get_first_object() = 0;
		
		virtual IScalable& get_second_object() = 0;
	};
}
