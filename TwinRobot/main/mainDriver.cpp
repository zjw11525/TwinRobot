///////////////////////////////////////////////////////////////////////////////
// mainDriver.cpp
#include "TcPch.h"
#pragma hdrstop

#include "mainDriver.h"
#include "mainClassFactory.h"

DECLARE_GENERIC_DEVICE(MAINDRV)

IOSTATUS CmainDriver::OnLoad( )
{
	TRACE(_T("CObjClassFactory::OnLoad()\n") );
	m_pObjClassFactory = new CmainClassFactory();

	return IOSTATUS_SUCCESS;
}

VOID CmainDriver::OnUnLoad( )
{
	delete m_pObjClassFactory;
}

unsigned long _cdecl CmainDriver::MAINDRV_GetVersion( )
{
	return( (MAINDRV_Major << 8) | MAINDRV_Minor );
}

