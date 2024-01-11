#pragma once
#include <filesystem>
#include <vector>
#include <ctre.hpp>
#include <absl/container/flat_hash_map.h>

template<auto P, typename Fn, typename... Args, typename R = std::invoke_result_t<Fn, const std::filesystem::path&, Args...> >
R for_files(const std::filesystem::path& dir, Fn fn, Args... args) {

	if constexpr(std::is_same_v<R, void>) {
		for(auto& entry: std::filesystem::directory_iterator(dir)) {
			if(entry.is_regular_file() && ctre::match<P>(entry.path().string())) {
				fn(entry.path(), args...);
			} else if(entry.is_directory()) {
				for_files<P>(entry.path(), fn, args...);
			}
		}
	} else {
		R result{};
		R result0{};
		for(auto& entry: std::filesystem::directory_iterator(dir)) {
			if(entry.is_regular_file() && ctre::match<P>(entry.path().string())) {
				result0 = fn(entry.path(), args...);
			} else if(entry.is_directory()) {
				result0 = for_files<P>(entry.path(), fn, args...);
			}
			if constexpr(std::is_same_v<R, std::vector<typename R::value_type> >) {
				result.insert(result.end(), result0.begin(), result0.end());
			} else if constexpr(std::is_same_v<R, absl::flat_hash_map<typename R::key_type, typename R::mapped_type> >) {
				for (const auto &pair : result0) {
					result.insert(pair);
				}
			}
		}
		return result;
	}
}
