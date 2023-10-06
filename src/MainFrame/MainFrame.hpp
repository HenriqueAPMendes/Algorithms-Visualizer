#include <wx/wx.h>
#include <wx/listctrl.h>
using namespace std;

#include <unordered_set>
#include <memory>

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    wxListView *basicListView;

    void populateListView();
    void addSingleItem(int id, const string &name, const string &description);

    void sortByColumn(int column);
    int sortDirection = 1;

    struct ItemData
    {
        int id;
        string name;
        string description;
    };

    unordered_set<unique_ptr<ItemData>> itemDataBag;

    static int compareInts(int i1, int i2, int direction);
    static int compareString(const string &s1, const string &s2, int direction);

    static int idSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
    static int nameSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
    static int descriptionSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
};