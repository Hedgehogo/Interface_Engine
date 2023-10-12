#pragma once

#include "../ILayoutObjectsArray/ILayoutObjectsArray.hpp"
#include "IE/component/IComponent/IScalable/IScalable.hpp"

namespace ie {
	class ILayoutTwoObjects : public virtual ILayoutObjectsArray {
	public:
		std::size_t getArraySize() const override;
		
		const IScalable& getObjectAt(std::size_t index) const override;
		
		virtual const IScalable& getFirstObject() const = 0;
		
		virtual const IScalable& getSecondObject() const = 0;
	
	protected:
		IScalable& getObjectAt(std::size_t index) override;
		
		virtual IScalable& getFirstObject() = 0;
		
		virtual IScalable& getSecondObject() = 0;
	};
}
