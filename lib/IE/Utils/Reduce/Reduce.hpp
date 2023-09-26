#pragma once

#include "SFML/Graphics.hpp"

namespace ie {
	template<typename T_, T_ const& (* Fn_)(T_ const&, T_ const&)>
	struct FnReduce {
		static T_ const& right(T_ const& first, T_ const& second) {
			return Fn_(first, second);
		}
		
		template<typename... Other>
		static T_ const& right(T_ const& first, Other const&... args) {
			return Fn_(first, FnReduce<T_, Fn_>::right(args...));
		}
		
		static T_ const& left(T_ const& first, T_ const& second) {
			return Fn_(first, second);
		}
		
		template<typename... Other>
		static T_ const& left(T_ const& first, T_ const& second, Other const&... args) {
			return FnReduce<T_, Fn_>::left(Fn_(first, second), args...);
		}
	};
	
	template<typename T, typename... Other>
	sf::Vector2<T> max(sf::Vector2<T> const& first, sf::Vector2<T> const& second, sf::Vector2<Other> const&... other) {
		return {FnReduce<T, std::max>::right(first.x, second.x, other.x...), FnReduce<T, std::max>::right(first.y, second.y, other.y...)};
	}
	
	template<typename T, typename... Other>
	sf::Vector2<T> min(sf::Vector2<T> const& first, sf::Vector2<T> const& second, sf::Vector2<Other> const&... other) {
		return {FnReduce<T, std::min>::right(first.x, second.x, other.x...), FnReduce<T, std::min>::right(first.y, second.y, other.y...)};
	}
}
