#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
    {
        // Create a panel to hold the buttons and panels
        mainPanel = new wxPanel(this, wxID_ANY);

        // Create two panels
        configPanel = new wxPanel(mainPanel, wxID_ANY);
        vectorPanel = new wxPanel(mainPanel, wxID_ANY);
        graphPanel = new wxPanel(mainPanel, wxID_ANY);

        // Create two buttons
        vectorButton = new wxButton(mainPanel, wxID_ANY, "Vector Algorithms");
        graphButton = new wxButton(mainPanel, wxID_ANY, "Graph Algorithms");

        // Set panels background colors
        vectorPanel->SetBackgroundColour(wxColour(200, 100, 100));
        graphPanel->SetBackgroundColour(wxColour(100, 100, 200));

        // Create labels for the panels
        vectorLabel = new wxStaticText(vectorPanel, wxID_ANY, "Vector Algorithms Panel");
        graphLabel = new wxStaticText(graphPanel, wxID_ANY, "Graph Algorithms Panel");

        // Create a sizer to vertically align config panels
        wxBoxSizer *configSizer = new wxBoxSizer(wxVERTICAL);
        configSizer->Add(vectorButton, 0, wxALL, 5);
        configSizer->Add(graphButton, 0, wxALL, 5);
        configPanel->SetSizer(configSizer);

        // Create a sizer to vertically align config panels
        wxBoxSizer *panelsSizer = new wxBoxSizer(wxVERTICAL);
        panelsSizer->Add(vectorPanel, 1, wxEXPAND | wxALL, 5);
        panelsSizer->Add(graphPanel, 1, wxEXPAND | wxALL, 5);
        vectorPanel->SetSizer(panelsSizer);
        graphPanel->SetSizer(panelsSizer);

        // Create a sizer to manage the layout
        wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
        mainSizer->Add(configPanel, 1, wxEXPAND | wxALL, 5);
        mainSizer->Add(graphPanel, 1, wxEXPAND | wxALL, 5);

        // Set the sizer for the main panel
        mainPanel->SetSizer(mainSizer);

        // Event handling
        vectorButton->Bind(wxEVT_BUTTON, &MyFrame::OnVectorButtonClick, this);
        graphButton->Bind(wxEVT_BUTTON, &MyFrame::OnGraphButtonClick, this);
    }

    void OnVectorButtonClick(wxCommandEvent &event)
    {
        vectorPanel->Show();
        graphPanel->Hide();
        mainPanel->Layout();
    }

    void OnGraphButtonClick(wxCommandEvent &event)
    {
        graphPanel->Show();
        vectorPanel->Hide();
        mainPanel->Layout();
    }

private:
    wxPanel *mainPanel;
    wxPanel *configPanel;
    wxButton *vectorButton;
    wxButton *graphButton;
    wxPanel *vectorPanel;
    wxPanel *graphPanel;
    wxStaticText *vectorLabel;
    wxStaticText *graphLabel;
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MyFrame *frame = new MyFrame("Algorithms Switcher", wxPoint(50, 50), wxSize(800, 600));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
