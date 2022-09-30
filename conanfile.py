from conans import ConanFile, Meson, tools
from conan.tools.files import get
from conan.tools.layout import basic_layout
import os


class MeshmonkConan(ConanFile):
    name = "meshmonk"
    version = "0.0.7"
    license = "Apache-2.0"
    url = "https://gitlab.kuleuven.be/mirc/meshmonk"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=True"
    generators = "pkg_config"
    requires = ["openmesh/9.0", "eigen/3.3.7"]
    exports_sources = "src*", "vendor*", "meshmonk.hpp", "meshmonk.cpp", "global.hpp", "meson*"
    
    def package_id(self):
        self.info.clear()

    def layout(self):
        basic_layout(self, src_folder="src")

    def build(self):
        meson = Meson(self)
        meson.configure(args=['-Dshared=' + str(self.options.shared)],
                        source_folder=os.path.join(self.source_folder, ".."),
                        build_folder=os.path.join(self.build_folder, "build"),
                        pkg_config_paths=[self.build_folder])
        meson.build()

    def package(self):
        self.copy("LICENSE", src=os.path.join(self.source_folder, ".."), dst="licenses")
        self.copy("*.h", src=os.path.join(self.source_folder, ".."), dst="include", keep_path=True)
        self.copy("*.hpp", src=os.path.join(self.source_folder, ".."), dst="include", keep_path=True)
        self.copy("*.lib", src=os.path.join(self.build_folder, "build"), dst="lib", keep_path=False)
        self.copy("*.dll", src=os.path.join(self.build_folder, "build"), dst="bin", keep_path=False)
        self.copy("*.dylib*", src=os.path.join(self.build_folder, "build"), dst="lib", keep_path=False)
        self.copy("*.so", src=os.path.join(self.build_folder, "build"), dst="lib", keep_path=False)
        self.copy("*.a", src=os.path.join(self.build_folder, "build"), dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["meshmonk"]
        self.cpp_info.includedirs = ["include"]

