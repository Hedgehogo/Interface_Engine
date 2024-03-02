#include "load_c_modules.hpp"

#include <open-lib/DynamicLibrary.hpp>
#include <curl/curl.h>
#include <iostream>

namespace ie {
	auto write_data(void* ptr, size_t size, size_t n_mem_b, void* stream) -> size_t {
		auto written{fwrite(ptr, size, n_mem_b, (FILE*)stream)};
		return written;
	}
	
	auto download_file(std::string_view url, std::string_view filepath) -> int {
		CURL* curl;
		CURLcode res;
		FILE* fp;
		
		curl = curl_easy_init();
		if(curl) {
			fp = fopen(filepath.data(), "w+");
			curl_easy_setopt(curl, CURLOPT_URL, url.data());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			
			res = curl_easy_perform(curl);
			if(res != CURLE_OK) {
				std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
				curl_easy_cleanup(curl);
				fclose(fp);
				return 1;
			}
			
			curl_easy_cleanup(curl);
			fclose(fp);
			return 0;
		}
		
		return 1;
	}
	
	auto load_c_modules(ieml::Node const& libs, int argc, char* argv[0]) -> void {
		auto lib_dir_fn = [](ieml::Node const& libs) -> std::string_view {
			auto lib_dir_result{libs.at("lib-dir").except().get_string()};
			return lib_dir_result.map_ok([](auto& value) -> std::string_view {
				return value;
			}).ok_or("./");
		};
		auto lib_dir{lib_dir_fn(libs)};
		
		for(auto& c_libs: libs.at("c-lib").ok_or_none()) {
			auto c_lib_dir{std::string(lib_dir) += lib_dir_fn(c_libs)};
			
			for(auto& paths: c_libs.at("path").ok_or_none()) {
				for(auto& path: paths.get_list().except()) {
					auto dl{open_lib::DynamicLibrary{c_lib_dir + path.get_string().except()}};
					dl.template get_sim<void (*)(int, char*[])>("init")(argc, argv);
				}
			}
			for(auto& paths: c_libs.at("download").ok_or_none()) {
				for(auto& path: paths.get_list().except()) {
					auto url{path.get_string().except()};
					url +=
						#if _WIN32
						".dll"
						#else
						".so"
						#endif
						;
					auto name{url};
					
					auto pos{size_t{0}};
					while((pos = name.find("_", pos)) != std::string::npos) {
						name.replace(pos, 1, "_1");
						pos += 2;
					}
					pos = 0;
					while((pos = name.find("/", pos)) != std::string::npos) {
						name.replace(pos, 1, "_2");
						pos += 2;
					}
					
					name = c_lib_dir + name;
					
					if(!std::filesystem::exists(name)) {
						download_file(url, name);
					}
					
					open_lib::DynamicLibrary dl{name.erase(name.rfind('.'))};
					dl.template get_sim<void (*)(int, char*[])>("init")(argc, argv);
				}
			}
		}
	}
}