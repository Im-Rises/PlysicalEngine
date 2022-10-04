#include "Transform.h"

#include "imgui/imgui.h"

Transform::Transform() {
    positionX = 0;
    positionY = 0;
    positionZ = 0;
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;
}

Transform::~Transform() {

}

void Transform::drawGui() {
    ImGui::Text("Position");
    if (ImGui::BeginTable("Position", 3)) {
        ImGui::TableNextColumn();
        ImGui::Text("X:");
        ImGui::SameLine();
        ImGui::InputFloat("##TransformPositionX", &positionX);
        ImGui::TableNextColumn();
        ImGui::Text("Y:");
        ImGui::SameLine();
        ImGui::InputFloat("##TransformPositionY", &positionY);
        ImGui::TableNextColumn();
        ImGui::Text("Z:");
        ImGui::SameLine();
        ImGui::InputFloat("##TransformPositionZ", &positionZ);
        ImGui::EndTable();
    }
    ImGui::Text("Rotation");
    if (ImGui::BeginTable("Rotation", 3)) {
        ImGui::TableNextColumn();
        ImGui::Text("X:");
        ImGui::SameLine();
        ImGui::InputFloat("##TransformRotationX", &rotationX);
        ImGui::TableNextColumn();
        ImGui::Text("Y:");
        ImGui::SameLine();
        ImGui::InputFloat("##TransformRotationY", &rotationY);
        ImGui::TableNextColumn();
        ImGui::Text("Z:");
        ImGui::SameLine();
        ImGui::InputFloat("##TransformRotationZ", &rotationZ);
        ImGui::EndTable();
    }
    ImGui::Text("Scale");
    if (ImGui::BeginTable("Scale", 3)) {
        ImGui::TableNextColumn();
        ImGui::Text("X:");
        ImGui::SameLine();
        ImGui::InputFloat("##TransformScaleX", &scaleX);
        ImGui::TableNextColumn();
        ImGui::Text("Y:");
        ImGui::SameLine();
        ImGui::InputFloat("##TransformScaleY", &scaleY);
        ImGui::TableNextColumn();
        ImGui::Text("Z:");
        ImGui::SameLine();
        ImGui::InputFloat("##TransformScaleZ", &scaleZ);
        ImGui::EndTable();
    }
}
