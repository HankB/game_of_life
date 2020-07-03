/*
Graphical "main" for the Game of Life simulation.

Borrowing heavily form the .../wxwidgets/samples/drawing/drawing.cpp example code
*/

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/artprov.h"
#include "wx/dcbuffer.h"
#include "wx/overlay.h"

#include <list>

#include "../res/sample.xpm"

// Our application class
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();

    //virtual int OnExit() { return 0; }

protected:
};

class MyCanvas;

// main window
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnShow(wxCommandEvent &event);

    MyCanvas *m_canvas;

private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};

// scrollable window to draw on
// define a scrollable canvas for drawing onto
class MyCanvas : public wxScrolledWindow
{
public:
    MyCanvas(MyFrame *parent);
    void OnPaint(wxPaintEvent &event);
    void Draw(wxDC &dc);

protected:
    void DrawCell(wxDC &dc, const wxPoint &coord, int r);

private:
    MyFrame *m_owner;

    wxIcon m_std_icon;
    wxDECLARE_EVENT_TABLE();
};

// IDs for the controls and the menu commands
enum
{
    // menu items
    File_Quit = wxID_EXIT,
    File_About = wxID_ABOUT,

    MenuShow_First = wxID_HIGHEST,
    File_ShowDefault = MenuShow_First,
    MenuShow_Last = File_ShowDefault,

    MenuOption_First,
};

IMPLEMENT_APP(MyApp)

static const size_t window_width = 800;
static const size_t window_height = 600;
static const size_t cell_radius = 5;
// Application

// `Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Create the main application window
    MyFrame *frame = new MyFrame(wxT("Conway's Game of Life"),
                                 wxDefaultPosition, wxSize(window_width, window_height));

    // Show it
    frame->Show(true);
    return true;
}

wxBEGIN_EVENT_TABLE(MyCanvas, wxScrolledWindow)
    EVT_PAINT(MyCanvas::OnPaint)
        wxEND_EVENT_TABLE()

            ; // gratuitous semicolon to sort automatic formatting

// construct drawing canvas

MyCanvas::MyCanvas(MyFrame *parent)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                       wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
    m_owner = parent;
    m_std_icon = wxArtProvider::GetIcon(wxART_INFORMATION);
    wxPoint currentpoint = wxPoint(50, 50);
    //add(currentpoint);
}

// draw circle, rec outline and green fill
void MyCanvas::DrawCell(wxDC &dc, const wxPoint &coord, int r)
{
    dc.SetPen(*wxRED_PEN);
    dc.SetBrush(*wxGREEN_BRUSH);
    dc.DrawCircle(coord.x, coord.y, r);
}

// time to paint canvas
void MyCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    wxBufferedPaintDC bpdc(this);
    bpdc.Clear();
    bpdc.SetMapMode(wxMM_TEXT);
    wxPoint origin = wxPoint(20,20);
    DrawCell(bpdc, origin, cell_radius);
}

// Event table to connect widgets with handlers

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(File_Quit, MyFrame::OnQuit)
        EVT_MENU(File_About, MyFrame::OnAbout)
            EVT_MENU_RANGE(MenuShow_First, MenuShow_Last, MyFrame::OnShow)

                wxEND_EVENT_TABLE()

                    ; // gratuitous semicolon to sort automatic formatting

// frame constructor
MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size,
              wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)
{
    // set the frame icon
    SetIcon(wxICON(sample));

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(File_About, wxT("&About\tCtrl-A"), wxT("Show about dialog"));
    menuFile->AppendSeparator();
    menuFile->Append(File_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, wxT("&File"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));

    m_canvas = new MyCanvas(this);
    m_canvas->SetScrollbars(10, 10, 100, 240);
}

void MyFrame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnShow(wxCommandEvent &event)
{
    Refresh();
}

void MyFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
    wxString msg;
    msg.Printf(wxT("Demonstration of Conway's Game of Life.\n")
                   wxT("Thank you John Conway.\n")
                       wxT("Rest in Peace\n")
                           wxT("Copyright (c) Hank Barta 2020"));

    wxMessageBox(msg, wxT("About Game of Life"), wxOK | wxICON_INFORMATION, this);
}
