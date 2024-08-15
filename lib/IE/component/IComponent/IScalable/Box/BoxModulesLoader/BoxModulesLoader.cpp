#include "BoxModulesLoader.hpp"

#include <open-lib/DynamicLibrary.hpp>
#include <utility>
#include <curl/curl.h>
#include "config.hpp"
#include "IE/utils/utf/to_utf/to_utf.hpp"
#include "IE/component/IComponent/IScalable/INonInteractive/OnlyDrawable/Empty/Empty.hpp"
#include "IE/shared/ISReadable/SString/SString.hpp"

namespace ie {
	namespace detail{
		struct Progress_bar_data {
			float& progress_bar;
			std::mutex& progress_bar_mutex;
			curl_off_t size;
			size_t count_libs;
			size_t i;
		};
		
		struct Write_data{
			FILE* file;
			std::filesystem::path path;
		};
		
		auto write_function(char *ptr, size_t size, size_t nmemb, void *userdata) -> size_t {
			auto write_data{static_cast<Write_data*>(userdata)};
			if(!write_data->file) {
				write_data->file = fopen(write_data->path.c_str(), "w+");
			}
			auto written{fwrite(ptr, size, nmemb, write_data->file)};
			return written;
		}
		
		static auto progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) -> size_t {
			auto clientp2{static_cast<Progress_bar_data*>(clientp)};
			auto lock_progress_bar{std::lock_guard<std::mutex>{clientp2->progress_bar_mutex}};
			if(dltotal == 0) {
				clientp2->progress_bar = 0;
			} else {
				clientp2->progress_bar = ((static_cast<float>(dlnow) / dltotal) + clientp2->i) / clientp2->count_libs;
			}
			return 0;
		}
	
	
		auto download(
			std::mutex& progress_bar_mutex,
			float& progress_bar,
			std::u32string& text_error,
			size_t count_libs,
			const std::string& url,
			const std::filesystem::path& path,
			size_t i
		) -> bool {
			auto result{true};
			if(!std::filesystem::exists(path)){
				if(CURL* curl{curl_easy_init()}; curl) {
					auto progress_bar_data{Progress_bar_data{progress_bar, progress_bar_mutex, 0, count_libs, i}};
					auto write_data{Write_data{nullptr, path}};
					
					curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
					curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
					curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
					
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_data);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
					
					curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &progress_bar_data);
					curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
					
					auto res{curl_easy_perform(curl)};
					if(res != CURLE_OK) {
						text_error = U"downloading `" + to_utf32(url) + U"` end with an error: " + to_utf32(curl_easy_strerror(res));
						result = false;
					}
					
					curl_easy_cleanup(curl);
					if(write_data.file) {
						fclose(write_data.file);
					}
				} else {
					text_error = to_utf32("easy curl init for `" + url + "` is not possible");
					result = false;
				}
			}
			return result;
		}
	}
	
	BoxModulesLoader::Make::Make(
		std::filesystem::path lib_dir,
		std::vector<LibsOneType> libs,
		BoxPtr<IScalable::Make>&& object,
		MakeDyn<ISMRFloat> progress_bar_value,
		MakeDyn<ISMString> text_error_value,
		orl::Option<ieml::Node> object_node,
		sf::Vector2f min_size
	) :
		lib_dir(std::move(lib_dir)),
		libs(std::move(libs)),
		object(std::move(object)),
		progress_bar_value(std::move(progress_bar_value)),
		text_error_value(std::move(text_error_value)),
		object_node(std::move(object_node)),
		min_size(min_size) {
	}
	
	BoxModulesLoader* BoxModulesLoader::Make::make(InitInfo init_info) {
		return new BoxModulesLoader{std::move(*this), init_info};
	}
	
	BoxModulesLoader::BoxModulesLoader(
		Make && make,
		InitInfo init_info
	) :
		Box(make.min_size),
		progress_bar_(0),
		progress_bar_value_(make.progress_bar_value.make(SInitInfo{init_info})),
		text_error_value_(make.text_error_value.make(SInitInfo{init_info})),
		status_load_libs_(
			[&make]{
				if(make.object_node.is_some()){
					return Status::Load;
				}
				return Status::Finish;
			}()
		),
		load_object_(!make.object_node.is_some()),
		object_node_(std::move(make.object_node)),
		download_thread_(
			[this, start = make.object_node.is_some(), &libs_buff = make.libs, &lib_dir_buff = make.lib_dir]() -> orl::Option<std::thread> {
				if(start) {
					return std::thread {
						[this, &libs_buff, &lib_dir_buff] {
							auto libs{libs_buff};
							auto lib_dir{lib_dir_buff};
							
							auto count_libs{size_t{0}};
							for(auto const& lib_one_type: libs) {
								count_libs += lib_one_type.urls.size();
							}
							
							auto download_libs_fn{
								[this, &count_libs, &lib_dir](std::vector<std::string>& urls, std::vector<std::filesystem::path>& paths) -> bool{
									auto names_correcter_fn{
										[](auto& strings){
											for(auto& string : strings) {
												auto string_str{static_cast<std::string>(string)};
												auto cursor{size_t{string_str.find('$')}};
												while(cursor != std::string::npos){
													if(cursor > 0 && string_str[cursor - 1] == '\\') {
														if(cursor > 1 && string_str[cursor - 2] == '\\') {
															string_str.erase(cursor - 2, 3);
															string_str.insert(cursor - 2, "\\$");
														} else {
															string_str.erase(cursor - 1, 2);
															string_str.insert(cursor - 1, "$");
														}
													} else {
														string_str.erase(cursor, 1);
														string_str.insert(cursor, std::string{"-"} + std::string{IE_COMMIT_HASH} + open_lib::get_extension());
													}
													cursor = string_str.find('$', cursor);
												}
												string = string_str;
											}
										}
									};
									
									names_correcter_fn(urls);
									for(auto i = size_t{0}; i < urls.size(); i++) {
										auto url{urls[i]};
										auto file_name{lib_dir.string() + std::to_string(std::hash<std::string>{}(url)) + open_lib::get_extension()};
										if(!detail::download(progress_bar_mutex_, progress_bar_, text_error_, count_libs, url, file_name, i)) {
											status_load_libs_.store(Status::Error, std::memory_order_relaxed);
											return false;
										}
										auto exception_size{open_lib::get_extension().size()};
										paths.emplace_back(file_name.erase(file_name.size() - exception_size, exception_size));
									}
									return true;
								}
							};
							
							for(auto& libs_one_type: libs) {
								switch(libs_one_type.lib_type) {
									case LibType::CLib : {
										for(auto& lib_path: libs_one_type.paths) {
											lib_path = lib_dir.string() + lib_path.string() + std::string{"-"} + std::string{IE_COMMIT_HASH};
										}
										if(!download_libs_fn(libs_one_type.urls, libs_one_type.paths)) {
											return;
										}
										for(auto& lib_path: libs_one_type.paths) {
											try {
												dls.emplace_back(lib_path).get_sim<void (*)()>("init")();
											} catch (std::runtime_error const& error) {
												text_error_ = ie::to_utf32(error.what());
												status_load_libs_.store(Status::Error, std::memory_order_relaxed);
												return;
											}
										}
									}
								}
							}
							status_load_libs_.store(Status::Finish, std::memory_order_relaxed);
						}
					};
				}
				return {};
			}()
		),
		init_info_(
			[&make, &init_info] () -> orl::Option<InitInfo>{
				if(make.object_node.is_some()){
					return init_info;
				}
				return {};
			}()
		),
		object_(make.object->make(init_info)) {
		init_info.update_manager.add(*this);
		progress_bar_value_.set_bounds(0, 1);
	}

	void BoxModulesLoader::update() {
		if(!load_object_) {
			switch(status_load_libs_.load(std::memory_order_relaxed)) {
				case Status::Load: {
					auto lock_progress_bar{std::lock_guard<std::mutex>{progress_bar_mutex_}};
					progress_bar_value_.set(progress_bar_);
					break;
				}
				case Status::Error: {
					text_error_value_.set(text_error_);
					download_thread_.some().join();
					load_object_ = true;
					break;
				}
				case Status::Finish: {
					load_object_ = true;
					progress_bar_value_.set(1);
					object_.set(object_node_.some().as<ie::BoxPtr<ie::IScalable::Make> >().except()->make(init_info_.some()));
					object_->resize(get_size(), get_position());
					download_thread_.some().join();
					break;
				}
			}
		}
	}

	auto BoxModulesLoader::get_object() const -> const IScalable& {
		return *object_;
	}
	
	auto BoxModulesLoader::get_object() -> IScalable& {
		return *object_;
	}
}

auto ieml::Decode<char, ie::BoxModulesLoader::Status>::decode(ieml::Node const& node) -> orl::Option<ie::BoxModulesLoader::Status>{
	auto& str{node.get_clear().get_string().except()};
	if(str == "load") {
		return ie::BoxModulesLoader::Status::Load;
	} else if(str == "error") {
		return ie::BoxModulesLoader::Status::Error;
	} else if(str == "finish") {
		return ie::BoxModulesLoader::Status::Finish;
	}
	return {};
}

auto ieml::Decode<char, ie::BoxModulesLoader::LibsOneType>::decode(ieml::Node const& node) -> orl::Option<ie::BoxModulesLoader::LibsOneType>{
	
	auto lib_type{ie::BoxModulesLoader::LibType::CLib};
	auto lib_type_str{node.get_tag().except()};
	if(lib_type_str == "CLib"){
		lib_type = ie::BoxModulesLoader::LibType::CLib;
	}
	
	auto map{node.get_map_view().except()};
	auto urls_load_string{map.get_as<std::vector<ie::LoadString> >("urls").except().ok_or({})};
	auto urls_string{std::vector<std::string>{urls_load_string.size()}};
	std::transform(urls_load_string.begin(), urls_load_string.end(), urls_string.begin(), [](auto load_string){return load_string.str;});
	
	return ie::BoxModulesLoader::LibsOneType{
		lib_type,
		map.get_as<std::vector<std::filesystem::path> >("paths").except().ok_or({}),
		urls_string
	};
}

auto ieml::Decode<char, ie::BoxModulesLoader::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxModulesLoader::Make>{
	auto map{node.get_map_view().except()};
	auto libs{map.get_as<std::vector<ie::BoxModulesLoader::LibsOneType> >("libs").except().ok_or({})};
	return ie::BoxModulesLoader::Make{
		map.get_as<std::filesystem::path>("lib-dir").except().ok_or("./"),
		libs,
		[&map, &libs]{
			if(libs.empty()) {
				return map.at("object").except().as<bp::BoxPtr<ie::IScalable::Make> >().except();
			}
			return map.get_as<ie::BoxPtr<ie::IScalable::Make> >("progress-bar").except().ok_or_else([] {
				return bp::make_box_ptr<ie::Empty::Make>(ie::Empty::Make{});
			});
		}(),
		map.get_as<ie::MakeDyn<ie::ISMRFloat> >("progress-bar-value").except().ok_or_else([]{
			return ie::MakeDyn<ie::ISMRFloat>{bp::make_box_ptr<ie::SMRFloat::Make>(0.f)};
		}),
		map.get_as<ie::MakeDyn<ie::ISMString> >("text-error-value").except().ok_or_else([]{
			return ie::MakeDyn<ie::ISMString>{bp::make_box_ptr<ie::SMString::Make>(U"")};
		}),
		[&map, &libs]() -> orl::Option<ieml::Node>{
			if(libs.empty()){
				return {};
			}
			return map.at("object").except();
		}(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}