#pragma once
#include <scene/Component.h>
#include <scene/TransformComponent.h>

#include <vector>
#include <string>

class Entity {
  std::vector<Component *> components;
  TransformComponent *transformer;
public:
  int genericComponentCount() const { return components.size(); }
  Component *getComponent(int index) const { return components[index]; }

};