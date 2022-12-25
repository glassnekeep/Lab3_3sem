//
// Created by - on 18.12.2022.
//

#include "MainFrame.h"
#include <wx/wx.h>
#include "../presenter/Presenter.h"

using namespace std;

MainFrame::MainFrame(const wxString &title): wxFrame(nullptr, wxID_ANY, title) {
    panel = new wxPanel(this);
    panel->SetBackgroundColour(*wxLIGHT_GREY);
    txtSlider = new wxStaticText(panel, wxID_ANY, "Number of elements: ", wxPoint(30, 45), wxDefaultSize);
    slider = new wxSlider(panel, wxID_ANY, 6, 6, 50, wxPoint(30, 65), wxSize(200, -1), wxSL_LABELS);
    buttonCreateGraph = new wxButton(panel, wxID_ANY, "Create Graph", wxPoint(30, 110), wxSize(160, -1));
    buttonPrintGraph = new wxButton(panel, wxID_ANY, "Print Graph", wxPoint(30, 140), wxSize(160, -1));
    buttonConnectivityComponents = new wxButton(panel, wxID_ANY, "Connectivity components", wxPoint(30, 170), wxSize(160, -1));
    buttonFindShortestPaths = new wxButton(panel, wxID_ANY, "Shortest paths", wxPoint(30, 200), wxSize(160, -1));
    buttonFindMinimumSkeleton = new wxButton(panel, wxID_ANY, "Minimum skeleton", wxPoint(30, 230), wxSize(160, -1));
    buttonClearText = new wxButton(panel, wxID_ANY, "Clear text", wxPoint(30, 260), wxSize(160, -1));
    textPrint = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(280, 20), wxSize(520, 545), wxTE_MULTILINE);

    buttonCreateGraph -> Bind(wxEVT_BUTTON, &MainFrame::onCreateGraphButtonClicked, this);
    buttonPrintGraph -> Bind(wxEVT_BUTTON, &MainFrame::onPrintGraphButtonClicked, this);
    buttonConnectivityComponents -> Bind(wxEVT_BUTTON, &MainFrame::onConnectivityComponentsButtonClicked, this);
    buttonFindShortestPaths -> Bind(wxEVT_BUTTON, &MainFrame::onFindShortestPathsButtonClicked, this);
    buttonFindMinimumSkeleton -> Bind(wxEVT_BUTTON, &MainFrame::onFindMinimumSkeletonButtonClicked, this);
    buttonClearText -> Bind(wxEVT_BUTTON, &MainFrame::onClearTextButtonClicked, this);
}

void MainFrame::onCreateGraphButtonClicked(wxCommandEvent &event) {
    presenter.generateGraph(slider -> GetValue());
    textPrint -> WriteText("Graph was created\n");
}

void MainFrame::onConnectivityComponentsButtonClicked(wxCommandEvent &event) {
    textPrint -> WriteText(presenter.connectivityComponents());
}

void MainFrame::onFindShortestPathsButtonClicked(wxCommandEvent &event) {
    textPrint -> WriteText(presenter.findShortestPaths());
}

void MainFrame::onFindMinimumSkeletonButtonClicked(wxCommandEvent &event) {
    textPrint -> WriteText(presenter.findTheMinimumSkeleton());
}

void MainFrame::onPrintGraphButtonClicked(wxCommandEvent &event) {
    textPrint -> WriteText(presenter.printGraph());
}

void MainFrame::onClearTextButtonClicked(wxCommandEvent &event) {
    textPrint -> Clear();
}