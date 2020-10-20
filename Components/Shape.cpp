#include <string>

#include "Shape.h"
#include "Transform.h"

#include "..//Shader.h"
#include "..//GameObject.h"
#include "..//Globals.h"

using namespace glm;


Shape::Shape() : Component(TYPE_SHAPE)
{}

Shape::~Shape()
{
	delete shape;
}

void Shape::Update()
{}

void Shape::Draw(Shader _shader)
{
	Transform* _goTr = static_cast<Transform*>(mpOwner->getComponent(TYPE_TRANSFORM));
	_shader.use();

	mat4 model = mat4(1.0f);
	model = translate(model, _goTr->getPosition());
	model = rotate(model, radians(_goTr->getSpin()), vec3(0.0f, 1.0f, 0.0f));
	model = rotate(model, radians(_goTr->getTilt()), vec3(1.0f, 0.0f, 0.0f));
	model = rotate(model, radians(_goTr->getYaw()), vec3(0.0f, 0.0f, 1.0f));
	model = scale(model, _goTr->getSize());

	int loc = glGetUniformLocation(_shader.ID, "model");
	glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(model));

	shape->Draw(_shader);

	_shader.unuse();
}


void Shape::Serialize(json& j)
{
	shape = pResourceManager->LoadModel((j.get<std::string>()).c_str());
}


