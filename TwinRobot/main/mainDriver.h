///////////////////////////////////////////////////////////////////////////////
// mainDriver.h

#ifndef __MAINDRIVER_H__
#define __MAINDRIVER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TcBase.h"

#define MAINDRV_NAME        "MAIN"
#define MAINDRV_Major       1
#define MAINDRV_Minor       0

#define DEVICE_CLASS CmainDriver

#include "ObjDriver.h"

class CmainDriver : public CObjDriver
{
public:
	virtual IOSTATUS	OnLoad();
	virtual VOID		OnUnLoad();

	//////////////////////////////////////////////////////
	// VxD-Services exported by this driver
	static unsigned long	_cdecl MAINDRV_GetVersion();
	//////////////////////////////////////////////////////
	
};

Begin_VxD_Service_Table(MAINDRV)
	VxD_Service( MAINDRV_GetVersion )
End_VxD_Service_Table


#endif // ifndef __MAINDRIVER_H__