#pragma once

#include <SFML/System.hpp>
#include "../ISValue/ISValue.hpp"

namespace ie {
	namespace make_system {
		template<typename T_>
		struct ISVec2 : public virtual ISValue<sf::Vector2<T_> > {
		};
	}
	
	template<typename T_>
	class ISVec2 : public virtual ISValue<sf::Vector2<T_> > {
	public:
		using ReadFn = typename ISValue<T_>::ReadFn;
		using Make = make_system::ISVec2<T_>;
	};
	
	using ISVec2B = ISVec2<bool>;
	using ISVec2F = ISVec2<float>;
	using ISVec2I = ISVec2<int>;
	using ISVec2S = ISVec2<size_t>;
}
