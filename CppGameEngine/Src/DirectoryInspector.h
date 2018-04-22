//
// Created by matha on 26/03/2018.
//
#pragma once

#include <string>
#include <vector>
#include "vendor/imgui/imgui.h"
#include "vendor/tinydir/tinydir.h"
#include "Texture.h"
#include "Model.h"
#include "GameObject.h"


class DirectoryInspector {
private:
    bool show;
    std::vector<Texture*> files;
    int selectedSubmesh = 0;
    int selectedGameObject = 0;

public:
    DirectoryInspector() {
        std::string texturesPath = "res/textures";

        tinydir_dir dir;
        tinydir_open(&dir, texturesPath.c_str());

        while(dir.has_next) {
            tinydir_file file;
            tinydir_readfile(&dir, &file);
            if(strstr(file.extension, "png") || strstr(file.extension, "jpg"))
            files.emplace_back(Texture::GetTexture(file.path));

            tinydir_next(&dir);
        }

        tinydir_close(&dir);
    }

    void Draw(std::vector<GameObject*> gameObjects) {
        ImGui::Begin("Model Inspector", &show, ImGuiWindowFlags_NoNav);
        {
            for (int j = 0; j < gameObjects.size(); ++j) {
                for (int i = 0; i < gameObjects[j]->GetModel()->SubmeshCount(); ++i) {
                    if(ImGui::Button(gameObjects[j]->GetModel()->GetSubmesh(i)->name.c_str())) {
                        selectedSubmesh = i;
                        selectedGameObject = j;
                    }
                }
            }

        }
        ImGui::End();

        ImGui::Begin("Textures", &show, ImGuiWindowFlags_NoNav);
        {
            for (int i = 0; i < files.size(); ++i) {
                if(ImGui::ImageButton((ImTextureID)files[i]->GetTextureId(), {100, 100})) {
                    gameObjects[selectedGameObject]->GetModel()->GetMaterial(selectedSubmesh)->Diffuse = files[i];
                }
            }
        }
        ImGui::End();
    }
};