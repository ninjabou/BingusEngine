add_rules("mode.debug", "mode.release")

add_requires("glfw")
includes("external/xmake_soloud.lua")
add_requires("soloud")
add_requires("sokol")
add_requires("glm")
add_requires("stb")

target("helloworld")
    set_kind("binary")
    set_languages("cxx17")

    add_deps("BingusEngine")

    -- Copy assets
    after_build(function (target)
        cprint("Copying assets")
        os.cp("$(projectdir)/assets", path.directory(target:targetfile()))
    end)
    
    add_files("demo/helloworld.cpp")

target("BingusEngine")
    set_kind("static")
    set_languages("cxx17")

    add_packages("glfw")
    add_packages("sokol")
    add_packages("soloud")
    add_packages("glm", {public = true})
    add_packages("stb")
    
    -- Declare our engine's header path.
    -- This allows targets that depend on the engine to #include them.
    add_includedirs("src", {public = true})
    
    -- Add all .cpp files in the `src` directory.
    add_files("src/*.cpp")