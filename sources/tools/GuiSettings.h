#ifndef GUISETTINGS_H
#define GUISETTINGS_H

#pragma once
#include "Window.h"
#include "Context.h"
#include "Settings.h"

class GuiSettings
{
public:
    GuiSettings(const Window&  window, 
                const Context& context,
                Settings&      settings);
    ~GuiSettings();

    void update();

private:
    void render();

    Settings& settings_;
};

#endif