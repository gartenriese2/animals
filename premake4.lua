solution "PM"
    configurations {"Debug", "Release"}
    platforms {"Native"}

project "main"
    configurations {"Debug", "Release"}
    platforms {"Native"}
    kind "ConsoleApp"
    language "C++"

    location "./build"
    targetdir "./bin"
    targetname "pm"

    files {"src/**.h", "src/**.hpp", "src/**.cpp"}

    -- scan args
    local use_clang = false
    local argc = 1
    while(_ARGS[argc] ~= nil) do
        if (_ARGS[argc] == "--clang") then
            use_clang = true
        end
        argc = argc + 1
    end

    flags {"Symbols"}
    buildoptions {"-std=c++11", "-Wall", "-pedantic"}
    links {"ncurses"}

    if (use_clang) then
        buildoptions {"-stdlib=libc++"}
        linkoptions {"-stdlib=libc++"}
        links {"c++abi"}
        premake.gcc.cc = "clang"
        premake.gcc.cxx = "clang++"
        print("\n" ..
              "====================================\n" ..
              "|                                  |\n" ..
              "| Don't forget to run clangfix.sh! |\n" ..
              "|                                  |\n" ..
              "====================================\n")
    end

    configuration "Debug"
        defines {"DEBUG"}

    configuration "Release"
        defines {"NDEBUG"}
        flags {"EnableSSE2", "OptimizeSpeed"}

