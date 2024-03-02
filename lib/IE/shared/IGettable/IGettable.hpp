#pragma once

namespace ie {
	template<typename T_>
	class IGettable {
	public:
		using T = T_;
		
		virtual auto get() const -> T_ = 0;
		
		virtual ~IGettable() = default;
	};
}
