// Start of wxWidgets "Hello World" Program
#include <wx/wx.h>
#include <wx/listctrl.h>
using namespace std;

#include <unordered_set>
#include <memory>

#include "MainFrame/MainFrame.hpp"

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

enum
{
    ID_Hello = 1
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
