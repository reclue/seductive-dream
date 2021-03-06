#include "scene/scene.h"

#include "app_exceptions.h"

#include <iterator>


Scene::Scene() :
    Transformable {},
    m_objects {} {}

Scene::~Scene() {
    m_objects.Clear();
}

CollectionOf<Object>& Scene::GetObjects() {
    return m_objects;
}

const CollectionOf<Object>& Scene::GetObjects() const {
    return m_objects;
}

void Scene::Processing() {
    for (auto& object : m_objects.Get()) {
        if (object) {
            object->SetParentTransform(GetGlobalTransform());
            object->Processing();
        }
    }
}
