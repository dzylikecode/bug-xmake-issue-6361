add_rules("mode.debug", "mode.release")

add_requires("serial") -- GitHub: wjwwood/serial
add_requires("fmt") -- GitHub: fmtlib/fmt

target("serial_port")
    set_kind("shared")
    set_languages("c++17")
    add_includedirs("include", {public = true})
    add_files("src/*.cpp")
    add_packages("serial")
    add_defines("BUILDING_DLL")

    after_build(function (target)
        -- os.rm("$(builddir)/output")
        -- os.mkdir("$(builddir)/output/include")
        -- os.mkdir("$(builddir)/output/lib/$(plat)/$(arch)")
        -- os.cp("include/*", "$(builddir)/output/include")
        -- os.cp(target:targetfile(), "$(builddir)/output/lib/$(plat)/$(arch)")
        os.rm("$(builddir)/native")
        os.mkdir("$(builddir)/native")
        os.cp("include/*", "$(builddir)/native")
        os.cp(target:targetfile(), "$(builddir)/native")
    end)

function add_example(name)
    target(name)
        set_kind("binary")
        set_languages("c++17")
        add_includedirs("include", {public = true})
        add_files("examples/" .. name .. ".cpp")
        add_deps("serial_port")
        add_packages("fmt")
end

add_example("list_ports")