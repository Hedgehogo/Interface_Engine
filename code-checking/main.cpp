#include "config.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <mutex>
#include <regex>
#include <optional>
#include <algorithm>

struct Sources {
	std::vector<std::string> src;
	std::mutex mtx;
	std::size_t size;
	
	explicit Sources(const std::vector<std::string>& src) : src(src), size(src.size()) {
	}
};

std::optional<std::filesystem::path> get_source(Sources& sources) {
	std::lock_guard<std::mutex> lock{sources.mtx};
	auto include_files_size{sources.src.size()};
	if(include_files_size == 0)
		return std::nullopt;
	auto result{sources.src[sources.src.size() - 1]};
	sources.src.pop_back();
	return result;
}

std::optional<std::tuple<std::filesystem::path, bool>> case_insensitive_file_find(const std::filesystem::path& dir, const std::filesystem::path& file, bool corrected = true) {
	auto begin_file{*file.begin()};
	auto begin_file_str{begin_file.string()};
	auto begin_file_lower{begin_file_str};
	std::transform(begin_file_lower.begin(), begin_file_lower.end(), begin_file_lower.begin(), tolower);
	
	if(begin_file_str == ".."){
		return case_insensitive_file_find(dir.parent_path(), file.lexically_relative(begin_file));
	}
	
	for(const auto& entry: std::filesystem::directory_iterator(dir)) {
		auto filename{entry.path().filename().string()};
		auto filename_lower{filename};
		std::transform(filename_lower.begin(), filename_lower.end(), filename_lower.begin(), tolower);
		
		
		if(filename_lower == begin_file_lower) {
			if(filename != begin_file_str)
				corrected = false;
			if(begin_file.extension() == ".hpp" || begin_file.extension() == ".inl") {
				return std::tuple{entry.path(), corrected};
			} else {
				return case_insensitive_file_find(entry.path(), file.lexically_relative(begin_file), corrected);
			}
		}
	}
	return {};
}

void code_checking(Sources& sources, std::vector<std::filesystem::path> include_dirs) {
	std::size_t count_not_corrected_includes{0};
	std::size_t count_not_found_includes{0};
	
	for(std::size_t file_number = 1;; ++file_number) {
		std::filesystem::path source_path{};
		if(auto opt = get_source(sources)) {
			source_path = opt.value();
		} else {
			break;
		}
		std::ifstream file{source_path};
		if(file.is_open()) {
			std::string str;
			std::regex filter{R"(#include ["<]([^"<>]+?.hpp)[>"])"};
			std::smatch matches;
			std::string file_str;
			bool not_corrected_file = false;
			
			for(std::size_t line_number = 1; std::getline(file, str); ++line_number) {
				if(std::regex_search(str, matches, filter)) {
					
					std::filesystem::path match{matches.str(1)};
					include_dirs.emplace_back(source_path.parent_path());
					
					std::filesystem::path possible_path;
					
					bool file_not_found = true;
					
					for(const auto& include_dir: std::vector<std::filesystem::path>{include_dirs.rbegin(), include_dirs.rend()}) {
						if(auto opt = case_insensitive_file_find(include_dir, match.lexically_normal())) {
							file_not_found = false;
							if(!std::get<1>(opt.value()))
								possible_path = std::get<0>(opt.value());
						}
					}
					
					if (file_not_found) {
						std::cout << "File: [" << source_path.string() << ":" << line_number << "] included [" << match.string() << "] not found\n";
						++count_not_found_includes;
					}
					
					if(!possible_path.empty()){
						++count_not_corrected_includes;
						not_corrected_file = true;
						std::cout << "File: [" << source_path.string() << ":" << line_number << "] includes [" << match.string() << "], the path to which may not work on a case-sensitive operating system.\nPerhaps you meant this file: [" << possible_path.string() << "] -> \n";
						auto optimal_path{possible_path};
						for(const auto& include_dir: include_dirs){
							auto possible_optimal_path = possible_path.lexically_relative(include_dir);
							if(optimal_path.string().size() > possible_optimal_path.string().size()){
								optimal_path = possible_optimal_path;
							}
						}
						str.replace(str.find(match.string()), match.string().size(), optimal_path.string());
						std::cout << "[" << optimal_path.string() << "]\n";
					}
					include_dirs.pop_back();
				}
				file_str += str + "\n";
			}
			file.close();
			if(not_corrected_file){
				file_str.erase(file_str.size() - 1);
				std::ofstream file_for_write{source_path};
				if(file_for_write.is_open()) {
					file_for_write << file_str;
					std::cout << "File corrected\n";
				}
				file_for_write.close();
			}
			
		}
	}
	
	if (count_not_corrected_includes + count_not_found_includes != 0) {
		if(count_not_corrected_includes != 0) {
			std::cout << count_not_corrected_includes << " includes have been fixed\n";
		}
		if (count_not_found_includes != 0) {
			std::cout << count_not_found_includes << " includes not found\n";
		}
		
	} else {
		std::cout << "All includes correct\n";
	}
}

std::vector<std::string> split_set(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	for(std::size_t i = 0; std::getline(tokenStream, token, delimiter); ++i) {
		if(std::find(tokens.begin(), tokens.end(), token) == tokens.end())
			tokens.push_back(token);
	}
	return tokens;
}

std::vector<std::filesystem::path> cleansing_include_dirs(const std::vector<std::string>& include_dirs) {
	std::vector<std::filesystem::path> result;
	for(const auto& include_dir: include_dirs) {
		if(include_dir.find("$<INSTALL_INTERFACE:") == std::string::npos && include_dir.find("includes-NOTFOUND") == std::string::npos) {
			std::regex filter{R"(\$<.+?:(.+)>)"};
			std::smatch matches;
			std::regex_match(include_dir, matches, filter);
			auto match{matches.str(1)};
			std::filesystem::path current_path{match.empty() ? include_dir : match};
			if(std::filesystem::exists(current_path)) {
				result.emplace_back(current_path);
			}
		}
	}
	return result;
}

int main() {
	Sources sources{split_set(SOURCES, ';')};
	auto include_dirs{split_set(INCLUDE_DIRS, ';')};
	
	code_checking(sources, cleansing_include_dirs(include_dirs));
	
	return 0;
}