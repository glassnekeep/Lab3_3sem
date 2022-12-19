//
// Created by - on 18.12.2022.
//

#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);
wxIMPLEMENT_WXWIN_MAIN_CONSOLE;

bool App::onInit() {
    auto* mainFrame = new MainFrame("Lab 3");

    return true;
}
