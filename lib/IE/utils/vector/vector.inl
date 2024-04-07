//included into vector.hpp

namespace ie {
	template<typename T>
	auto y_size(std::vector<std::vector<T>>& vector) -> size_t {
		if(vector.empty()) {
			return 0;
		}
		return vector[0].size();
	}
	
	namespace detail {
		template<typename T>
		auto add_items(std::vector<T>&) -> void {
		}
		
		template<typename T, typename A, typename... As>
		auto add_items(std::vector<T>& vector, A&& arg, As&& ... args) -> void {
			vector.emplace_back(std::move(arg));
			add_items<T, As...>(vector, std::move(args)...);
		}
	}
	
	template<typename T, typename... As>
	auto make_vector(T&& arg, As&& ... args) -> std::vector<T> {
		auto result{std::vector<T>{}};
		result.reserve(sizeof...(As) + 1);
		detail::add_items<T, As...>(result, std::move(arg), std::move(args)...);
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
