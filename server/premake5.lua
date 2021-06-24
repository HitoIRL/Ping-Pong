project "server"
    kind "ConsoleApp"

    language "C++"
    cppdialect "C++latest"

    targetdir(target)
    objdir(obj)

    files { "**.cpp", "**.hpp" }
    includedirs { includes["enet"] }
    links { "enet" }

    filter "configurations:debug"
        runtime "Debug"
		symbols "on"

    filter "configurations:release"
        runtime "Release"
		optimize "on"