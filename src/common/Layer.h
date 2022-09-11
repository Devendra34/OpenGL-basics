//
// Created by Devendra Varma on 08/09/22.
//

#ifndef OPENGL_BASICS_LAYER_H
#define OPENGL_BASICS_LAYER_H

#include <string>
#include <utility>

class Layer {
public:
    explicit Layer(std::string name = "Layer") : m_DebugName(std::move(name)) {}

    virtual ~Layer() = default;

    virtual void OnAttach() = 0;

    virtual void Render() = 0;

    virtual void OnDetach() = 0;

//    virtual void OnEvent(EventSystem& event) {}

    const std::string &GetName() { return m_DebugName; }

protected:
    std::string m_DebugName;
};

#endif //OPENGL_BASICS_LAYER_H
