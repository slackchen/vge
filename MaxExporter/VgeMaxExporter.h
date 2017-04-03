#pragma once

//----------------------------------------------------------------------------
// MaxExporter
//----------------------------------------------------------------------------

class MaxExporter : public SceneExport
{
private:
	static int _stdcall ExporterDialogProc( HWND windowhandle, DWORD msgid, WPARAM wparam, LPARAM lparam );

public:
	virtual int ExtCount( )
	{ return 1; }

	virtual const vchar* Ext( int )
	{ return (const vchar*)_FILE_EXTENTION; }

	virtual const vchar* LongDesc( )
	{ return (const vchar*)_PLUGIN_NAME; }

	virtual const vchar* ShortDesc( )
	{ return (const vchar*)_PLUGIN_NAME; }

	virtual const vchar* AuthorName( )
	{ return (const vchar*)_PLUGIN_AUTHOR; }

	virtual const vchar* CopyrightMessage( )
	{ return (const vchar*)_PLUGIN_COPYRIGHT; }

	virtual const vchar* OtherMessage1( )
	{ return VT(""); }

	virtual const vchar* OtherMessage2( )
	{ return VT(""); }

	virtual unsigned int Version( )
	{ return _FILE_VERSION; }

	virtual void ShowAbout( HWND )
	{ }

	virtual int DoExport( const vchar* filename, ExpInterface* expinterface, Interface* maxinterface, BOOL suppressprompts, DWORD options );
};

//----------------------------------------------------------------------------
// MaxExporterDesc
//----------------------------------------------------------------------------

class MaxExporterDesc : public ClassDesc2
{
public:
	virtual int IsPublic( )
	{ return 1; }

	virtual const vchar* ClassName( )
	{ return (const vchar*)_PLUGIN_NAME; }

	virtual const vchar* InternalName( )
	{ return (const vchar*)_PLUGIN_NAME; }

	virtual SClass_ID SuperClassID( )
	{ return SCENE_EXPORT_CLASS_ID; }

	virtual Class_ID ClassID( )
	{ return Class_ID(0x63625baa, 0x280617cc); }

	virtual const vchar* Category( )
	{ return VT("Game Utilities"); }

	virtual vchar* GetRsrcString( int )
	{ return null; }

	virtual void* Create( BOOL )
	{ return new MaxExporter( ); }
};