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
			
			static V map(const T*& object, I initInfo) {
				return object->make(initInfo);
			}
		};
		
		template<typename T, typename I>
		struct MakeMap<BoxPtr<T>, I> {
			using V = BoxPtr<MakeType<T, I> >;
			
			static V map(const BoxPtr<T>& object, I initInfo) {
				return V{object->make(initInfo)};
			}
		};
		
		template<typename T, typename I>
		struct MakeMap<std::vector<T>, I> {
			using V = std::vector<typename MakeMap<T, I>::V>;
			
			static V map(const std::vector<T>& object, I initInfo) {
				V result;
				std::transform(object.cbegin(), object.cend(), result.begin(), [&](const auto& item) {
					return MakeMap<T, I>::map(item, initInfo);
				});
				return result;
			}
		};
	}
	
	template<typename T, typename I>
	typename detail::MakeMap<T, I>::V make_map(const T& object, I initInfo) {
		return detail::MakeMap<T, I>::map(object, initInfo);
	}
}