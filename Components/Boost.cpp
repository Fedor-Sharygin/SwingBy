#include "Boost.h"


void Boost::Serialize(json& j)
{
	auto sp = j.find("speed");
	if (sp != j.end())
		speedBoost = glm::vec3(j["speed"][0].get<float>(),
			j["speed"][1].get<float>(),
			j["speed"][2].get<float>());
}

