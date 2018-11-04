import qbs 1.0

Project {
    CppApplication {
        name: "hexstringconvertbenchmark"
        files: [
            "convert_functions.cpp",
            "random_data_generator.cpp",
            "benchmarks.convert_functions.cpp",
            "main.cpp"
        ]
        cpp.optimization: "ludicrousSpeed"
        cpp.cxxLanguageVersion: "c++17"
        Properties
        {
            condition: qbs.targetOS.contains("windows")
            cpp.includePaths: ["C:/Software/boost_1_68_0/"]
        }
        Properties
        {
            condition: qbs.targetOS.contains("linux")
            cpp.commonCompilerFlags: ["-pthread"]
        }
    }

    CppApplication {
        name: "tests-generator"
        files: [
            "random_data_generator.cpp",
            "tests.random_data_generator.cpp",
            "matcher.hexadecimal_digit.cpp"
        ]
        cpp.optimization: "ludicrousSpeed"
        cpp.cxxLanguageVersion: "c++17"
    }

    CppApplication {
        name: "tests"
        files: [
            "convert_functions.cpp",
            "tests.convert_functions.cpp"
        ]
        cpp.optimization: "ludicrousSpeed"
        cpp.cxxLanguageVersion: "c++17"
    }
}