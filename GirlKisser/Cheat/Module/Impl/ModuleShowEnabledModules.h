﻿#pragma once
#include <algorithm>
#include <imgui.h>

#include "../ModuleBase.h"
#include "../../Hooks/Hooks.h"

static BKCModule __array_list = { "Show Enabled Modules", VISUAL, 0x0, true, {} };

static ImU32 color_array = ImGui::ColorConvertFloat4ToU32({0.875f, 0.12f, 0.9f, 1.00f});
static ImU32 color_bg = ImGui::ColorConvertFloat4ToU32({0.00f, 0.00f, 0.00f, 0.85f});

class ModuleArrayList : ModuleBase
{
public:
    ModuleArrayList() : ModuleBase(&__array_list) {}
    
    void do_module(void* arg) override
    {
        ImGui::PushFont(BKCImGuiHooker::arraylist_font);
        
        // ArrayList
        float x = 5;
        float y = 48 * BKCImGuiHooker::scale_factor;
        float size = ImGui::GetFontSize();
        float modc = 0;

        std::vector<BKCModule*> module_list = {};
        for (const auto mod : BKCImGuiHooker::modules) module_list.push_back(mod);
        std::sort(module_list.begin(), module_list.end(), alphabetical_cmp());
        
        for (auto& module : module_list)
        {
            if (module->enabled) modc++;
        }
        ImGui::GetBackgroundDrawList()->AddRectFilled({x, y}, {x + 200 * BKCImGuiHooker::scale_factor, y + modc * (size + 2) + 10}, color_bg, 10);
        for (auto& module : module_list)
        {
            if (module->enabled)
            {
                ImGui::GetBackgroundDrawList()->AddText(NULL, size, {x + 5, y + 2}, color_array, module->name.c_str());
                y += size + 2;
            }
        }
        
        ImGui::PopFont();
    }
private:
    struct alphabetical_cmp
    {
        bool operator() (const BKCModule* mod1, const BKCModule* mod2) const
        {
            return mod1->name.compare(mod2->name) <= 0;
        }
    };
};
