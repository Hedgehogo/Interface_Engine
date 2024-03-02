#pragma once

#include "SFML/Graphics.hpp"

namespace ie {
	template<typename T_, T_ const& (* Fn_)(T_ const&, T_ const&)>
	struct FnReduce {
		static auto right(T_ const& first, T_ const& second) -> T_ const& {
			return Fn_(first, second);
		}
		
		template<typename... Other>
		static auto right(T_ const& first, T_ const& second, Other const&... args) -> T_ const& {
			return Fn_(first, FnReduce<T_, Fn_>::right(second, args...));
		}
		
		static auto left(T_ const& first, T_ const& second) -> T_ const& {
			return Fn_(first, second);
		}
		
		template<typename... Other>
		static auto left(T_ const& first, T_ const& second, Other const&... args) -> T_ const& {
			return FnReduce<T_, Fn_>::left(Fn_(first, second), args...);
		}
	};
	
	template<typename T, typename... Other>
	auto max(sf::Vector2<T> const& first, sf::Vector2<T> const& second, sf::Vector2<Other> const&... other) -> sf::Vector2<T> {
		return {FnReduce<T, std::max>::right(first.x, second.x, other.x...), FnReduce<T, std::max>::right(first.y, second.y, other.y...)};
	}
	
	template<typename T, typename... Other>
	auto min(sf::Vector2<T> const& first, sf::Vector2<T> const& second, sf::Vector2<Other> const&... other) -> sf::Vector2<T> {
		return {FnReduce<T, std::min>::right(first.x, second.x, other.x...), FnReduce<T, std::min>::right(first.y, second.y, other.y...)};
	}
}
