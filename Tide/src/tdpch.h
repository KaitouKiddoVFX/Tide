#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Tide/Core/Log.h"
#include "Tide/Debug/Instrumentor.h"

#ifdef TD_PLATFORM_WINDOWS
	#include <Windows.h>
#endif