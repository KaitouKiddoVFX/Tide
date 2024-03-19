workspace "TideEnginee"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Tide/vendor/GLFW/include"
--IncludeDir["GLFW_SRC"] = "Tide/vendor/GLFW/src"

include "Tide/vendor/GLFW"

project "Tide"
    location "Tide"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "tdpch.h"
    pchsource "Tide/src/tdpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        --"%{IncludeDir.GLFW_SRC}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "TD_PLATFORM_WINDOWS",
            "TD_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/TideSandBox")
        }

    filter "configurations:Debug"
        defines "TD_DEBUG"
        symbols "On"
        buildoptions "/MDd"

    filter "configurations:Release"
        defines "TD_RELEASE"
        symbols "On"
        buildoptions "/MD"

    filter "configurations:Dist"
        defines "TD_DIST"
        symbols "On"
        buildoptions "/MD"

project "TideSandBox"
    location "TideSandBox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Tide/vendor/spdlog/include",
        "Tide/src"
    }

    links
    {
        "Tide"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "TD_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "TD_DEBUG"
        symbols "On"
        buildoptions "/MDd"

    filter "configurations:Release"
        defines "TD_RELEASE"
        symbols "On"
        buildoptions "/MD"

    filter "configurations:Dist"
        defines "TD_DIST"
        symbols "On"
        buildoptions "/MD"        