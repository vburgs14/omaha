// Copyright 2008-2010 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ========================================================================
//
// Contains ProcessLauncher class to launch a process using a COM interface. The
// COM object is typically created by the caller as a medium integrity object
// impersonating the identity of the active user. This is to allow for launching
// a medium-integrity process from a high-integrity process.

#ifndef OMAHA_GOOPDATE_PROCESS_LAUNCHER_H__
#define OMAHA_GOOPDATE_PROCESS_LAUNCHER_H__

#include <windows.h>
#include <atlbase.h>
#include <atlcom.h>
#include <atlstr.h>
#include "omaha/base/atlregmapex.h"
#include "omaha/common/const_cmd_line.h"
#include "omaha/common/const_goopdate.h"
#include "omaha/common/goopdate_utils.h"
#include "omaha/goopdate/com_proxy.h"
#include "omaha/goopdate/non_localized_resource.h"

// Generated by MIDL in the "BUILD_MODE.OBJ_ROOT + SETTINGS.SUBDIR".
#include "goopdate/omaha3_idl.h"

namespace omaha {

const TCHAR* const kTlbVersion    = _T("1.0");
const TCHAR* const kProcessWorkerDescription =
    _T("Google Update Process Launcher Class");

class ATL_NO_VTABLE ProcessLauncher
    : public CComObjectRootEx<CComMultiThreadModel>,
      public CComCoClass<ProcessLauncher, &__uuidof(ProcessLauncherClass)>,
      public IProcessLauncher,
      public StdMarshalInfo {
 public:
  ProcessLauncher();
  virtual ~ProcessLauncher();

  DECLARE_NOT_AGGREGATABLE(ProcessLauncher)
  DECLARE_PROTECT_FINAL_CONSTRUCT()

  DECLARE_REGISTRY_RESOURCEID_EX(IDR_LOCAL_SERVER_RGS)

  #pragma warning(push)
  // C4640: construction of local static object is not thread-safe
  #pragma warning(disable : 4640)
  BEGIN_REGISTRY_MAP()
    REGMAP_ENTRY(_T("HKROOT"),       goopdate_utils::GetHKRoot())
    REGMAP_MODULE2(_T("MODULE"),     kOmahaOnDemandFileName)
    REGMAP_ENTRY(_T("VERSION"),      kTlbVersion)
    REGMAP_ENTRY(_T("PROGID"),       kProgIDProcessLauncher)
    REGMAP_ENTRY(_T("DESCRIPTION"),  kProcessWorkerDescription)
    REGMAP_UUID(_T("CLSID"),         __uuidof(ProcessLauncherClass))
  END_REGISTRY_MAP()
  #pragma warning(pop)

  // C4505: unreferenced IUnknown local functions have been removed
  #pragma warning(disable : 4505)
  BEGIN_COM_MAP(ProcessLauncher)
    COM_INTERFACE_ENTRY(IProcessLauncher)
    COM_INTERFACE_ENTRY(IStdMarshalInfo)
  END_COM_MAP()

  // Launches a command line at medium integrity.
  STDMETHOD(LaunchCmdLine)(const TCHAR* cmd_line);

  // Launches the appropriate browser.
  STDMETHOD(LaunchBrowser)(DWORD type, const TCHAR* url);

  // Launches a command line elevated.
  STDMETHOD(LaunchCmdElevated)(const WCHAR* app_guid,
                               const WCHAR* cmd_id,
                               DWORD caller_proc_id,
                               ULONG_PTR* proc_handle);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(ProcessLauncher);
};

}  // namespace omaha

#endif  // OMAHA_GOOPDATE_PROCESS_LAUNCHER_H__