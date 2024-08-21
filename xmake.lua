add_rules("mode.debug")

includes("xf_utils/xmake.lua")

function add_xf_init() 
    add_includedirs("src")
    add_files("src/*.c")
end

target("xf_init")
    set_kind("binary")
    add_cflags("-Wall")
    add_cflags("-std=gnu99 -O0")
    add_ldflags("-Wl,-Map=build/linux.map")
    add_ldflags("-Tlinker/gcc_x86_64.xf_init.ld")
    add_files("examples/*.c")
    add_includedirs("examples")
    add_files("examples/other_component/*.c")
    add_includedirs("examples/other_component")
    add_xf_init()
    add_xf_utils("xf_utils")
    add_links("pthread", "m", "c")

