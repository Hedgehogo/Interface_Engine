#include "config.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "for_files.hpp"

auto my_copy_file(std::filesystem::path const& source_path, std::filesystem::path const& destination_path) -> void {
	auto source{std::ifstream{source_path, std::ios::binary}};
	
	if(source.is_open()) {
		auto destination_i(std::ifstream{destination_path, std::ios::binary});
		if(destination_i.is_open()) {
			auto destination_str{std::string{}};
			auto source_str{std::string{}};
			std::getline(destination_i, destination_str, '\0');
			std::getline(source, source_str, '\0');
			if(destination_str != source_str) {
				destination_i.close();
				auto destination_o{std::ofstream{destination_path, std::ios::binary}};
				if(destination_o.is_open()) {
					destination_o << source_str;
					destination_o.close();
				}
			}
		}
		source.close();
	}
}

template<bool B>
auto copy_file(
	std::filesystem::path const& first_path,
	std::filesystem::path const& first_dir,
	std::filesystem::path const& second_dir
) -> void {
	auto second_path{[&]() -> std::filesystem::path {
		if constexpr(B) {
			return {second_dir.string() + first_path.string().erase(0, first_dir.string().length())};
		}
		return {second_dir.string() + first_path.filename().string()};
	}()};
	
	if(!std::filesystem::exists(second_path)) {
		if(!std::filesystem::exists(second_dir)) {
			std::filesystem::create_directories(second_dir);
		}
		std::filesystem::copy_file(first_path, second_path);
	} else {
		my_copy_file(first_path, second_path);
	}
}

auto get_test_class(std::filesystem::path const& path) -> absl::flat_hash_map<std::string, std::string> {
	auto result{absl::flat_hash_map<std::string, std::string>{}};
	auto file{std::ifstream{path}};
	
	if(file.is_open()) {
		auto str_file{std::string{}};
		std::getline(file, str_file, '\0');
		
		static constexpr auto pattern = ctll::fixed_string{R"(TEST\(([^,]+), ([^\)]+)\))"};
		
		for(auto [whole_match, test_group, test_name]: ctre::search_all<pattern>(str_file)) {
			result[test_name.str()] = test_group.str() + "_" + test_name.str() + "_Test";
		}
		file.close();
	}
	return result;
}

auto establish_friendship(
	std::filesystem::path const& first_path,
	absl::flat_hash_map<std::string, std::string> const& tests_data,
	std::filesystem::path const& lib_dir,
	std::filesystem::path const& test_lib_dir
) -> void {
	auto second_path{std::filesystem::path{test_lib_dir.string() + first_path.string().erase(0, lib_dir.string().length())}};
	auto first_file{std::ifstream{first_path}};
	
	if(first_file.is_open()) {
		auto str_file{std::string{}};
		std::getline(first_file, str_file, '\0');
		
		static constexpr auto pattern = ctll::fixed_string{R"([ \t]*class ([a-z_A-Z][a-z_A-Z0-9]+) *(\<|:|\{).*?\n)"};
		
		for(auto [whole_match, name, b]: ctre::search_all<pattern>(str_file)) {
			if(auto find{tests_data.find(name.str())}; find != tests_data.end()) {
				auto declare_friend{std::string{"class "} + find->second + std::string{";\n"}};
				auto use_friend{std::string{"\nfriend "} + find->second + std::string{";\n"}};
				str_file.insert(whole_match.end(), use_friend.begin(), use_friend.end());
				str_file.insert(str_file.begin(), declare_friend.begin(), declare_friend.end());
			}
		}
		auto input_second_file{std::ifstream{second_path}};
		if(input_second_file.is_open()) {
			auto second_str{std::string{}};
			std::getline(input_second_file, second_str, '\0');
			if(second_str != str_file) {
				auto output_second_file{std::ofstream{second_path, std::ios::trunc}};
				if(output_second_file.is_open()) {
					output_second_file.clear();
					output_second_file << str_file;
					output_second_file.close();
				}
				input_second_file.close();
			}
		}
	}
	first_file.close();
}

auto main() -> int {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	for_files<ctll::fixed_string{R"(.+(\.png|\.txt|\.glsl))"}>(TEST_DIR, copy_file<false>, TEST_DIR, SRC_TEST_DIR);
	
	for_files<ctll::fixed_string{R"(.+(\.cpp|\.inl))"}>(LIB_DIR, copy_file<true>, LIB_DIR, TEST_LIB_DIR);
	
	auto tests_data = for_files<ctll::fixed_string{R"(.+\.cpp)"}>(TEST_DIR, get_test_class);
	
	for_files<ctll::fixed_string{ctll::fixed_string{R"(.+\.hpp)"}}>(LIB_DIR, establish_friendship, tests_data, LIB_DIR, TEST_LIB_DIR);
	return 0;
}