project "game"
    kind "ConsoleApp"

    language "C++"
    cppdialect "C++latest"

    targetdir(target)
    objdir(obj)

    defines { "GLFW_INCLUDE_NONE" }

    files { "**.cpp", "**.hpp" }
    includedirs { includes["glad"], includes["glfw"], includes["glm"] }
    links { "glad", "glfw" }

    filter "configurations:debug"
        runtime "Debug"
		symbols "On"
    filter "configurations:release"
        runtime "Release"
		optimize "On"