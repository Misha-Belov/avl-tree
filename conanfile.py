from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class AvlTreeRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("googletest/[>=1.16.0 <1.17.0]")

    #def build_requirements(self):
        #self.tool_requires("cmake/[>=3.14.0 <3.32.0]")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def layout(self):
        cmake_layout(self)
