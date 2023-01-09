// pch.hpp : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxdlgs.h>
#include <atlimage.h>

#if PCH_SUPPORT
#include "cstdmf/cstdmf_lib.hpp"
#include "appmgr/appmgr_lib.hpp"
#include "controls/auto_tooltip.hpp"
#include "chunk/chunk_lib.hpp"
#include "duplo/action_queue.hpp"
#include "duplo/py_attachment.hpp"
#include "editor_shared/app/i_editor_app.hpp"
#include "editor_shared/gui/i_main_frame.hpp"
#include "editor_shared/pages/gui_tab_content.hpp"
#include "gizmo/gizmo_lib.hpp"
#include "input/input_lib.hpp"
#include "guimanager/guimanager_lib.hpp"
#include "guitabs/guitabs_content.hpp"
#include "guitabs/manager.hpp"
#include "math/math_lib.hpp"
#include "model/model_lib.hpp"
#include "moo/moo_lib.hpp"
#include "physics2/material_kinds.hpp"
#include "pyscript/pyscript_lib.hpp"
#include "resmgr/resmgr_lib.hpp"
#include "romp/romp_lib.hpp"

#include "tools/common/delay_redraw.hpp"
#include "tools/common/python_adapter.hpp"
#include "tools/common/resource_loader.hpp"
#include "tools/common/romp_harness.hpp"
#include "tools/common/tools_camera.hpp"
#include "tools/common/utilities.hpp"

#include "ual/ual_lib.hpp"

#include <Python.h>
#endif // PCH_SUPPORT
