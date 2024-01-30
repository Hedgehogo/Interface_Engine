#include "config.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "for_files.hpp"

void copyFile(const std::filesystem::path& sourcePath, const std::filesystem::path& destinationPath) {
	std::ifstream source(sourcePath, std::ios::binary);
	
	if(source.is_open()) {
		std::ofstream destination(destinationPath, std::ios::binary);
		if(destination.is_open()) {
			destination << source.rdbuf();
			destination.close();
		}
		source.close();
	}
}

bool is_file_empty(const std::filesystem::path& filename) {
	std::ifstream file(filename, std::ios::ate);
	return file.tellg() == 0;
}

template<bool B>
void copy_file(
	const std::filesystem::path& first_path,
	const std::filesystem::path& first_dir,
	const std::filesystem::path& second_dir
) {
	std::filesystem::path second_path;
	if constexpr(B) {
		second_path = second_dir.string() + first_path.string().erase(0, first_dir.string().length());
	} else {
		second_path = second_dir.string() + first_path.filename().string();
	}
	
	if(!std::filesystem::exists(second_path)) {
		if(!std::filesystem::exists(second_dir)) {
			std::filesystem::create_directories(second_dir);
		}
		std::filesystem::copy_file(first_path, second_path);
	} else if(is_file_empty(second_path) || std::filesystem::last_write_time(first_path) > std::filesystem::last_write_time(second_path)) {
		copyFile(first_path, second_path);
	}
}

absl::flat_hash_map<std::string, std::string> get_test_class(const std::filesystem::path& path) {
	absl::flat_hash_map<std::string, std::string> result{};
	
	std::ifstream file{path};
	
	if(file.is_open()) {
		std::string str_file;
		std::getline(file, str_file, '\0');
		
		static constexpr auto pattern = ctll::fixed_string{R"(TEST\(([^,]+), ([^\)]+)\))"};
		
		for(auto [whole_match, test_group, test_name]: ctre::search_all<pattern>(str_file)) {
			result[test_name.str()] = test_group.str() + "_" + test_name.str() + "_Test";
		}
		file.close();
	}
	return result;
}

void establish_friendship(
	const std::filesystem::path& first_path,
	const absl::flat_hash_map<std::string, std::string>& tests_data,
	const std::filesystem::path& lib_dir,
	const std::filesystem::path& test_lib_dir
) {
	std::filesystem::path second_path{test_lib_dir.string() + first_path.string().erase(0, lib_dir.string().length())};
	if(std::filesystem::last_write_time(first_path) > std::filesystem::last_write_time(second_path) || is_file_empty(second_path)) {
		std::ifstream first_file{first_path};
		
		if(first_file.is_open()) {
			bool edit = false;
			std::string str_file;
			std::getline(first_file, str_file, '\0');
			
			static constexpr auto pattern = ctll::fixed_string{R"([ \t]*class ([a-z_A-Z][a-z_A-Z0-9]+) *(\<|:|\{).*?\n)"};
			
			for(auto [whole_match, name, b]: ctre::search_all<pattern>(str_file)) {
				if(auto find{tests_data.find(name.str())}; find != tests_data.end()) {
					edit = true;
					std::string declare_friend = "class " + find->second + ";\n";
					std::string use_friend = "\nfriend " + find->second + ";\n";
					str_file.insert(whole_match.end(), use_friend.begin(), use_friend.end());
					str_file.insert(str_file.begin(), declare_friend.begin(), declare_friend.end());
				}
			}
			
			
			if(is_file_empty(second_path) || edit) {
				std::ofstream second_file{second_path};
				if(second_file.is_open()) {
					second_file << str_file;
					second_file.close();
				}
			}
			
		}
		first_file.close();
	}
}

int main() {
	for_files<ctll::fixed_string{R"(.+(\.png|\.txt|\.glsl))"}>(TEST_DIR, copy_file<false>, TEST_DIR, SRC_TEST_DIR);
	
	for_files<ctll::fixed_string{R"(.+(\.cpp|\.inl))"}>(LIB_DIR, copy_file<true>, LIB_DIR, TEST_LIB_DIR);
	
	auto tests_data = for_files<ctll::fixed_string{R"(.+\.cpp)"}>(TEST_DIR, get_test_class);
	
	for_files<ctll::fixed_string{ctll::fixed_string{R"(.+\.hpp)"}}>(LIB_DIR, establish_friendship, tests_data, LIB_DIR, TEST_LIB_DIR);
	return 0;
}