#include "load_c_modules.hpp"

#include <open-lib/DynamicLibrary.hpp>
#include <yaml-cpp/yaml.h>
#include <curl/curl.h>
#include <iostream>
#include "../../yaml.hpp"

namespace ie {
	size_t write_data(void* ptr, size_t size, size_t nMem_b, void* stream) {
		size_t written = fwrite(ptr, size, nMem_b, (FILE*)stream);
		return written;
	}
	
	int download_file(const std::string& url, const std::string& filepath) {
		CURL* curl;
		CURLcode res;
		FILE* fp;
		
		curl = curl_easy_init();
		if(curl) {
			fp = fopen(filepath.c_str(), "w+");
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
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
	
	void load_c_modules(const YAML::Node& libs, int argc, char* argv[0]) {
		std::string lib_dir = conv_def<std::string>(libs["lib-dir"], "./");
		
		if(YAML::Node cLibs{libs["CLib"]}) {
			std::string cLib_dir{lib_dir + conv_def<std::string>(cLibs["lib-dir"], "./")};
			
			if(auto paths = cLibs["path"]; paths) {
				for(const auto& path: paths) {
					open_lib::DynamicLibrary dl{cLib_dir + path.as<std::string>()};
					dl.get_sim <void(*)(int argc, char * argv[])>("init")(argc, argv);
				}
			}
			if(auto paths = cLibs["download"]; paths) {
				for(const auto& path: paths) {
					std::string url = path.as<std::string>();
					url +=
						#if _WIN32
						".dll"
						#else
						".so"
						#endif
						;
					auto name = url;
					
					size_t pos = 0;
					while((pos = name.find("_", pos)) != std::string::npos) {
						name.replace(pos, 1, "_1");
						pos += 2;
					}
					pos = 0;
					while((pos = name.find("/", pos)) != std::string::npos) {
						name.replace(pos, 1, "_2");
						pos += 2;
					}
					
					name = cLib_dir + name;
					
					if(!std::filesystem::exists(name)) {
						download_file(url, name);
					}
					
					open_lib::DynamicLibrary dl{name.erase(name.rfind('.'))};
					dl.get_sim < void(*)(int argc, char * argv[])>("init")(argc, argv);
				}
			}
		}
	}
}