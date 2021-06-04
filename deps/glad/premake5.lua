project "glad"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    targetdir(target)
    objdir(obj)

    files { "**.c", "**.h" }
    includedirs { "include" }

    filter "configurations:debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:release"
        runtime "Release"
        optimize "On"