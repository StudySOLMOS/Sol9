// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define NOMINMAX

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

// TODO: reference additional headers your program requires here
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define TIXML_USE_STL
#include <tinyxml.h>

#if defined _MT
	#if defined _DLL
		#if defined _DEBUG
			#pragma comment(lib, "tinyxmlSTL_MDd")
		#else
			#pragma comment(lib, "tinyxmlSTL_MD")
		#endif
	#else
		#if defined _DEBUG
			#pragma comment(lib, "tinyxmlSTL_MTd")
		#else
			#pragma comment(lib, "tinyxmlSTL_MT")
		#endif
	#endif
#endif

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>


// sol9
#include "types.h"
#include "Entity.h"
#include "Mesh.h"