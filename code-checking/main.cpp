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
	size_t size;
	
	explicit Sources(std::vector<std::string> const& src) : src(src), size(src.size()) {
	}
};

auto get_source(Sources& sources) -> std::optional<std::filesystem::path> {
	auto lock{std::lock_guard<std::mutex>{sources.mtx}};
	auto include_files_size{sources.src.size()};
	if(include_files_size == 0) {
		return std::nullopt;
	}
	auto result{sources.src[sources.src.size() - 1]};
	sources.src.pop_back();
	return result;
}

auto case_insensitive_file_find(
	std::filesystem::path const& dir,
	std::filesystem::path const& file,
	bool corrected = true
) -> std::optional<std::tuple<std::filesystem::path, bool> > {
	auto begin_file{*file.begin()};
	auto begin_file_str{begin_file.string()};
	auto begin_file_lower{begin_file_str};
	std::transform(begin_file_lower.begin(), begin_file_lower.end(), begin_file_lower.begin(), tolower);
	
	if(begin_file_str == "..") {
		return case_insensitive_file_find(dir.parent_path(), file.lexically_relative(begin_file));
	}
	
	for(auto const& entry: std::filesystem::directory_iterator(dir)) {
		auto filename{entry.path().filename().string()};
		auto filename_lower{filename};
		std::transform(filename_lower.begin(), filename_lower.end(), filename_lower.begin(), tolower);
		
		if(filename_lower == begin_file_lower) {
			if(filename != begin_file_str) {
				corrected = false;
			}
			if(begin_file.extension() == ".hpp" || begin_file.extension() == ".inl") {
				return std::tuple{entry.path(), corrected};
			} else {
				return case_insensitive_file_find(entry.path(), file.lexically_relative(begin_file), corrected);
			}
		}
	}
	return {};
}

auto code_checking(Sources& sources, std::vector<std::filesystem::path> include_dirs) -> void {
	auto count_not_corrected_includes{size_t{0}};
	auto count_not_found_includes{size_t{0}};
	
	for(auto file_number{size_t{1}};; ++file_number) {
		auto source_path{std::filesystem::path{}};
		if(auto opt = get_source(sources)) {
			source_path = opt.value();
		} else {
			break;
		}
		auto file{std::ifstream{source_path}};
		if(file.is_open()) {
			auto str{std::string{}};
			auto filter{std::regex{R"(#include ["<]([^"<>]+?.hpp)[>"])"}};
			auto matches{std::smatch{}};
			auto file_str{std::string{}};
			auto not_corrected_file{false};
			
			for(auto line_number{size_t{1}}; std::getline(file, str); ++line_number) {
				if(std::regex_search(str, matches, filter)) {
					auto match_str{matches.str(1)};
					auto match{std::filesystem::path{match_str}};
					include_dirs.emplace_back(source_path.parent_path());
					
					auto possible_path{std::filesystem::path{}};
					
					auto file_not_found{true};
					
					if(match_str.find('\\') != std::string::npos) {
						not_corrected_file = true;
						auto match_str_temp{match_str};
						std::replace(match_str_temp.begin(), match_str_temp.end(), '\\', '/');
						match = std::filesystem::path{match_str_temp};
					}
					
					for(auto const& include_dir: std::vector<std::filesystem::path>{
						include_dirs.rbegin(), include_dirs.rend()
					}) {
						if(auto opt{
							case_insensitive_file_find(include_dir, match.lexically_normal(), !not_corrected_file)
						}) {
							file_not_found = false;
							if(!std::get<1>(opt.value())) {
								possible_path = std::get<0>(opt.value());
							}
						}
					}
					
					if(file_not_found) {
						std::cout << "File: [" << source_path.string() << ":" << line_number << "] included [" << match_str << "] not found\n";
						++count_not_found_includes;
					}
					
					if(!possible_path.empty()) {
						++count_not_corrected_includes;
						not_corrected_file = true;
						std::cout
							<< "File: [" << source_path.string() << ":" << line_number << "] "
							<< "includes [" << match_str << "], "
							<< "the path to which may not work on a case-sensitive operating system.\n"
							<< "Perhaps you meant this file: [" << possible_path.string() << "] -> ";
						auto optimal_path{possible_path};
						for(const auto& include_dir: include_dirs) {
							auto possible_optimal_path = possible_path.lexically_relative(include_dir);
							if(optimal_path.string().size() > possible_optimal_path.string().size()) {
								optimal_path = possible_optimal_path;
							}
						}
						str.replace(str.find(match_str), match_str.size(), optimal_path.string());
						std::replace(str.begin(), str.end(), '\\', '/');
						std::cout << "[" << optimal_path.string() << "]\n";
					}
					include_dirs.pop_back();
				}
				file_str += str + "\n";
			}
			file.close();
			if(not_corrected_file) {
				file_str.erase(file_str.size() - 1);
				auto file_for_write{std::ofstream{source_path}};
				if(file_for_write.is_open()) {
					file_for_write << file_str;
					std::cout << "File corrected\n";
				}
				file_for_write.close();
			}
			
		}
	}
	
	if(count_not_corrected_includes + count_not_found_includes != 0) {
		if(count_not_corrected_includes != 0) {
			std::cout << count_not_corrected_includes << " includes have been fixed\n";
		}
		if(count_not_found_includes != 0) {
			std::cout << count_not_found_includes << " includes not found\n";
		}
	} else {
		std::cout << "All includes correct\n";
	}
}

auto split_set(std::string const& s, char delimiter) -> std::vector<std::string> {
	auto tokens{std::vector<std::string>{}};
	auto token{std::string{}};
	auto token_stream(std::istringstream{s});
	for(size_t i = 0; std::getline(token_stream, token, delimiter); ++i) {
		if(std::find(tokens.begin(), tokens.end(), token) == tokens.end()) {
			tokens.push_back(token);
		}
	}
	return tokens;
}

auto cleansing_include_dirs(std::vector<std::string> const& include_dirs) -> std::vector<std::filesystem::path> {
	auto result{std::vector<std::filesystem::path>{}};
	for(auto const& include_dir: include_dirs) {
		if(include_dir.find("$<INSTALL_INTERFACE:") == std::string::npos && include_dir.find("includes-NOTFOUND") == std::string::npos) {
			auto filter{std::regex{R"(\$<.+?:(.+)>)"}};
			auto matches{std::smatch{}};
			std::regex_match(include_dir, matches, filter);
			auto match{matches.str(1)};
			auto current_path{std::filesystem::path{match.empty() ? include_dir : match}};
			if(std::filesystem::exists(current_path)) {
				result.emplace_back(current_path);
			}
		}
	}
	return result;
}

auto main() -> int {
	auto sources{Sources{split_set(SOURCES, ';')}};
	auto include_dirs{split_set(INCLUDE_DIRS, ';')};
	
	code_checking(sources, cleansing_include_dirs(include_dirs));
	
	return 0;
}