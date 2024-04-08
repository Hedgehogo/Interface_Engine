namespace ie{
	namespace detail {
		template<size_t S, typename F, size_t... I>
		auto array_from_fn(F fn, std::index_sequence<I...>) -> std::array<std::invoke_result_t<F, size_t>, S> {
			return std::array<std::invoke_result_t<F, size_t>, S>{fn(I)...};
		}
	}
	
	template<size_t S, typename F>
	auto array_from_fn(F fn) -> std::array<std::invoke_result_t<F, size_t>, S> {
		return detail::array_from_fn<S>(fn, std::make_index_sequence<S>{});
	}
	
	template<size_t S, size_t I, typename F, typename... As>
	auto array_try_from_fn(F fn, As&&... args) -> orl::Result<
		std::array<typename std::invoke_result_t<F, size_t>::OkType, S>,
		typename std::invoke_result_t<F, size_t>::ErrorType
	> {
		using Item = typename std::invoke_result_t<F, size_t>::OkType;
		using Error = typename std::invoke_result_t<F, size_t>::ErrorType;
		using Result = orl::Result<std::array<Item, S>, Error>;
		if constexpr (sizeof...(As) == S) {
			return Result::Ok(std::array<Item, S>{std::forward<Item>(args)...});
		} else {
			return fn(I).ok_and_then([&](Item object) {
				return array_try_from_fn<S, I + 1, F>(fn, std::forward<Item>(args)..., object);
			});
		}
	}
}