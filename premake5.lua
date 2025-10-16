require("ecc/ecc")

workspace("safer_c")
configurations({ "Debug", "Release" })

project("safer_c")
kind("SharedLib")
language("C")
targetdir("build/%{cfg.buildcfg}")

includedirs("include")

files({
	"src/**.c",
})

filter("configurations:Debug")
defines({ "DEBUG" })
symbols("On")

filter("configurations:Release")
defines({ "NDEBUG" })
optimize("On")
