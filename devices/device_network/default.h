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

#ifndef __EMBREE_DEFAULT_H__
#define __EMBREE_DEFAULT_H__

#include "sys/platform.h"
#include "sys/ref.h"
#include "sys/intrinsics.h"
#include "sys/vector.h"
#include "sys/string.h"

#include <sstream>

namespace embree
{
  template<typename T> __forceinline std::string stringOf( T const& v) {
    std::stringstream s; s << v; return s.str();
  }
}

#include "math/math.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/col3.h"
#include "math/affinespace.h"

namespace embree
{
  struct Array12f {
    float values[12];
    operator float*() { return(values); }
  };
  
  __forceinline AffineSpace3f copyFromArray(const float* v) 
  {
    return AffineSpace3f(LinearSpace3f(Vec3f(v[0],v[1],v[2]),
                                       Vec3f(v[3],v[4],v[5]),
                                       Vec3f(v[6],v[7],v[8])),
                                       Vec3f(v[9],v[10],v[11]));
  }
}

#include "simd/simd.h"

#include "sys/thread.h"
#include "sys/atomic.h"
#include "sys/barrier.h"

#endif
