#include "VgeMaxPlugin.h"
#include "VgeMaxExporter.h"
#include "VgeMaxInterface.h"

HINSTANCE		gInstance	= null;

//----------------------------------------------------------------------------
// MaxExporter Implementation
//----------------------------------------------------------------------------

int MaxExporter::DoExport( const vchar* filename, ExpInterface* expinterface, Interface* maxinterface, BOOL suppressprompts, DWORD options )
{
	//::InitCommonControls( );

	MaxInterface* gInterface = new MaxInterface( expinterface, maxinterface );
	gInterface->EnumScene( );

	//gFileName = StringFormatter::AnsiToUnicode( null, 0, filename );
	//gFileName = StringFormatter::RemoveExtention( gFileName );

	//::DialogBox( gInstance, MAKEINTRESOURCE( IDD_DIALOG_EXPORTER ), maxinterface->GetMAXHWnd( ), (DLGPROC) ExporterDialogProc );

	delete gInterface;

	return 1;
}

//----------------------------------------------------------------------------
// MaxExporterDesc Implementation
//----------------------------------------------------------------------------

MaxExporterDesc gExporter;

//----------------------------------------------------------------------------
// LibDescription Implementation
//----------------------------------------------------------------------------

extern "C" __declspec( dllexport ) const vchar* LibDescription( )
{
	return _PLUGIN_NAME;
}

//----------------------------------------------------------------------------
// LibNumberClasses Implementation
//----------------------------------------------------------------------------

extern "C" __declspec( dllexport ) long LibNumberClasses( )
{
	return 1;
}

//----------------------------------------------------------------------------
// LibClassDesc Implementation
//----------------------------------------------------------------------------

extern "C" __declspec( dllexport ) ClassDesc* LibClassDesc( int )
{
	return &gExporter;
}

//----------------------------------------------------------------------------
// LibVersion Implementation
//----------------------------------------------------------------------------

extern "C" __declspec( dllexport ) dword LibVersion( )
{
	return VERSION_3DSMAX;
}

//----------------------------------------------------------------------------
// DllMain Implementation
//----------------------------------------------------------------------------

int __stdcall DllMain( HINSTANCE instance, DWORD, void* )
{
	gInstance = instance;

	return 1;
}