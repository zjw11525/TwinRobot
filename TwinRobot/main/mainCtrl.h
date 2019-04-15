///////////////////////////////////////////////////////////////////////////////
// mainCtrl.h

#ifndef __MAINCTRL_H__
#define __MAINCTRL_H__

#include <atlbase.h>
#include <atlcom.h>

#define MAINDRV_NAME "MAIN"

#include "resource.h"       // main symbols
#include "mainW32.h"
#include "TcBase.h"
#include "mainClassFactory.h"
#include "TcOCFCtrlImpl.h"

class CmainCtrl 
	: public CComObjectRootEx<CComMultiThreadModel>
	, public CComCoClass<CmainCtrl, &CLSID_mainCtrl>
	, public ImainCtrl
	, public ITcOCFCtrlImpl<CmainCtrl, CmainClassFactory>
{
public:
	CmainCtrl();
	virtual ~CmainCtrl();

DECLARE_REGISTRY_RESOURCEID(IDR_MAINCTRL)
DECLARE_NOT_AGGREGATABLE(CmainCtrl)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CmainCtrl)
	COM_INTERFACE_ENTRY(ImainCtrl)
	COM_INTERFACE_ENTRY(ITcCtrl)
	COM_INTERFACE_ENTRY(ITcCtrl2)
END_COM_MAP()

};

#endif // #ifndef __MAINCTRL_H__
