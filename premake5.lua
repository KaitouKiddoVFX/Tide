workspace "TideEnginee"
    architecture "x64"
    startproject "TideSandBox"

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
IncludeDir["Glad"] = "Tide/vendor/Glad/include"
IncludeDir["ImGui"] = "Tide/vendor/imgui"
IncludeDir["glm"] = "Tide/vendor/glm"

include "Tide/vendor/GLFW"
include "Tide/vendor/Glad"
include "Tide/vendor/imgui"

project "Tide"
    location "Tide"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "tdpch.h"
    pchsource "Tide/src/tdpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "TD_PLATFORM_WINDOWS",
            "TD_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/TideSandBox")
        }

    filter "configurations:Debug"
        defines "TD_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "TD_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "TD_DIST"
        runtime "Release"
        optimize "On"

project "TideSandBox"
    location "TideSandBox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "Off"

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
        "Tide/src",
        "Tide/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Tide"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "TD_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "TD_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "TD_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "TD_DIST"
        runtime "Release"        
        optimize "On"
