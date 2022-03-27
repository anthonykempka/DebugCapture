// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

// Define windows version
#define _WIN32_WINNT _WIN32_WINNT_WIN7 

#if !defined(AFX_STDAFX_H__1E845FE6_18A4_4F42_8319_F40FF7F700B2__INCLUDED_)
#define AFX_STDAFX_H__1E845FE6_18A4_4F42_8319_F40FF7F700B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Added includes
#include <psapi.h>
#include <AclAPI.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1E845FE6_18A4_4F42_8319_F40FF7F700B2__INCLUDED_)
