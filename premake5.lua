target = "%{wks.location}/bin/%{prj.name}/%{cfg.buildcfg}"
obj = "%{wks.location}/bin-int/%{prj.name}/"

local dep = "%{wks.location}/deps/"
includes = {
    glad = dep .. "glad/include",
    glfw = dep .. "glfw/include",
    glm = dep .. "glm"
}

workspace "ping pong"
    configurations { "debug", "release" }
    architecture "x86_64"
    startproject "game"

    include "src"
    include "deps/glad"
    include "deps/glfw"