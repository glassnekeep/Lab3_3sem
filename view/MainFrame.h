//
// Created by - on 18.12.2022.
//

#ifndef LAB3_3SEM_MAINFRAME_H
#define LAB3_3SEM_MAINFRAME_H

#include <wx/wx.h>
#include <wx/statline.h>
#include <string>
#include <iostream>
#include "../presenter/Presenter.h"

class MainFrame: public wxFrame {
public:
    MainFrame(const wxString& title);
private:
    wxPanel* panel;
    wxSlider* slider;
    wxStaticText* txtSlider;
    wxTextCtrl* textPrint;
    wxButton* buttonCreateGraph, *buttonTopologicalSort, *buttonConnectivityComponents, *buttonFindShortestPaths, *buttonFindMinimumSkeleton, *buttonPrintGraph, *buttonClearText;
    Presenter presenter;

    void onCreateGraphButtonClicked(wxCommandEvent& event);
    void onTopologicalSortButtonClicked(wxCommandEvent& event);
    void onConnectivityComponentsButtonClicked(wxCommandEvent& event);
    void onFindShortestPathsButtonClicked(wxCommandEvent& event);
    void onFindMinimumSkeletonButtonClicked(wxCommandEvent& event);
    void onPrintGraphButtonClicked(wxCommandEvent& event);
    void onClearTextButtonClicked(wxCommandEvent& event);
};


#endif //LAB3_3SEM_MAINFRAME_H
