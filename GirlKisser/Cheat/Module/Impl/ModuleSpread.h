﻿#pragma once
#include "../ModuleBase.h"

static GKSlider __spread_coeff = GKSlider("Spread Coefficient", 0, -100, 100, "Spread values too small/large may cause interesting effects!");
static GKModule __spread_modifier = { "No Spread", COMBAT, 0x0, false, { (GKSetting<>*) &__spread_coeff } };

class ModuleSpread : ModuleBase
{
public:
    ModuleSpread() : ModuleBase(&__spread_modifier) {}
    
    void do_module(void* arg) override
    {
        set_float(arg, 0xB8, __spread_coeff.value); // moveScatterCoeff
        set_float(arg, 0x11C, __spread_coeff.value); // moveScatterCoeffZoom
    }
};
