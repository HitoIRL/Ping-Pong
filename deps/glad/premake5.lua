project "glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir(target)
    objdir(obj)

    files { "**.c", "**.h" }
    includedirs { "include" }

    filter "configurations:debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:release"
        runtime "Release"
        optimize "on"