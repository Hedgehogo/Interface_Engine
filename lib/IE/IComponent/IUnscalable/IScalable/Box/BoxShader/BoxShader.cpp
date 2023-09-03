#include "BoxShader.hpp"

namespace ie {
	uint convertTransmissionDef(const YAML::Node& node) {
		uint transmission{};
		if(node) {
			std::map<std::string, BoxShader::Transmission> transmissionMap{
				{"size",          BoxShader::Transmission::Size},
				{"texture",       BoxShader::Transmission::Texture},
				{"aspectRatio",   BoxShader::Transmission::AspectRatio},
				{"mousePosition", BoxShader::Transmission::MousePosition},
				{"time",          BoxShader::Transmission::Time},
			};
			
			if(node.IsScalar()) {
				std::string strTransmission = node.as<std::string>();
				transmission = transmissionMap[strTransmission];
			} else if(node.IsSequence()) {
				std::string strTransmission;
				for(const auto& item: node) {
					strTransmission = item.as<std::string>();
					transmission = static_cast<BoxShader::Transmission>(transmission | transmissionMap[strTransmission]);
				}
			}
		}
		return transmission;
	}
	
	BoxShader::Make::Make(
		BoxPtr<IScalable::Make>&& object,
		sf::Shader* shader,
		uint transmission,
		std::map<std::string, PISfloat> valuesF,
		std::map<std::string, PISint> valuesI,
		std::map<std::string, PISbool> valuesB,
		std::map<std::string, PISValue<sf::Color>> valuesC,
		std::map<std::string, PSRVec2f> valuesV,
		bool optimize,
		sf::Vector2f minSize
	) :
		BoxRenderTexture::Make(std::move(object), optimize, minSize),
		shader(shader),
		transmission(transmission),
		valuesF(valuesF),
		valuesI(valuesI),
		valuesB(valuesB),
		valuesC(valuesC),
		valuesV(valuesV) {
	}
	
	BoxShader* BoxShader::Make::make(InitInfo initInfo) {
		return new BoxShader{std::move(*this), initInfo};
	}
	
	BoxShader::BoxShader(Make&& make, InitInfo initInfo) :
		BoxRenderTexture(std::move(make.object), make.optimize, make.minSize, initInfo),
		shader(make.shader),
		transmission(make.transmission) {
		auto addSetters = [&](auto& values) {
			for(auto& pair: values) {
				pair.second->addSetter([&](auto var) {
					setUniform(pair.first, var);
				});
			}
		};
		
		addSetters(make.valuesF);
		addSetters(make.valuesI);
		addSetters(make.valuesB);
		addSetters(make.valuesC);
		addSetters(make.valuesV);
	}
	
	BoxShader::BoxShader(
		BoxPtr<IScalable>&& object, sf::Shader* shader, uint transmission,
		std::map<std::string, PISfloat> valuesF,
		std::map<std::string, PISint> valuesI,
		std::map<std::string, PISbool> valuesB,
		std::map<std::string, PISValue<sf::Color>> valuesC,
		std::map<std::string, PSRVec2f> valuesV,
		bool optimize, sf::Vector2f minSize
	) : BoxRenderTexture(std::move(object), optimize, minSize), shader(shader), transmission(transmission) {
		auto addSetters = [&](auto& values) {
			for(auto& pair: values) {
				pair.second->addSetter([&](auto var) {
					setUniform(pair.first, var);
				});
			}
		};
		
		addSetters(valuesF);
		addSetters(valuesI);
		addSetters(valuesB);
		addSetters(valuesC);
		addSetters(valuesV);
	}
	
	BoxShader::~BoxShader() {
		delete shader;
	}
	
	void BoxShader::setUniform(std::string name, float var) {
		shader->setUniform(name, var);
	}
	
	void BoxShader::setUniform(std::string name, int var) {
		shader->setUniform(name, var);
	}
	
	void BoxShader::setUniform(std::string name, bool var) {
		shader->setUniform(name, var);
	}
	
	void BoxShader::setUniform(std::string name, sf::Color var) {
		shader->setUniform(name, sf::Glsl::Vec4{var});
	}
	
	void BoxShader::setUniform(std::string name, sf::Vector2f var) {
		shader->setUniform(name, var);
	}
	
	void BoxShader::setSize(sf::Vector2f size) {
		if(transmission & Transmission::Size)
			shader->setUniform("size", size);
		if(transmission & Transmission::AspectRatio)
			shader->setUniform("aspectRatio", size.x / size.y);
		layout.setSize(size);
	}
	
	void BoxShader::draw() {
		if(!optimize || active || interactionManager->isBlocked()) {
			renderTexture.clear(sf::Color(0, 0, 0, 0));
			drawManager.draw();
			renderTexture.display();
			sprite.setTexture(renderTexture.getTexture());
			active = false;
		}
		if(transmission & Transmission::Time)
			shader->setUniform("time", clock.getElapsedTime().asSeconds());
		if(transmission & Transmission::Texture)
			shader->setUniform("texture", renderTexture.getTexture());
		renderTarget->draw(sprite, shader);
	}
	
	void BoxShader::resize(sf::Vector2f size, sf::Vector2f position) {
		if(transmission & Transmission::Size)
			shader->setUniform("size", size);
		if(transmission & Transmission::AspectRatio)
			shader->setUniform("aspectRatio", size.x / size.y);
		BoxRenderTexture::resize(size, position);
	}
	
	bool BoxShader::updateInteractions(sf::Vector2f mousePosition) {
		if(transmission & Transmission::MousePosition)
			shader->setUniform("mousePosition", mousePosition - layout.position);
		return BoxRenderTexture::updateInteractions(mousePosition);
	}
	
	BoxShader* BoxShader::copy() {
		return new BoxShader{*this};
	}
	
	template<typename T>
	auto getSValuesDef(const YAML::Node& node) {
		std::map<std::string, std::shared_ptr<T> > result;
		if(node) {
			for(auto& pair: node) {
				result.insert(std::make_pair(pair.first.as<std::string>(), Buffer::get<T>(pair.second)));
			}
		}
		return result;
	}
	
	bool DecodePointer<BoxShader>::decodePointer(const YAML::Node& node, BoxShader*& boxWithShader) {
		sf::Shader* shader{new sf::Shader{}};
		if(node["shader"]) {
			node["shader"] >> *shader;
		}
		boxWithShader = new BoxShader{
			node["object"].as < BoxPtr < IScalable > > (),
			shader,
			convertTransmissionDef(node["transmission"]),
			getSValuesDef<ISfloat>(node["values-f"]),
			getSValuesDef<ISint>(node["values-i"]),
			getSValuesDef<ISbool>(node["values-b"]),
			getSValuesDef<ISValue<sf::Color> >(node["values-c"]),
			getSValuesDef<SRVec2f>(node["values-v"]),
			convDef(node["optimize"], true),
			convDef(node["min-size"], sf::Vector2f{})
		};
		return true;
	}
}
