#pragma once

#include "../ILayout.hpp"
#include "IE/IComponent/IUnscalable/IScalable/IScalable.hpp"

namespace ie {
	class ILayoutObjectsArray : public virtual ILayout {
	public:
		virtual std::size_t getArraySize() const = 0;
		
		virtual const IScalable& getObjectAt(std::size_t index) const = 0;
	
	protected:
		virtual IScalable& getObjectAt(std::size_t index) = 0;
	};
}
