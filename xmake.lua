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

--变量
local OPM = "test/test_optimization.c"
local OPM_TGT = "./build/test/optimization"
local RM_ANA = "find ./analysis -type f -exec rm -f {} +"

local TIMES = 10 -- 10次测试取平均值

function get_dir(targetname)
    return string.format("%s/%s",OPM_TGT,targetname)
end

target("NCUSCC-Enroll")
    set_kind("static")
    add_files("src/**.c")
    set_targetdir("./build/lib")
    -- 分析报告导出准备
    after_build(function (t) 
        os.mkdir("./analysis")
    end)

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
    set_targetdir(get_dir("test_optimization_o0"))
    add_files(OPM)
    add_deps("NCUSCC-Enroll")
    add_cflags("-O0")
    after_run(function (target)
        local output = os.iorun(string.format("gprof %s/%s/%s %s/%s/gmon.out",OPM_TGT,target:name(),target:name(),OPM_TGT,target:name()))
        io.writefile(string.format("./analysis/%s.txt",target:name()),output)
        os.run(string.format("rm %s/%s/gmon.out",OPM_TGT,target:name()))
    end)

target("test_optimization_o1")
    set_kind("binary")
    set_targetdir(get_dir("test_optimization_o1"))
    add_files(OPM)
    add_deps("NCUSCC-Enroll")
    add_cflags("-O1")
    after_run(function (target)
        local output = os.iorun(string.format("gprof %s/%s/%s %s/%s/gmon.out",OPM_TGT,target:name(),target:name(),OPM_TGT,target:name()))
        io.writefile(string.format("./analysis/%s.txt",target:name()),output)
        os.run(string.format("rm %s/%s/gmon.out",OPM_TGT,target:name()))
    end)

target("test_optimization_o2")
    set_kind("binary")
    set_targetdir(get_dir("test_optimization_o2"))
    add_files(OPM)
    add_deps("NCUSCC-Enroll")
    add_cflags("-O2")
    after_run(function (target)
        local output = os.iorun(string.format("gprof %s/%s/%s %s/%s/gmon.out",OPM_TGT,target:name(),target:name(),OPM_TGT,target:name()))
        io.writefile(string.format("./analysis/%s.txt",target:name()),output)
        os.run(string.format("rm %s/%s/gmon.out",OPM_TGT,target:name()))
    end)

target("test_optimization_o3")
    set_kind("binary")
    set_targetdir(get_dir("test_optimization_o3"))
    add_files(OPM)
    add_deps("NCUSCC-Enroll")
    add_cflags("-O3")
    after_run(function (target)
        local output = os.iorun(string.format("gprof %s/%s/%s %s/%s/gmon.out",OPM_TGT,target:name(),target:name(),OPM_TGT,target:name()))
        io.writefile(string.format("./analysis/%s.txt",target:name()),output)
        os.run(string.format("rm %s/%s/gmon.out",OPM_TGT,target:name()))
    end)

target("test_optimization_ofast")
    set_kind("binary")
    set_targetdir(get_dir("test_optimization_ofast"))
    add_files(OPM)
    add_deps("NCUSCC-Enroll")
    add_cflags("-Ofast")
    after_run(function (target)
        local output = os.iorun(string.format("gprof %s/%s/%s %s/%s/gmon.out",OPM_TGT,target:name(),target:name(),OPM_TGT,target:name()))
        io.writefile(string.format("./analysis/%s.txt",target:name()),output)
        os.run(string.format("rm %s/%s/gmon.out",OPM_TGT,target:name()))
    end)

-- TODO:分析性能的脚本
-- TODO:添加处理逻辑自动进行10次性能测试然后生成svg图像
target("test_analysis")
    set_kind("phony")
    add_deps("test_optimization_o0","test_optimization_o1","test_optimization_o2","test_optimization_o3","test_optimization_ofast")
    before_run(function (target) 
        -- clean
        os.run(RM_ANA)
        print("[INFO] Clean analysis files")
    end)
    on_run(function (target)  
        -- 循环获得10次数据
        for i = 1, TIMES do
        --生成一次运行记录
        os.run("xmake run test_optimization_o0")
        os.run("xmake run test_optimization_o1")
        os.run("xmake run test_optimization_o2")
        os.run("xmake run test_optimization_o3")
        os.run("xmake run test_optimization_ofast")
        --生成report
        os.run("python3 ./script/formate.py")
        -- clean
        os.run(RM_ANA)
        print(string.format("[INFO] Finish %d optimization test",i))
        end
        print(string.format("[INFO] %d test finish",TIMES))
        -- 合并
        os.run("python3 ./script/merge.py")
        print("[INFO] Finish merge data")
        -- 求平均值
        os.run("python3 ./script/average.py")
        print("[INFO] Finish average data")
        -- 生成全比较图
        os.run("python3 ./script/gen_all_svg.py")
        print("[INFO] Finish generate all svgs")
        -- 生成单个比较图
        os.run("python3 ./script/gen_sin_svg.py")
        print("[INFO] Finish generate single svgs")
    end)
    after_run(function (target) 
        -- clean
        os.run(RM_ANA)
        print("[INFO] All done")
    end)

-- 清除测试数据
target("test_clean")
    set_kind("phony")
    on_run(function (target) 
        -- clean analysis文件
        os.run(RM_ANA)
        -- clean report
        os.run("rm -rf ./report")
    end)


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

