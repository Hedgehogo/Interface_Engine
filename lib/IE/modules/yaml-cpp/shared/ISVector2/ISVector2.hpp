#pragma once

#include "../ISValue/ISCoefficientValue/SCoefficientValue/SCoefficientValue.hpp"
#include "../ISValue/ISCoefficientValue/SReferenceCoefficientValue/SReferenceCoefficientValue.hpp"

namespace ie {
	class ISVector2 : public virtual IShared {
	public:
		ISVector2() = default;
		
		virtual PIShared getXPtr() const = 0;
		
		virtual void setXPtr(PIShared value) = 0;
		
		virtual PIShared getYPtr() const = 0;
		
		virtual void setYPtr(PIShared value) = 0;
	};
}