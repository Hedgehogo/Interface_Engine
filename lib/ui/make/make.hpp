#pragma once

#include <vector>
#include <algorithm>
#include <Box_Ptr/boxPtr.hpp>

namespace ui {
	using namespace bp;
	
	namespace detail {
		template<typename T, typename I>
		using MakeType = std::remove_pointer_t<decltype(std::declval<T>().make(std::declval<I>()))>;
		
		template<typename T, typename I>
		struct MakeMap {};
		
		template<typename T, typename I>
		struct MakeMap<T*, I> {
			using V = MakeType<T, I>*;
			
			static V map(T*&& make, I initInfo) {
				return make->make(initInfo);
			}
		};
		
		template<typename T, typename I>
		struct MakeMap<BoxPtr<T>, I> {
			using V = BoxPtr<MakeType<T, I> >;
			
			static V map(BoxPtr<T>&& make, I initInfo) {
				return V{make->make(initInfo)};
			}
		};
		
		template<typename T, typename I>
		struct MakeMap<std::vector<T>, I> {
			using V = std::vector<typename MakeMap<T, I>::V>;
			
			static V map(std::vector<T>&& make, I initInfo) {
				V result;
				std::transform(
					std::make_move_iterator(make.begin()),
					std::make_move_iterator(make.end()),
					result.begin(),
					[&](auto&& item) {
						return MakeMap<T, I>::map(std::move(item), initInfo);
					}
				);
				return result;
			}
		};
	}
	
	template<typename T, typename I>
	typename detail::MakeMap<T, I>::V make_map(T&& make, I initInfo) {
		return detail::MakeMap<T, I>::map(std::move(make), initInfo);
	}
}