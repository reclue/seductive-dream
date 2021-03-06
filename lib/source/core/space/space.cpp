#include "space/space.h"

#include "app_exceptions.h"
#include "everywhere.h"
#include "transform/transform.h"

#include <iterator>


const glm::mat4 Space::MODEL { 1.0f };


Space::Space() :
    m_scenes {} {}

Space::~Space() {
    m_scenes.Clear();
}

CollectionOf<Scene>& Space::GetScenes() {
    return m_scenes;
}

const CollectionOf<Scene>& Space::GetScenes() const {
    return m_scenes;
}

void Space::Processing() {
    if (!Everywhere::Instance().Get<Input>().IsFocused()) {
        return;
    }

    for (auto& scene : m_scenes.Get()) {
        if (scene) {
            scene->Processing();
        }
    }
}

glm::mat4 Space::ToMatrix() const {
    return Space::MODEL;
}
