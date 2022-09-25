//
// Created by Devendra Varma on 08/09/22.
//

#ifndef OPENGL_BASICS_UI_LAYER_H
#define OPENGL_BASICS_UI_LAYER_H


#include "../common/Layer.h"
#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "WindowHandler.h"
#include "ImSequencer.h"
#include "gtx/quaternion.hpp"

struct UIProps {
    glm::vec3 translation = {0.0f, 0.0f, 1.0f};
    glm::vec3 scale = {1.0f, 1.0f, 1.0f};
    glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
    glm::vec3 cameraTranslation = {0.0f, 0.0f, -600.0f};
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 cameraView = glm::translate(glm::mat4(1.0f), cameraTranslation);

    glm::mat4 model() const {
        auto mat =  glm::translate(glm::mat4(1.0f), translation)
//        mat = glm::rotate(mat, glm::radians(rotation[0]), glm::vec3(1,0,0));
//        mat = glm::rotate(mat, glm::radians(rotation[1]), glm::vec3(0,1,0));
//        mat = glm::rotate(mat, glm::radians(rotation[2]), glm::vec3(0,0,1));
        * glm::toMat4(glm::quat(-glm::radians(rotation)))
          * glm::scale(glm::mat4(1.0f), scale);
//        mat = glm::scale(mat, scale);
        return mat;
    }

    static glm::mat4 proj() {
        auto windowWidth = (float) WindowHandler::getWidth();
        auto windowHeight = (float) WindowHandler::getHeight();
        return glm::perspective(glm::radians(45.0f), windowWidth/windowHeight, 0.1f, 1000.0f);
//        return glm::ortho(0.0f, windowWidth, 0.0f, windowHeight, -1.0f, 1.0f);
    }

};

struct MySequencer : public ImSequencer::SequenceInterface {
public:
    int GetFrameMin() const override { return 0; };

    int GetFrameMax() const override { return 5; };

    int GetItemCount() const override { return 7; };

    void Get(int index, int** start, int** end, int* type, unsigned int* color) override {

    }

};

class UILayer : public Layer {
private:

    static void BeginRendering();

    static void EndRendering();

    void Sample();

public:
    MySequencer sequencer;
    UIProps uiProps;

    void OnAttach() override;

    void Render() override;

    void OnDetach() override;

};


#endif //OPENGL_BASICS_UI_LAYER_H
