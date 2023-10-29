#pragma once

namespace ie {
	class IChangeVariable {
	public:
		virtual float get_size() = 0;
		
		virtual float operator()(float frame) = 0;
		
		virtual IChangeVariable* copy() = 0;
		
		virtual ~IChangeVariable() = default;
	};
}