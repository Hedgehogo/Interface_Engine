#pragma once

namespace ie {
	template<typename T_>
	class IGettable {
	public:
		using T = T_;
		
		virtual T_ get() const = 0;
	};
}
