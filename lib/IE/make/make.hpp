#pragma once

#include <vector>
#include <algorithm>
#include <Box_Ptr/boxPtr.hpp>

namespace ui {
	using namespace bp;
	
	namespace detail {
		template<typename, typename Functor, typename... Args>
		[[noreturn]] [[maybe_unused]] static auto invoke_result_or_else_helper(Functor&&) -> std::invoke_result_t<Functor, Args...> {
		}
		
		template<typename Default, typename, typename...>
		[[noreturn]] [[maybe_unused]] static Default invoke_result_or_else_helper(...) {
		}
	}
	
	template<typename Default, typename Functor, typename... Args>
	struct invoke_result_or_else {
		using type = decltype(detail::invoke_result_or_else_helper<Default, Functor, Args...>(std::declval<Functor>()));
	};
	
	template<typename D, typename F, typename... As>
	using invoke_result_or_else_t = typename invoke_result_or_else<D, F, As...>::type;
	
	namespace detail {
		template<typename I>
		using MakeInitInfo = invoke_result_or_else_t<I, I, std::size_t>;
		
		template<typename T, typename I>
		using MakeType = std::remove_pointer_t<decltype(std::declval<T>().make(std::declval<I>()))>;
		
		template<typename T, typename I>
		struct MapMake {};
		
		template<typename T, typename I>
		struct MapMake<T*, I> {
			using V = MakeType<T, I>*;
			
			static V map(T*&& make, const I& initInfo) {
				return make->make(initInfo);
			}
		};
		
		template<typename T, typename I>
		struct MapMake<BoxPtr<T>, I> {
			using V = BoxPtr<MakeType<T, I> >;
			
			static V map(BoxPtr<T>&& make, const I& initInfo) {
				return V{make->make(initInfo)};
			}
		};
		
		template<typename T, typename I>
		struct MapMake<std::vector<T>, I> {
			using V = std::vector<typename MapMake<T, MakeInitInfo<I> >::V>;
			
			static V map(std::vector<T>&& make, const I& initInfo) {
				V result;
				if constexpr(std::is_invocable_v<I, std::size_t>) {
					std::size_t size{make.size()};
					result.reserve(size);
					for(std::size_t i = 0; i < size; ++i) {
						result.push_back(MapMake<T, MakeInitInfo<I> >::map(std::move(make[i]), initInfo(i)));
					}
				} else {
					result.reserve(make.size());
					for(auto& item : make) {
						result.push_back(MapMake<T, MakeInitInfo<I> >::map(std::move(item), initInfo));
					}
				}
				return result;
			}
		};
	}
	
	template<typename T, typename I>
	typename detail::MapMake<T, I>::V mapMake(T&& make, const I& initInfo) {
		return detail::MapMake<T, I>::map(std::move(make), initInfo);
	}
}