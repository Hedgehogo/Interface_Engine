#include "yamlBuilderInitializer.h"

namespace ui {
	void yamlBuilderInit() {
		std::locale::global( std::locale( "" ));
		YamlBuilder<OnlyDrawable>::add("Empty", Empty::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("FullColor", FullColor::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("RoundedRectangle", RoundedRectangle::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("Capsule", Capsule::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("Caption", Caption::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("Sprite", Sprite::createFromYaml);
		YamlBuilder<OnlyDrawable>::add("Bar", Bar::createFromYaml);
		YamlBuilder<IScalable>::addSubtype(YamlBuilder<OnlyDrawable>::build);
		YamlBuilder<IUnscalable>::addSubtype(YamlBuilder<IScalable>::build);
	}
	
	YamlBuilderInitializer::YamlBuilderInitializer() {
		yamlBuilderInit();
	}
}