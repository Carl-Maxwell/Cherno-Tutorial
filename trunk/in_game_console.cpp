
#include <string>
#include <vector>

#include "mtypedefs.h"
#include "in_game_console.h"

Console::Console() {
  this->console_selected_line = u32(-1);
  this->visible = false;
};

void Console::draw() {
  // TODO need a way to unset selected line ... can probably do so on the console window losing focus.
    ImGui::Begin("Console");
    ImGui::BeginChild("console lines");
    for (u32 i = 0 ; i < the().console_lines.size(); i++) {
      auto line = the().console_lines[i];

      ImGui::PushID(i);

      if (the().console_selected_line == i) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{1.0f, 0.2f, 0.2f, 1.0f});
      }

      ImGui::TextWrapped(line.c_str());

      if (the().console_selected_line == i) {
        ImGui::PopStyleColor();
      }

      if (ImGui::BeginPopupContextItem("context menu")) {
        the().console_selected_line = i;
        ImGui::Text("context menu");
        ImGui::Text(std::to_string(i).c_str());
        ImGui::Separator();
        if (ImGui::MenuItem("Copy text", "", false)) {
          ImGui::SetClipboardText(line.c_str());
        } 
        ImGui::EndPopup();
      }
      ImGui::PopID();
    }
    ImGui::EndChild();
    ImGui::End();
};
