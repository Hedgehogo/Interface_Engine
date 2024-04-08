//included into vector.hpp

namespace ie {
	template<typename T>
	auto y_size(std::vector<std::vector<T>>& vector) -> size_t {
		if(vector.empty()) {
			return 0;
		}
		return vector[0].size();
	}
	
	template<typename T, typename... As>
	auto make_vector(T&& first, As&& ... args) -> std::vector<T> {
		auto result{std::vector<T>{}};
		result.reserve(sizeof...(As) + 1);
		result.emplace_back(std::forward<T>(first));
		(static_cast<void>(result.emplace_back(std::forward<T>(args))), ...);
		return result;
	}
	
	template<typename F>
	auto vector_from_fn(size_t size, F fn) -> std::vector<std::invoke_result_t<F, size_t> > {
		using Item = std::invoke_result_t<F, size_t>;
		auto result{std::vector<Item>{}};
		result.reserve(size);
		for(auto i{size_t{0}}; i < size; ++i) {
			result.emplace_back(fn(i));
		}
		return result;
	}
	
	template<typename F>
	auto vector_try_from_fn(size_t size, F fn) -> orl::Result<
		std::vector<typename std::invoke_result_t<F, size_t>::OkType>,
		typename std::invoke_result_t<F, size_t>::ErrorType
	> {
		using Item = typename std::invoke_result_t<F, size_t>::OkType;
		using Error = typename std::invoke_result_t<F, size_t>::ErrorType;
		using Result = orl::Result<std::vector<Item>, Error>;
		auto result{std::vector<Item>{}};
		result.reserve(size);
		for(auto i{size_t{0}}; i < size; ++i) {
			auto fn_result{fn(i)};
			if(fn_result.is_ok()) {
				result.emplace_back(std::forward<Item>(fn_result.ok()));
			} else {
				return Result::Error(std::forward<Error>(fn_result.error()));
			}
		}
		return Result::Ok(std::move(result));
	}
}
