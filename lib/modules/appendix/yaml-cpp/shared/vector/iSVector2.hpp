#pragma once

#include "../value/general/sf_Vector2/withValue_sf_Vector2.hpp"
#include "../value/coefficient/general/sCoefficientValue.hpp"
#include "../value/coefficient/reference/sReferenceCoefficientValue.hpp"

namespace ui {
	class ISVector2 : public IShared {
	public:
		ISVector2() = default;
		
		virtual PIShared getXPtr() const = 0;
		
		virtual void setXPtr(PIShared value) = 0;
		
		virtual PIShared getYPtr() const = 0;
		
		virtual void setYPtr(PIShared value) = 0;
	};
}