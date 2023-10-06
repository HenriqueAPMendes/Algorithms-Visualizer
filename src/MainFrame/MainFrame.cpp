#include "MainFrame.hpp"

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxPanel *panel = new wxPanel(this);
    basicListView = new wxListView(panel);
    basicListView->AppendColumn("ID");
    basicListView->AppendColumn("Name");
    basicListView->AppendColumn("Description");
    basicListView->SetColumnWidth(0, 80);
    basicListView->SetColumnWidth(1, 120);
    basicListView->SetColumnWidth(2, 600);

    basicListView->Bind(wxEVT_LIST_COL_CLICK, [this](wxListEvent &e)
                        { this->sortByColumn(e.GetColumn()); });

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(basicListView, 1, wxALL | wxEXPAND, 0);
    panel->SetSizerAndFit(sizer);

    populateListView();
}

// Populate list
void MyFrame::populateListView()
{
    addSingleItem(123, "Some Item", "This is an item");
    addSingleItem(456, "Other Item", "A different item");
    addSingleItem(102, "Another Item", "The best one!");
}

// Adds one item to the list
void MyFrame::addSingleItem(int id, const string &name, const string &description)
{
    int index = basicListView->GetItemCount();

    basicListView->InsertItem(index, to_string(id));
    basicListView->SetItem(index, 1, name);
    basicListView->SetItem(index, 2, description);

    ItemData data{id, name, description};
    auto dataPtr = make_unique<ItemData>(data);

    basicListView->SetItemData(index, reinterpret_cast<wxIntPtr>(dataPtr.get())); // to sort on input

    itemDataBag.insert(move(dataPtr));
}

// List sorting
void MyFrame::sortByColumn(int column)
{
    switch (column)
    {
    case 0:
        basicListView->SortItems(idSortCallback, this->sortDirection);
        break;
    case 1:
        basicListView->SortItems(nameSortCallback, this->sortDirection);
        break;
    case 2:
        basicListView->SortItems(descriptionSortCallback, this->sortDirection);
        break;

    default:
        return;
    }

    basicListView->Refresh();
    this->sortDirection = -this->sortDirection;
}

// Callback functions
int MyFrame::idSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
    return compareInts(reinterpret_cast<ItemData *>(item1)->id, reinterpret_cast<ItemData *>(item2)->id, static_cast<int>(direction));
}

int MyFrame::nameSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
    return compareString(reinterpret_cast<ItemData *>(item1)->name, reinterpret_cast<ItemData *>(item2)->name, static_cast<int>(direction));
}

int MyFrame::descriptionSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
    return compareString(reinterpret_cast<ItemData *>(item1)->description, reinterpret_cast<ItemData *>(item2)->description, static_cast<int>(direction));
}

// Comparations used on callback functions
int MyFrame::compareInts(int i1, int i2, int direction)
{
    return i1 == i2 ? 0 : (i1 < i2 ? -direction : direction);
}

int MyFrame::compareString(const string &s1, const string &s2, int direction)
{
    return s1.compare(s2) * direction;
}
