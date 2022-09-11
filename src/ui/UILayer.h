//
// Created by Devendra Varma on 08/09/22.
//

#ifndef OPENGL_BASICS_UI_LAYER_H
#define OPENGL_BASICS_UI_LAYER_H


#include "../common/Layer.h"
#include <glm.hpp>

struct UIProps {
    glm::vec3 translation = {200.0f, 200.0f, 0.0f};
};

class UILayer : public Layer {
private:

    static void BeginRendering();

    static void EndRendering();

public:
    UIProps uiProps;

    void OnAttach() override;

    void Render() override;

    void OnDetach() override;

};


#endif //OPENGL_BASICS_UI_LAYER_H
