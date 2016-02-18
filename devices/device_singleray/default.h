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

#include "math/math.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec3fa.h"
#include "math/vec4.h"
#include "math/color.h"
#include "math/random.h"
#include "math/affinespace.h"

#include "sys/platform.h"
#include "sys/ref.h"
#include "sys/intrinsics.h"

#include "sys/string.h"
#include <sstream>

namespace embree
{
  template<typename T> __forceinline std::string stringOf( T const& v) {
    std::stringstream s; s << v; return s.str();
  }
}

#include "sys/vector.h"

#define vector_t avector // selec default vector_t type
namespace embree
{
	template<class T> void shuffle(vector_t<T> &t, Random& rng)
	{
		const size_t sz = t.size();
	  	for (size_t i = 0; i < sz; i++)
	    	std::swap(t[i], t[rng.getInt((int)sz)]);
	}
}

#include "sys/string.h"

namespace embree
{
  ////////////////////////////////////////////////////////////////////////////////
  // Data conversions for AffineSpace3f
  ////////////////////////////////////////////////////////////////////////////////

  struct Array12f {
    float values[12];
    operator float*() { return(values); }
  };
  
  __forceinline Array12f copyToArray(const AffineSpace3f& xfm)  
  {
    Array12f values;
    values[ 0] = xfm.l.vx.x;  values[ 1] = xfm.l.vx.y;  values[ 2] = xfm.l.vx.z;       
    values[ 3] = xfm.l.vy.x;  values[ 4] = xfm.l.vy.y;  values[ 5] = xfm.l.vy.z;       
    values[ 6] = xfm.l.vz.x;  values[ 7] = xfm.l.vz.y;  values[ 8] = xfm.l.vz.z;       
    values[ 9] = xfm.p.x;     values[10] = xfm.p.y;     values[11] = xfm.p.z;       
    return values;
  }
  
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
#include "sys/condition.h"
#include "sys/barrier.h"

namespace embree
{
  /* default barrier type */
  class Barrier : public BarrierSys {};
}

#include "samplers/sample.h"
#include "samplers/shapesampler.h"

////////////////////////////////////////////////////////////////////////////////
/// Basic Types
////////////////////////////////////////////////////////////////////////////////

typedef          long long  int64;
typedef unsigned long long uint64;
typedef                int  int32;
typedef unsigned       int uint32;
typedef              short  int16;
typedef unsigned     short uint16;
typedef               char   int8;
typedef unsigned      char  uint8;

#ifdef __WIN32__
#if defined(__X86_64__)
typedef int64 ssize_t;
#else
typedef int32 ssize_t;
#endif
#endif


namespace embree
{
  /* vertex and triangle layout */
  struct RTCVertex   { float x,y,z,a; };
  struct RTCTriangle { int v0, v1, v2; };
};

#endif
