add_rules("mode.debug", "mode.release")

includes("xf_utils/xmake.lua")

target("xf_init")
    set_kind("binary")
    add_includedirs("src")
    add_ldflags("-Wl,-Map=build/linux.map")
    add_ldflags("-Tlinker/gcc_x86_64.xf_init.ld")
    add_files("src/**.c")
    add_files("example/*.c")
    add_includedirs("example")
    add_includedirs("src")
    add_xf_utils("xf_utils")
