#pragma once

#include "../BoxRenderTexture/BoxRenderTexture.hpp"
#include "IE/Modules/yaml-cpp/shared/vector/general/sVector2.hpp"

namespace ie {
	class BoxShader : public BoxRenderTexture {
	public:
		enum Transmission {
			None = 0,
			Texture = 1 << 0,
			MousePosition = 1 << 1,
			Size = 1 << 2,
			AspectRatio = 1 << 3,
			Time = 1 << 4,
		};
		
		struct Make : public BoxRenderTexture::Make {
			sf::Shader* shader;
			uint transmission;
			std::map<std::string, PISfloat> valuesF = {};
			std::map<std::string, PISint> valuesI = {};
			std::map<std::string, PISbool> valuesB = {};
			std::map<std::string, PISValue<sf::Color>> valuesC = {};
			std::map<std::string, PSRVec2f> valuesV = {};
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				sf::Shader* shader,
				uint transmission,
				std::map<std::string, PISfloat> valuesF = {},
				std::map<std::string, PISint> valuesI = {},
				std::map<std::string, PISbool> valuesB = {},
				std::map<std::string, PISValue<sf::Color>> valuesC = {},
				std::map<std::string, PSRVec2f> valuesV = {},
				bool optimize = true,
				sf::Vector2f minSize = {}
			);
			
			BoxShader* make(InitInfo initInfo) override;
		};
		
		BoxShader(Make&& make, InitInfo initInfo);
		
		BoxShader(
			BoxPtr<IScalable>&& object, sf::Shader* shader, uint transmission,
			std::map<std::string, PISfloat> valuesF = {},
			std::map<std::string, PISint> valuesI = {},
			std::map<std::string, PISbool> valuesB = {},
			std::map<std::string, PISValue<sf::Color>> valuesC = {},
			std::map<std::string, PSRVec2f> valuesV = {},
			bool optimize = true, sf::Vector2f minSize = {}
		);
		
		~BoxShader();
		
		void setUniform(std::string name, float var);
		
		void setUniform(std::string name, int var);
		
		void setUniform(std::string name, bool var);
		
		void setUniform(std::string name, sf::Color var);
		
		void setUniform(std::string name, sf::Vector2f var);
		
		void setSize(sf::Vector2f size) override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxShader* copy() override;
	
	protected:
		sf::Shader* shader;
		uint transmission;
		
		sf::Clock clock;
	};
	
	template<>
	struct DecodePointer<BoxShader> {
		static bool decodePointer(const YAML::Node& node, BoxShader*& boxWithShader);
	};
}