#pragma once

#pragma warning( disable : 4819 )
#pragma warning( disable : 4996 )

#include <windows.h>
#include <commctrl.h>
#include <max.h>
#include <cs/bipexp.h>
#include <cs/phyexp.h>
#include <iparamb2.h>
#include <maxscrpt/maxscrpt.h>
#include <iskin.h>
#include <decomp.h>

#include <Vge.h>
using namespace Vge;

#pragma comment( lib, "comctl32" )
#pragma comment( lib, "core" )
#pragma comment( lib, "geom" )
#pragma comment( lib, "mesh" )
#pragma comment( lib, "maxutil" )
#pragma comment( lib, "maxscrpt" )
#pragma comment( lib, "paramblk2" )


#define _PLUGIN_NAME				VT("Vge Max Exporter 0.1")
#define _PLUGIN_AUTHOR				VT("Adrian Chen")
#define _PLUGIN_COPYRIGHT			VT("Copyright (C) 2010 N.G. Inc.")

#define _FILE_ID					0x00524056		// "VGR"
#define _FILE_VERSION				0x00000300		// 0.30
#define _FILE_EXTENTION				VT("VGR")

//#include "MaxNode.h"
//#include "MaxInterface.h"
//#include "MaxExporter.h"