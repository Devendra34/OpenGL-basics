//
// Created by Devendra Varma on 08/09/22.
//

#include <iostream>
#include "UILayer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "WindowHandler.h"
#include "ImGuizmo.h"
#include "ImSequencer.h"
#include "gtc/type_ptr.hpp"
#include <glm/gtx/matrix_decompose.hpp>

void UILayer::OnAttach() {
    IMGUI_CHECKVERSION();
    if (ImGui::GetCurrentContext() == nullptr) {
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
        io.ConfigWindowsMoveFromTitleBarOnly = true;


        ImGui_ImplGlfw_InitForOpenGL(WindowHandler::GetMainWindow(), true);
        ImGui_ImplOpenGL3_Init();
    }
}
void UILayer::Render() {
    BeginRendering();

    static bool showDemo = false;

    ImGuizmo::BeginFrame();

    static bool isOpen = true;

#if 0
    auto windowWidth = (float) WindowHandler::getWidth();
    auto windowHeight = (float) WindowHandler::getHeight();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
//    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
    ImGui::Begin("ImGui", &isOpen, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
    ImGui::Checkbox("Show Demo", &showDemo);
    ImGui::DragFloat3("Translation", &uiProps.translation[0]);

    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();

    static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
    static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);


    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
//    ImGuizmo::SetRect(0, 0, WindowHandler::getWidth(), WindowHandler::getHeight());

    auto &props = uiProps;
    float left = ImGui::GetWindowPos().x;
    float right = ImGui::GetWindowSize().x;
    float top = ImGui::GetWindowPos().y;
    float bottom = ImGui::GetWindowSize().y;
    auto identity = glm::ortho(left, right, top, bottom, -1.0f, 1.0f);
    auto mvp = props.proj() * props.view * props.model();
//    ImGuizmo::DrawCubes(&uiProps.view[0][0],&uiProps.proj()[0][0], &mvp[0][0], 1);
//    auto m = &uiProps.model()[0][0];
    auto m = &(uiProps.cameraView * uiProps.model())[0][0];
//    ImGuizmo::DrawCubes(glm::value_ptr(uiProps.cameraView),glm::value_ptr(identity),m, 1);
    ImGuizmo::Manipulate(glm::value_ptr(uiProps.cameraView), glm::value_ptr(identity), mCurrentGizmoOperation, mCurrentGizmoMode, m);

    if (ImGuizmo::IsUsing()) {
        glm::vec3 trans, rotate, scale;
        ImGuizmo::DecomposeMatrixToComponents(m, &trans[0], &rotate[0], &scale[0]);
        uiProps.translation = trans;
//            uiProps.translation = glm::vec3(m[3]);

    }

//    static int currentFrame = 0;
//    static int selectedEntry = 0;
//    static int firstFrame = 0;
//    static bool expanded = true;
//    ImSequencer::Sequencer(&sequencer, &currentFrame, &expanded, &selectedEntry, &firstFrame, ImSequencer::SEQUENCER_EDIT_ALL);

    ImGui::End();
#endif

    if (showDemo) {
        ImGui::ShowDemoWindow(&showDemo);
    }

    Sample();

    EndRendering();
}

void UILayer::OnDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UILayer::BeginRendering() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UILayer::EndRendering() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void UILayer::Sample() {
    ImGuizmo::BeginFrame();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(WindowHandler::getWidth(), WindowHandler::getHeight()));
    ImGui::Begin("Sample", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

    ImGui::PushItemWidth(300);
    ImGui::DragFloat3("Translation", &uiProps.translation[0]);
    ImGui::DragFloat3("Rotation", &uiProps.rotation[0]);
    ImGui::DragFloat3("Scale", &uiProps.scale[0], 0.05f);
    ImGui::PopItemWidth();

    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();

    static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::OPERATION::TRANSLATE);
    static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);

    ImGui::Spacing();
    ImGui::Text("");

    ImGuizmo::SetRect(0, 0, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
    auto identity = glm::mat4(1.0f);

    auto m = &(uiProps.model())[0][0];

    ImGuizmo::Manipulate(glm::value_ptr(uiProps.cameraView), glm::value_ptr(uiProps.proj()), mCurrentGizmoOperation, mCurrentGizmoMode, m);

    ImGuizmo::DrawCubes(glm::value_ptr(uiProps.cameraView), glm::value_ptr(uiProps.proj()), m, 1);
    if (ImGuizmo::IsUsing()) {
        glm::vec3 trans, rotate, scale;
        ImGuizmo::DecomposeMatrixToComponents(m, &trans[0], &rotate[0], &scale[0]);
        auto deltaRotation = rotate - uiProps.rotation;
        uiProps.translation = trans;
        // todo fix rotation
//        uiProps.rotation = glm::degrees(rotate);
//        uiProps.rotation += deltaRotation;
        uiProps.scale = scale;

    }
    ImGui::End();

}
