#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <open-lib/DynamicLibrary.hpp>
#include "../Box.hpp"
#include "IE/component/IUpdatable/IUpdatable/IUpdatable.hpp"
#include "IE/shared/ISReadable/ISRanged/SRanged/SRanged.hpp"
#include "IE/component/IComponent/IComponentLayout/IComponentObject/IComponentObject.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/ieml/ieml-basic/ieml-basic.hpp"

namespace ie {
	class BoxModulesLoader : public Box, public virtual IComponentObject, public virtual IUpdatable{
	public:
		enum class Status{
			Load,
			Error,
			Finish,
		};
		
		enum class LibType{
			CLib,
		};
		
		struct LibsOneType{
			LibType lib_type;
			std::vector<std::filesystem::path> paths;
			std::vector<std::string> urls;
		};
		
	struct Make : public Box::Make, public IComponentObject::Make{
			std::filesystem::path lib_dir;
			std::vector<LibsOneType> libs;
			bp::BoxPtr<IScalable::Make> object;
			MakeDyn<ISMRFloat> progress_bar_value;
			MakeDyn<ISMString> text_error_value;
			orl::Option<ieml::Node> object_node;
			sf::Vector2f min_size;
			
			Make(
				std::filesystem::path lib_dir,
				std::vector<LibsOneType> libs,
				BoxPtr<IScalable::Make>&& object,
				MakeDyn<ISMRFloat> progress_bar_value,
				MakeDyn<ISMString> text_error_value,
				orl::Option<ieml::Node> object_node,
				sf::Vector2f min_size
			);
			
			auto make(InitInfo init_info) -> BoxModulesLoader* override;
		};
		
		BoxModulesLoader(Make&& make, InitInfo init_info);
		
		auto update() -> void override;
		
		auto get_object() const -> IScalable const& override;
		
	protected:
		auto get_object() -> IScalable& override;
		
		std::mutex progress_bar_mutex_;
		float progress_bar_;
		ISMRFloat& progress_bar_value_;
		
		std::u32string text_error_;
		ISMString& text_error_value_;
		
		std::atomic<Status> status_load_libs_;
		
		bool load_object_;
		orl::Option<ieml::Node> object_node_;
		orl::Option<std::thread> download_thread_;
		std::vector<open_lib::DL> dls;
		orl::Option<InitInfo> init_info_;
		bp::BoxPtr<IScalable> object_;
	};
}

template<>
struct ieml::Decode<char, ie::BoxModulesLoader::Status> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxModulesLoader::Status>;
};

template<>
struct ieml::Decode<char, ie::BoxModulesLoader::LibsOneType> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxModulesLoader::LibsOneType>;
};

template<>
struct ieml::Decode<char, ie::BoxModulesLoader::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::BoxModulesLoader::Make>;
};