/////////////////////////////////////////////////////////////////////////////
// Name:        docview.h
// Purpose:     c++ wrapper for the wx Document/View Framework
// Author:      Simon Flack
// Modified by:
// Created:     28/08/2002
// RCS-ID:      
// Copyright:   (c) 2002 Simon Flack
// Licence:     This program is free software; you can redistribute it and/or
//              modify it under the same terms as Perl itself
/////////////////////////////////////////////////////////////////////////////

#include <wx/docview.h>
#if wxUSE_MDI_ARCHITECTURE && wxUSE_DOC_VIEW_ARCHITECTURE
#include "wx/docmdi.h"
#endif

#include "cpp/v_cback.h"


// --- Wx::Document ----------------------------------------------------

class wxPliDocument : public wxDocument
{
    WXPLI_DECLARE_DYNAMIC_CLASS( wxPliDocument );
    WXPLI_DECLARE_V_CBACK();
public:
    WXPLI_DEFAULT_CONSTRUCTOR( wxPliDocument, "Wx::Document", TRUE );

    DEC_V_CBACK_BOOL__VOID( Close );
    DEC_V_CBACK_BOOL__VOID( Save );
    DEC_V_CBACK_BOOL__VOID( SaveAs );
    DEC_V_CBACK_BOOL__VOID( Revert );
    
    // see helpers.h - wxPliInputStream
#if wxUSE_STD_IOSTREAM
    wxSTD ostream& SaveObject( ostream& );
    wxSTD istream& LoadObject( istream& );
#else
    wxOutputStream& SaveObject( wxOutputStream& );
    wxInputStream& LoadObject( wxInputStream& );
#endif
    DEC_V_CBACK_BOOL__WXSTRING( OnSaveDocument );
    DEC_V_CBACK_BOOL__WXSTRING( OnOpenDocument );
    DEC_V_CBACK_BOOL__VOID( OnNewDocument );
    DEC_V_CBACK_BOOL__VOID( OnCloseDocument );

    DEC_V_CBACK_BOOL__VOID( OnSaveModified );

    bool OnCreate( const wxString&, long );
    // ??? OnCreateCommandProcessor/GetCommandProcessor/SetCommandProcessor ???

    DEC_V_CBACK_VOID__VOID( OnChangedViewList );
    DEC_V_CBACK_BOOL__VOID( DeleteContents );

    // ??? Draw() ???

    bool IsModified() const;
    void  Modify( bool );

    bool AddView( wxView* );
    bool RemoveView( wxView* );

    void UpdateAllViews( wxView* sender=NULL, wxObject* = NULL);
#if WXPERL_W_VERSION_GE( 2, 3, 3 )
    DEC_V_CBACK_VOID__VOID( NotifyClosing );
#endif
    DEC_V_CBACK_BOOL__VOID( DeleteAllViews );

    wxDocManager *GetDocumentManager() const;
    wxDocTemplate *GetDocumentTemplate() const;
    void SetDocumentTemplate( wxDocTemplate* );

    bool GetPrintableName( wxString& ) const;

    wxWindow *GetDocumentWindow() const;
};


DEF_V_CBACK_BOOL__VOID( wxPliDocument, wxDocument, Close );
DEF_V_CBACK_BOOL__VOID( wxPliDocument, wxDocument, Save );
DEF_V_CBACK_BOOL__VOID( wxPliDocument, wxDocument, SaveAs );
DEF_V_CBACK_BOOL__VOID( wxPliDocument, wxDocument, Revert );

#if wxUSE_STD_IOSTREAM
wxSTD ostream wxPliDocument::SaveObject( wxSTD ostream& stream )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "SaveObject" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR, "o", &stream );
    }
    return wxDocument::SaveObject( stream );
}

wxSTD istream wxPliDocument::LoadObject( istream& stream )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "LoadObject" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR, "o", &stream );
    }
    return wxDocument::LoadObject( stream );
}
#else
wxOutputStream& wxPliDocument::SaveObject( wxOutputStream& stream )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "SaveObject" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR, "o", &stream );
    }
    return wxDocument::SaveObject( stream );
}

wxInputStream& wxPliDocument::LoadObject( wxInputStream& stream )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "LoadObject" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR, "o", &stream );
    }
    return wxDocument::LoadObject( stream );
}
#endif

bool wxPliDocument::OnSaveDocument( const wxString& filename )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "OnSaveDocument" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "P", &filename);
        bool val = SvTRUE( ret );
        SvREFCNT_dec( ret );
        return val;
    }
      return wxDocument::OnSaveDocument( filename );
}

bool wxPliDocument::OnOpenDocument( const wxString& filename )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "OnOpenDocument" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "P", &filename);
        bool val = SvTRUE( ret );
        SvREFCNT_dec( ret );
        return val;
    }
      return wxDocument::OnOpenDocument( filename );
}

DEF_V_CBACK_BOOL__VOID( wxPliDocument, wxDocument, OnNewDocument );
DEF_V_CBACK_BOOL__VOID( wxPliDocument, wxDocument, OnCloseDocument );
DEF_V_CBACK_BOOL__VOID( wxPliDocument, wxDocument, OnSaveModified );

bool wxPliDocument::OnCreate( const wxString& path, long flags  )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "OnCreate" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "Pl",
                                                     &path, flags);
        bool val = SvTRUE( ret );
        SvREFCNT_dec( ret );
        return val;
    }
      return wxDocument::OnCreate( path, flags );
}


DEF_V_CBACK_VOID__VOID( wxPliDocument, wxDocument, OnChangedViewList );
DEF_V_CBACK_BOOL__VOID( wxPliDocument, wxDocument, DeleteContents );

bool wxPliDocument::IsModified() const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "IsModified" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR );
        bool val = SvTRUE( ret );
        SvREFCNT_dec( ret );
        return val;
    }

    return wxDocument::IsModified();
}

void wxPliDocument::Modify( bool mod )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "Modify" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR, "b", mod );
    }
    wxDocument::Modify( mod );
}

bool wxPliDocument::AddView( wxView *view)
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "AddView" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "O", view );
        bool val = SvTRUE( ret );
        SvREFCNT_dec( ret );
        return val;
    }
    return wxDocument::AddView( view );
}

bool wxPliDocument::RemoveView( wxView *view )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "RemoveView" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "O", view );
        bool val = SvTRUE( ret );
        SvREFCNT_dec( ret );
        return val;
    }
    return wxDocument::RemoveView( view );
}

void wxPliDocument::UpdateAllViews( wxView *sender, wxObject *hint)
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "UpdateAllViews" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR, "OO", sender, hint);
    }
    wxDocument::UpdateAllViews( sender, hint );
}

#if WXPERL_W_VERSION_GE( 2, 3, 3 )
DEF_V_CBACK_VOID__VOID( wxPliDocument, wxDocument, NotifyClosing );
#endif

DEF_V_CBACK_BOOL__VOID( wxPliDocument, wxDocument, DeleteAllViews );

wxDocManager *wxPliDocument::GetDocumentManager() const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "GetDocumentManager" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR );
        wxDocManager* retval =
            (wxDocManager*)wxPli_sv_2_object( aTHX_ ret, "Wx::DocManager" );
        SvREFCNT_dec( ret );

        return retval;
    }
    return wxDocument::GetDocumentManager();
}

wxDocTemplate *wxPliDocument::GetDocumentTemplate() const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "GetDocumentTemplate" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR );
        wxDocTemplate* retval =
            (wxDocTemplate*)wxPli_sv_2_object( aTHX_ ret, "Wx::DocTemplate" );
        SvREFCNT_dec( ret );

        return retval;
    }
    return wxDocument::GetDocumentTemplate();
}

void wxPliDocument::SetDocumentTemplate( wxDocTemplate *temp )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "SetDocumentTemplate" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback, G_SCALAR, "O",
                                           temp );
    }
    wxDocument::SetDocumentTemplate( temp );
}

bool wxPliDocument::GetPrintableName( wxString &buf ) const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "GetPrintableName" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "P", &buf);
        bool val = SvTRUE( ret );
        SvREFCNT_dec( ret );
        return val;
    }
    return wxDocument::GetPrintableName( buf );
}

wxWindow *wxPliDocument::GetDocumentWindow() const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "GetDocumentWindow" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR );

        wxWindow* retval =
          (wxWindow*) wxPli_sv_2_object( aTHX_ ret, "Wx::Window" );
        SvREFCNT_dec( ret );
        return retval;
    }
    return wxDocument::GetDocumentWindow();
}


WXPLI_IMPLEMENT_DYNAMIC_CLASS( wxPliDocument, wxDocument );


// --- Wx::DocTemplate -------------------------------------------------


class wxPliDocTemplate : public wxDocTemplate
{
    WXPLI_DECLARE_DYNAMIC_CLASS( wxPliDocTemplate );
    WXPLI_DECLARE_V_CBACK();
public:
    wxPliDocTemplate( const char* package, wxDocManager* manager,
                      const wxString& descr, const wxString& filter,
                      const wxString& dir, const wxString& ext,
                      const wxString& docTypeName,
                      const wxString& viewTypeName, wxClassInfo* docClassInfo,
                     wxClassInfo* viewClassInfo, long flags)
       : wxDocTemplate(manager, descr, filter, dir, ext, docTypeName,
                     viewTypeName, docClassInfo, viewClassInfo, flags),
         m_callback( "Wx::DocTemplate" )
    {
       m_callback.SetSelf( wxPli_make_object( this, package ), TRUE);
    }
    ~wxPliDocTemplate();

    wxDocument *CreateDocument( const wxString& path, long flags = 0);
    wxView *CreateView( wxDocument*, long );

    wxString GetViewName() const;
    wxString GetDocumentName() const;

    DEC_V_CBACK_BOOL__WXSTRING( FileMatchesTemplate );
};

wxPliDocTemplate::~wxPliDocTemplate() {}

wxDocument *wxPliDocTemplate::CreateDocument( const wxString& path,
                                              long flags )
{

    dTHX;
    wxDocument* doc;

    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "CreateDocument" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR );
        doc = (wxDocument*) wxPli_sv_2_object( aTHX_ ret, "Wx::Document" );
        SvREFCNT_dec( ret );
    }
    else
    {
      delete doc;
      return (wxDocument *) NULL;
    }

    doc->SetFilename(path);
    doc->SetDocumentTemplate(this);
    GetDocumentManager()->AddDocument(doc);
    doc->SetCommandProcessor(doc->OnCreateCommandProcessor());

    if (doc->OnCreate(path, flags))
        return doc;
    else
    {
         if (GetDocumentManager()->GetDocuments().Member(doc))
                  doc->DeleteAllViews();
        return (wxDocument *) NULL;
    }
}



wxView *wxPliDocTemplate::CreateView( wxDocument* doc, long flags )
{
    dTHX;
    wxView* view;

    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "CreateView" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR );
        view = (wxView*) wxPli_sv_2_object( aTHX_ ret, "Wx::View" );
        SvREFCNT_dec( ret );
    }
    else
    {
      delete view;
      return (wxView *) NULL;
    }

    view->SetDocument(doc);
    if (view->OnCreate(doc, flags))
    {
        return view;
    }
    else
    {
        delete view;
        return (wxView *) NULL;
    }
}

wxString wxPliDocTemplate::GetViewName() const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "GetViewName" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR );
        wxString retval;
        WXSTRING_INPUT( retval, wxString, ret );
        SvREFCNT_dec( ret );
        return retval;
    }
    return wxDocTemplate::GetViewName();
}

wxString wxPliDocTemplate::GetDocumentName() const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "GetDocumentName" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR );
        wxString retval;
        WXSTRING_INPUT( retval, wxString, ret );
        SvREFCNT_dec( ret );
        return retval;
    }
    return wxDocTemplate::GetDocumentName();
}

bool wxPliDocTemplate::FileMatchesTemplate( const wxString& path )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "FileMatchesTemplate" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "P", &path );
        bool val = SvTRUE( ret );
        SvREFCNT_dec( ret );
        return val;
    }
    return wxDocTemplate::FileMatchesTemplate( path );
}

WXPLI_IMPLEMENT_DYNAMIC_CLASS( wxPliDocTemplate, wxDocTemplate );






// --- Wx::DocManager -------------------------------------------------


class wxPliDocManager : public wxDocManager
{
    WXPLI_DECLARE_DYNAMIC_CLASS( wxPliDocManager );
    WXPLI_DECLARE_V_CBACK();
public:
    wxPliDocManager(  const char* package, long flags = wxDEFAULT_DOCMAN_FLAGS,
                     bool initialize = TRUE)
       : wxDocManager(flags, initialize),
         m_callback( "Wx::DocManager" )
    {
       m_callback.SetSelf( wxPli_make_object( this, package ), TRUE);
    }
    ~wxPliDocManager();

    bool ProcessEvent( wxEvent& );
    DEC_V_CBACK_VOID__VOID( OnOpenFileFailure );

    wxDocument* CreateDocument( const wxString& path, long flags = 0 );
    wxView* CreateView( wxDocument* doc, long flags = 0 );
    void DeleteTemplate( wxDocTemplate* temp, long flags = 0 );
    bool FlushDoc( wxDocument* );
    wxDocTemplate* MatchTemplate( const wxString& );
    wxDocTemplate* SelectDocumentPath( wxDocTemplate** templates,
                                       int noTemplates, wxString& path,
                                       bool save=FALSE);
    wxDocTemplate* SelectDocumentType( wxDocTemplate** templates,
                                       int noTemplates, bool sort=FALSE);
    wxDocTemplate* SelectViewType( wxDocTemplate** templates, int noTemplates,
                                   bool sort=FALSE );
    wxDocTemplate* FindTemplateForPath( const wxString& );

    void ActivateView( wxView*, bool activate = TRUE, bool deleting = FALSE);
    wxView* GetCurrentView() const;

    bool MakeDefaultName( wxString& );

    wxString MakeFrameTitle( wxDocument* );

    wxFileHistory* OnCreateFileHistory();
    wxFileHistory* GetFileHistory();

    void AddFileToHistory( const wxString& );
    void RemoveFileFromHistory( int );
    int GetNoHistoryFiles() const;
    wxString GetHistoryFile( int ) const;
    void FileHistoryUseMenu( wxMenu* );
    void FileHistoryRemoveMenu( wxMenu* );
#if wxUSE_CONFIG
    // FileHistoryLoad()/Save()
#endif

    void FileHistoryAddFilesToMenu();
    void FileHistoryAddFilesToMenu( wxMenu* );

};

wxPliDocManager::~wxPliDocManager() {}

wxDocument* wxPliDocManager::CreateDocument( const wxString& path, long flags )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "CreateDocument" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR, "Pl", &path, flags );
        wxDocument* retval =
            (wxDocument*)wxPli_sv_2_object( aTHX_ ret, "Wx::Document" );
        SvREFCNT_dec( ret );
        return retval;
    }
    return wxDocManager::CreateDocument( path, flags );
}


wxView* wxPliDocManager::CreateView( wxDocument* doc, long flags )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "CreateView" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "Ol", doc,
                                                     flags );
        wxView* retval =
            (wxView*)wxPli_sv_2_object( aTHX_ ret, "Wx::View" );
        SvREFCNT_dec( ret );
        return retval;
    }
    return wxDocManager::CreateView( doc, flags );
}



void wxPliDocManager::DeleteTemplate( wxDocTemplate* temp, long flags )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "DeleteTemplate" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "Ol", &temp,
                                           flags );
                return;
    }
    wxDocManager::DeleteTemplate( temp, flags );
}

bool wxPliDocManager::FlushDoc( wxDocument* doc )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "FlushDoc" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR, "O", doc );
      bool val = SvTRUE( ret );
      SvREFCNT_dec( ret );
      return val;
    }
    return wxDocManager::FlushDoc( doc );
}


wxDocTemplate* wxPliDocManager::MatchTemplate( const wxString& path )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "MatchTemplate" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR, "P", &path );
      wxDocTemplate* retval =
        (wxDocTemplate*)wxPli_sv_2_object( aTHX_ ret, "Wx::DocTemplate" );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxDocManager::MatchTemplate(path);
}

wxDocTemplate* wxPliDocManager::SelectDocumentPath( wxDocTemplate** templates,
                                                    int noTemplate,
                                                    wxString& path,
                                                    bool save)
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "SelectDocumentPath" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR, "OiPb", templates,
                                                   noTemplate, &path, save );
      wxDocTemplate* retval =
        (wxDocTemplate*)wxPli_sv_2_object( aTHX_ ret, "Wx::DocTemplate" );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxDocManager::SelectDocumentPath(templates, noTemplate, path, save);
}


wxDocTemplate* wxPliDocManager::SelectDocumentType( wxDocTemplate** templates,
                                                    int noTemplate,
                                                    bool sort)
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "SelectDocumentType" ) )
    {
      SV *ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR, "Oib", templates,
                                                   noTemplate, sort );
      wxDocTemplate* retval =
        (wxDocTemplate*)wxPli_sv_2_object( aTHX_ ret, "Wx::DocTemplate" );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxDocManager::SelectDocumentType(templates, noTemplate, sort);
}


wxDocTemplate* wxPliDocManager::SelectViewType( wxDocTemplate** templates,
                                                int noTemplate,
                                                bool sort )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "SelectViewType" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR, "Oib", templates,
                                                   noTemplate, sort );
      wxDocTemplate* retval =
        (wxDocTemplate*)wxPli_sv_2_object( aTHX_ ret, "Wx::DocTemplate" );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxDocManager::SelectViewType(templates, noTemplate, sort);
}


wxDocTemplate* wxPliDocManager::FindTemplateForPath( const wxString& path )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "FindTemplateForPath" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR,  "P", &path );
      wxDocTemplate* retval =
        (wxDocTemplate*)wxPli_sv_2_object( aTHX_ ret, "Wx::DocTemplate" );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxDocManager::FindTemplateForPath( path );
}

void wxPliDocManager::ActivateView( wxView* view, bool activate, bool deleting)
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "ActivateView" ) )
    {
      wxPliVirtualCallback_CallCallback( aTHX_ &m_callback, G_SCALAR|G_DISCARD,
                                         "Obb", view, activate, deleting );
      return;
    }
  wxDocManager::ActivateView( view, activate, deleting );
}

wxView* wxPliDocManager::GetCurrentView() const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "GetCurrentView" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,G_SCALAR);
      wxView* retval =
        (wxView*)wxPli_sv_2_object( aTHX_ ret, "Wx::View" );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxDocManager::GetCurrentView();
}

bool wxPliDocManager::MakeDefaultName( wxString& buf )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "MakeDefaultName" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR,
                                                   "P", &buf );
      wxString val;
      WXSTRING_INPUT( val, const char *, ret );
      buf = val;

      bool retval = SvTRUE( ret );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxDocManager::MakeDefaultName( buf );
}

wxString wxPliDocManager::MakeFrameTitle( wxDocument* doc )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "MakeFrameTitle" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR, "O", doc );
      wxString retval;
      WXSTRING_INPUT( retval, wxString, ret );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxDocManager::MakeFrameTitle( doc );
}


DEF_V_CBACK_VOID__VOID( wxPliDocManager, wxDocManager, OnOpenFileFailure );

bool wxPliDocManager::ProcessEvent( wxEvent& event )
{
    dTHX;
        if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                               "ProcessEvent" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "O", &event);
        bool val = SvTRUE( ret );
        SvREFCNT_dec( ret );
        return val;
    }
    return wxDocManager::ProcessEvent( event );
}

wxFileHistory* wxPliDocManager::OnCreateFileHistory()
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "OnCreateFileHistory" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR|G_NOARGS );
      wxFileHistory* retval =
        (wxFileHistory*)wxPli_sv_2_object( aTHX_ ret, "Wx::FileHistory" );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxDocManager::OnCreateFileHistory( );
}
wxFileHistory* wxPliDocManager::GetFileHistory()
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "GetFileHistory" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR|G_NOARGS );
      wxFileHistory* retval =
        (wxFileHistory*)wxPli_sv_2_object( aTHX_ ret, "Wx::FileHistory" );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxDocManager::GetFileHistory( );
}

void wxPliDocManager::AddFileToHistory( const wxString& file )
{
    dTHX;
        if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                               "AddFileToHistory" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR, "P", &file);
        return;
    }
    wxDocManager::AddFileToHistory( file );
}

void wxPliDocManager::RemoveFileFromHistory( int i )
{
    dTHX;
        if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                               "RemoveFileFromHistory" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "i", i);
        return;
    }
    wxDocManager::RemoveFileFromHistory( i );
}

int wxPliDocManager::GetNoHistoryFiles() const
{
    dTHX;
        if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                               "GetNoHistoryFiles" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR|G_NOARGS);
        int retval = (int)SvIV( ret );
        SvREFCNT_dec( ret );
        return retval;
    }
    return wxDocManager::GetNoHistoryFiles();
}

wxString wxPliDocManager::GetHistoryFile( int i ) const
{
    dTHX;
        if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                               "GetHistoryFile" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "i", i);
        wxString retval;
        WXSTRING_INPUT( retval, wxString, ret );
        SvREFCNT_dec( ret );
        return retval;
    }
    return wxDocManager::GetHistoryFile( i );
}

void wxPliDocManager::FileHistoryUseMenu( wxMenu* menu )
{
    dTHX;
        if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                               "FileHistoryUseMenu" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "O", menu);
        return;
    }
    wxDocManager::FileHistoryUseMenu( menu );
}

void wxPliDocManager::FileHistoryRemoveMenu( wxMenu* menu )
{
    dTHX;
        if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                               "FileHistoryRemoveMenu" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "O", menu);
        return;
    }
    wxDocManager::FileHistoryRemoveMenu( menu );
}

#if wxUSE_CONFIG
    // FileHistoryLoad()/Save()
#endif

void wxPliDocManager::FileHistoryAddFilesToMenu()
{
    dTHX;
        if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                               "FileHistoryAddFilesToMenu" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_NOARGS|G_DISCARD);
        return;
    }
    wxDocManager::FileHistoryAddFilesToMenu( );
}

void wxPliDocManager::FileHistoryAddFilesToMenu( wxMenu* menu )
{
    dTHX;
        if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                               "FileHistoryAddFilesToMenu" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "O", menu);
        return;
    }
    wxDocManager::FileHistoryAddFilesToMenu( menu );
}



WXPLI_IMPLEMENT_DYNAMIC_CLASS( wxPliDocManager, wxDocManager );





// --- Wx::View -------------------------------------------------


class wxPliView : public wxView
{
    WXPLI_DECLARE_DYNAMIC_CLASS( wxPliView );
    WXPLI_DECLARE_V_CBACK();
public:
    wxPliView( const char* package )
       : wxView(),
         m_callback( "Wx::View" )
    {
       m_callback.SetSelf( wxPli_make_object( this, package ), TRUE);
    }
    ~wxPliView();

    void OnActivateView( bool, wxView*, wxView* );
    void OnPrint( wxDC*, wxObject* );
    void OnUpdate( wxView* sender, wxObject* hint=(wxObject*) NULL );

#if WXPERL_W_VERSION_GE( 2, 3, 3 )
    DEC_V_CBACK_VOID__VOID( OnClosingDocument );
#endif

    DEC_V_CBACK_VOID__VOID( OnChangeFilename );
    bool OnCreate( wxDocument*, long );
    bool Close( bool deleteWindow = TRUE );
    bool OnClose( bool );

    bool ProcessEvent(wxEvent&);
    void Activate( bool );

    virtual void OnDraw(wxDC* dc);

#if wxUSE_PRINTING_ARCHITECTURE
    wxPrintout* OnCreatePrintout();
#endif
};

wxPliView::~wxPliView() {}

void wxPliView::OnDraw( wxDC* dc )
{
}

void wxPliView::OnActivateView( bool activate, wxView* activeView,
                                wxView* deactiveView)
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "OnActivateView" ) )
    {
      wxPliVirtualCallback_CallCallback( aTHX_ &m_callback, G_SCALAR|G_DISCARD,
                                         "bOO", activate, activeView,
                                         deactiveView);
      return;
    }
  wxView::OnActivateView( activate, activeView, deactiveView);
}


void wxPliView::OnPrint( wxDC* dc, wxObject* info)
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "OnPrint" ) )
    {
      wxPliVirtualCallback_CallCallback( aTHX_ &m_callback, G_SCALAR|G_DISCARD,
                                         "OO", dc, info );
      return;
    }
  wxView::OnPrint( dc, info);
}

void wxPliView::OnUpdate( wxView* sender, wxObject* hint )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "OnUpdate" ) )
    {
      wxPliVirtualCallback_CallCallback( aTHX_ &m_callback, G_SCALAR|G_DISCARD,
                                         "OO", sender, hint );
      return;
    }
  wxView::OnUpdate( sender, hint );
}

#if WXPERL_W_VERSION_GE( 2, 3, 3 )
DEF_V_CBACK_VOID__VOID( wxPliView, wxView, OnClosingDocument );
#endif

DEF_V_CBACK_VOID__VOID( wxPliView, wxView, OnChangeFilename );

bool wxPliView::OnCreate( wxDocument* doc, long flags )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "OnCreate" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR,"Ol", doc, flags );
      bool val = SvTRUE( ret );
      SvREFCNT_dec( ret );
      return val;
    }
  return wxView::OnCreate( doc, flags );
}


bool wxPliView::Close( bool deleteWindow )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "Close" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR, "b",
                                                   deleteWindow );
      bool val = SvTRUE( ret );
      SvREFCNT_dec( ret );
      return val;
    }
  return wxView::Close( deleteWindow );
}


bool wxPliView::OnClose( bool deleteWindow )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "OnClose" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR, "b",
                                                   deleteWindow );
      bool val = SvTRUE( ret );
      SvREFCNT_dec( ret );
      return val;
    }
  return wxView::OnClose( deleteWindow );
}

bool wxPliView::ProcessEvent(wxEvent& event)
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "ProcessEvent" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "O", &event);
        bool val = SvTRUE( ret );
        SvREFCNT_dec( ret );
        return val;
    }
  return wxView::ProcessEvent( event );
}


void wxPliView::Activate( bool activate )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "Activate" ) )
    {
      wxPliVirtualCallback_CallCallback( aTHX_ &m_callback, G_SCALAR|G_DISCARD,
                                         "b", activate );
      return;
    }
  wxView::Activate( activate );
}


#if wxUSE_PRINTING_ARCHITECTURE
wxPrintout* wxPliView::OnCreatePrintout()
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "OnCreatePrintout" ) )
    {
      SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                   G_SCALAR);
      wxPrintout* retval =
        (wxPrintout*)wxPli_sv_2_object( aTHX_ ret, "Wx::Printout" );
      SvREFCNT_dec( ret );
      return retval;
    }
  return wxView::OnCreatePrintout( );
}
#endif

WXPLI_IMPLEMENT_DYNAMIC_CLASS( wxPliView, wxView );




// --- Wx::DocChildFrame -------------------------------------------------


class wxPliDocChildFrame : public wxDocChildFrame
{
    WXPLI_DECLARE_DYNAMIC_CLASS( wxPliDocChildFrame );
    WXPLI_DECLARE_V_CBACK();
public:
    wxPliDocChildFrame(const char* package, wxDocument* doc, wxView* view,
      wxFrame* parent, wxWindowID id, const wxString& title, const wxPoint&
      pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
      long style = wxDEFAULT_FRAME_STYLE, const wxString& name = "frame")
       : wxDocChildFrame(doc, view, parent, id, title, pos, size, style, name),
         m_callback( "Wx::DocChildFrame" )
    {
       m_callback.SetSelf( wxPli_make_object( this, package ), TRUE);
    }
    ~wxPliDocChildFrame();

};

wxPliDocChildFrame::~wxPliDocChildFrame() {}

WXPLI_IMPLEMENT_DYNAMIC_CLASS( wxPliDocChildFrame, wxDocChildFrame );





// --- Wx::DocParentFrame -------------------------------------------------


class wxPliDocParentFrame : public wxDocParentFrame
{
    WXPLI_DECLARE_DYNAMIC_CLASS( wxPliDocParentFrame );
    WXPLI_DECLARE_V_CBACK();
public:
    wxPliDocParentFrame(const char* package, wxDocManager* manager,
      wxFrame *parent, wxWindowID id, const wxString& title,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE,
      const wxString& name = "frame")
       : wxDocParentFrame(manager, parent, id, title, pos, size, style, name),
         m_callback( "Wx::DocParentFrame" )
    {
       m_callback.SetSelf( wxPli_make_object( this, package ), TRUE);
    }
    ~wxPliDocParentFrame();


};

wxPliDocParentFrame::~wxPliDocParentFrame() {}

WXPLI_IMPLEMENT_DYNAMIC_CLASS( wxPliDocParentFrame, wxDocParentFrame );




// --- Wx::DocMDIChildFrame -------------------------------------------------

#if wxUSE_MDI_ARCHITECTURE && wxUSE_DOC_VIEW_ARCHITECTURE

class wxPliDocMDIChildFrame : public wxDocMDIChildFrame
{
    WXPLI_DECLARE_DYNAMIC_CLASS( wxPliDocMDIChildFrame );
    WXPLI_DECLARE_V_CBACK();
public:
    wxPliDocMDIChildFrame(const char* package, wxDocument* doc, wxView* view,
                         wxMDIParentFrame* frame, wxWindowID id,
                          const wxString& title, const wxPoint&
                          pos = wxDefaultPosition,
                          const wxSize& size = wxDefaultSize,
                          long style = wxDEFAULT_FRAME_STYLE,
                          const wxString& name = "frame")
       : wxDocMDIChildFrame(doc, view, frame, id, title, pos,
                            size, style, name),
         m_callback( "Wx::DocMDIChildFrame" )
    {
       m_callback.SetSelf( wxPli_make_object( this, package ), TRUE);
    }
    ~wxPliDocMDIChildFrame();

};

wxPliDocMDIChildFrame::~wxPliDocMDIChildFrame() {}

WXPLI_IMPLEMENT_DYNAMIC_CLASS( wxPliDocMDIChildFrame, wxDocMDIChildFrame );





// --- Wx::DocMDIParentFrame -------------------------------------------------


class wxPliDocMDIParentFrame : public wxDocMDIParentFrame
{
    WXPLI_DECLARE_DYNAMIC_CLASS( wxPliDocMDIParentFrame );
 
    WXPLI_DECLARE_V_CBACK();
public:
    wxPliDocMDIParentFrame(const char* package, wxDocManager* manager,
      wxFrame *parent, wxWindowID id, const wxString& title,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE,
      const wxString& name = "frame")
       : wxDocMDIParentFrame(manager, parent, id, title, pos, size,
                             style, name),
         m_callback( "Wx::DocMDIParentFrame" )
    {
       m_callback.SetSelf( wxPli_make_object( this, package ), TRUE);
    }
    ~wxPliDocMDIParentFrame();

};

wxPliDocMDIParentFrame::~wxPliDocMDIParentFrame() {}


WXPLI_IMPLEMENT_DYNAMIC_CLASS( wxPliDocMDIParentFrame, wxDocMDIParentFrame );

#endif



// --- Wx::FileHistory -------------------------------------------------


class wxPliFileHistory : public wxFileHistory
{
    WXPLI_DECLARE_DYNAMIC_CLASS( wxPliFileHistory );
    WXPLI_DECLARE_V_CBACK();
public:
    wxPliFileHistory(const char* package, int maxfiles = 9)
       : wxFileHistory( maxfiles ),
         m_callback( "Wx::FileHistory" )
    {
       m_callback.SetSelf( wxPli_make_object( this, package ), TRUE);
    }
    ~wxPliFileHistory();

    void AddFileToHistory( const wxString& );
    void RemoveFileFromHistory( int );
    int GetMaxFiles() const;

    void UseMenu( wxMenu* );
    void RemoveMenu( wxMenu* );
   
#if wxUSE_CONFIG
    void Load( wxConfigBase& );
    void Save( wxConfigBase& );
#endif

    void AddFilesToMenu();
    void AddFilesToMenu( wxMenu* );

    wxString GetHistoryFile( int ) const;

    int GetCount() const;

    wxList& GetMenus() const;

};

wxPliFileHistory::~wxPliFileHistory() {}

void wxPliFileHistory::AddFileToHistory( const wxString& file )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "AddFileToHistory" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "P", &file );
        return;
    }
    wxFileHistory::AddFileToHistory( file );
}


void wxPliFileHistory::RemoveFileFromHistory( int i )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "RemoveFileFromHistory" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "i", i );
        return;
    }
    wxFileHistory::RemoveFileFromHistory( i );
}

int wxPliFileHistory::GetMaxFiles() const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "GetMaxFiles" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR);
        int retval = (int)SvIV( ret );
        SvREFCNT_dec( ret );
        return retval;
    }
    return wxFileHistory::GetMaxFiles();
}

void wxPliFileHistory::UseMenu( wxMenu* menu )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "UseMenu" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "O", menu );
        return;
    }
    wxFileHistory:UseMenu( menu );
}

void wxPliFileHistory::RemoveMenu( wxMenu* menu )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "RemoveMenu" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "O", menu );
        return;
    }
    wxFileHistory::UseMenu( menu );
}
   
#if wxUSE_CONFIG
void wxPliFileHistory::Load( wxConfigBase& config )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "Load" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "o", &config,
                                           "Wx::ConfigBase");
        return;
    }
    wxFileHistory::Load( config );
}
void wxPliFileHistory::Save( wxConfigBase& config )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "Save" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "o", &config,
                                           "Wx::ConfigBase" );
        return;
    }
    wxFileHistory::Save( config );
}
#endif

void wxPliFileHistory::AddFilesToMenu()
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "AddFilesToMenu" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD|G_NOARGS );
        return;
    }
    wxFileHistory::AddFilesToMenu();
}

void wxPliFileHistory::AddFilesToMenu( wxMenu* menu )
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "AddFilesToMenu" ) )
    {
        wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                           G_SCALAR|G_DISCARD, "O", menu );
        return;
    }
    wxFileHistory::AddFilesToMenu( menu );
}

wxString wxPliFileHistory::GetHistoryFile( int i ) const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback,
                                           "GetHistoryFile" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR, "i", i );
        wxString retval;
        WXSTRING_INPUT( retval, wxString, ret );
        SvREFCNT_dec( ret );
        return retval;
    }
    return wxFileHistory::GetHistoryFile( i );
}

int wxPliFileHistory::GetCount() const
{
    dTHX;
    if( wxPliVirtualCallback_FindCallback( aTHX_ &m_callback, "GetCount" ) )
    {
        SV* ret = wxPliVirtualCallback_CallCallback( aTHX_ &m_callback,
                                                     G_SCALAR|G_NOARGS );
        int retval = (int)SvIV( ret );
        SvREFCNT_dec( ret );
        return retval;
    }
    return wxFileHistory::GetCount();
}


WXPLI_IMPLEMENT_DYNAMIC_CLASS( wxPliFileHistory, wxFileHistory );