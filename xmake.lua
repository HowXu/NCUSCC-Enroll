add_rules("mode.debug", "mode.release")
-- OS相关
if is_os("windows") then
    set_toolchains("mingw")
end

-- DEBUG相关
if is_mode("debug") then 
    add_cflags("-g","-pg","-O0")  -- 添加编译选项，生成性能分析信息
    add_ldflags("-pg")  -- 添加链接选项，生成性能分析信息
end

-- 关闭优化
set_optimize("none")

target("NCUSCC-Enroll")
    set_kind("static")
    add_files("src/**.c")
    set_targetdir("./build/lib")

target("test_runnable")
    set_kind("binary")
    set_targetdir("./build/test")
    add_files("test/test_unit_and_sort.c","./Unity/src/*.c")
--  add_linkdirs("./build/lib")
    add_links("NCUSCC-Enroll")
    add_deps("NCUSCC-Enroll")

-- 多层优化等级编译
target("test_optimization_o0")
    set_kind("binary")
    set_targetdir("./build/test/optimization")
    add_files("test/test_optimization.c")
--  add_linkdirs("./build/lib")
    add_links("NCUSCC-Enroll")
    add_deps("NCUSCC-Enroll")
    add_cflags("-O0")

target("test_optimization_o1")
    set_kind("binary")
    set_targetdir("./build/test/optimization")
    add_files("test/test_optimization.c")
--  add_linkdirs("./build/lib")
    add_links("NCUSCC-Enroll")
    add_deps("NCUSCC-Enroll")
    add_cflags("-O1")

target("test_optimization_o2")
    set_kind("binary")
    set_targetdir("./build/test/optimization")
    add_files("test/test_optimization.c")
--  add_linkdirs("./build/lib")
    add_links("NCUSCC-Enroll")
    add_deps("NCUSCC-Enroll")
    add_cflags("-O2")

target("test_optimization_o3")
    set_kind("binary")
    set_targetdir("./build/test/optimization")
    add_files("test/test_optimization.c")
--  add_linkdirs("./build/lib")
    add_links("NCUSCC-Enroll")
    add_deps("NCUSCC-Enroll")
    add_cflags("-O3")

target("test_optimization_ofast")
    set_kind("binary")
    set_targetdir("./build/test/optimization")
    add_files("test/test_optimization.c")
--  add_linkdirs("./build/lib")
    add_links("NCUSCC-Enroll")
    add_deps("NCUSCC-Enroll")
    add_cflags("-Ofast")

-- TODO:分析性能的脚本

--    add_links("unity")
--    add_linkdirs("./Unity/")
--    add_includedirs("./Unity/src/")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

