//
// Created by Devendra Varma on 08/09/22.
//

#ifndef OPENGL_BASICS_UI_LAYER_H
#define OPENGL_BASICS_UI_LAYER_H


#include "../common/Layer.h"

class UILayer : public Layer {
private:

    static void BeginRendering();

    static void EndRendering();

public:
    void OnAttach() override;

    void Render() override;

    void OnDetach() override;

};


#endif //OPENGL_BASICS_UI_LAYER_H
