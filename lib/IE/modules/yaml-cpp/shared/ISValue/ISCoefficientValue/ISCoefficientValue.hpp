#pragma once

#include "../ISValue.hpp"

namespace ie {
	class ISCoefficientValue : public virtual ISValue<float> {
	public:
		ISCoefficientValue() {
		}
	};
}
