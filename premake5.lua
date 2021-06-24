target = "%{wks.location}/bin/%{prj.name}/%{cfg.buildcfg}"
obj = "%{wks.location}/bin-int/%{prj.name}/"

local dep = "%{wks.location}/deps/"
includes = {
    glad = dep .. "glad/include",
    glfw = dep .. "glfw/include",
    glm = dep .. "glm",
    enet = dep .. "enet/include"
}

workspace "ping pong"
    configurations { "debug", "release" }
    architecture "x86_64"
    startproject "game"

    include "client"
    include "server"
    include "deps/glad"
    include "deps/glfw"
    include "deps/enet"