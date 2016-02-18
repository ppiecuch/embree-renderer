// ======================================================================== //
// Copyright 2009-2013 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include "library2.h"
#include "sys/sysinfo.h"
#include "sys/filename.h"

////////////////////////////////////////////////////////////////////////////////
/// Windows Platform
////////////////////////////////////////////////////////////////////////////////

#if defined(__WIN32__)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace embree
{
  /* opens a shared library */
  lib_t openLibrary(const std::string& file, bool silent)
  {
    std::string fullName = file+".dll";
    FileName executable = getExecutableFileName();
    HANDLE handle = LoadLibrary((executable.path() + fullName).c_str());
    return lib_t(handle);
  }
}
#endif

////////////////////////////////////////////////////////////////////////////////
/// Unix Platform
////////////////////////////////////////////////////////////////////////////////

#if defined(__UNIX__)

#include <dlfcn.h>

namespace embree
{
  /* opens a shared library */
  lib_t openLibrary(const std::string& file, bool silent)
  {
#if defined(__MACOSX__)
    std::string fullName = "lib"+file+".dylib";
#else
    std::string fullName = "lib"+file+".so";
#endif
    FileName executable = getExecutableFileName();
    void* lib = dlopen((executable.path() + fullName).c_str(),RTLD_NOW);
    if (!silent)
    	if (lib == NULL) throw std::runtime_error(dlerror());
    return lib_t(lib);
  }
}
#endif
