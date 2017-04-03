#pragma once

class MaxInterface : public ITreeEnumProc
{
public:
	MaxInterface( ExpInterface* expinterface, Interface* maxinterface );

	void EnumScene();

	virtual int callback( INode *node );

private:
	ExpInterface* mExpInterface;
	Interface* mMaxInterface;
};