#include "VgeMaxPlugin.h"
#include "VgeMaxInterface.h"


MaxInterface::MaxInterface( ExpInterface* expinterface, Interface* maxinterface )
	: mExpInterface( expinterface )
	, mMaxInterface( maxinterface )
{

}

void MaxInterface::EnumScene()
{
	mExpInterface->theScene->EnumTree( this );
}

int MaxInterface::callback( INode *node )
{
	if ( !node->IsNodeHidden() )
	{
		::Object* obj = node->EvalWorldState(0).obj;
		if ( obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)) )
		{
			::Mesh& maxmesh = ((::TriObject*)obj->ConvertToType(0, triObjectClassID))->mesh;
		}
	}

	return TREE_CONTINUE;
}