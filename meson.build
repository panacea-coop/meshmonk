project('meshmonk', 'cpp',
  version : '0.0.7',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

cc = meson.get_compiler('cpp')

c_dep = dependency('openmeshcore',required:true)
t_dep = dependency('openmeshtools',required:true)
eigen_dep = dependency('eigen3',required:true)

vendor = include_directories('vendor')

sources = ['meshmonk.cpp',
    'src/BaseCorrespondenceFilter.cpp',
    'src/CorrespondenceFilter.cpp',
    'src/Downsampler.cpp',
    'src/helper_functions.cpp',
    'src/InlierDetector.cpp',
    'src/NeighbourFinder.cpp',
    'src/NonrigidRegistration.cpp',
    'src/PyramidNonrigidRegistration.cpp',
    'src/RigidRegistration.cpp',
    'src/RigidTransformer.cpp',
    'src/ScaleShifter.cpp',
    'src/SymmetricCorrespondenceFilter.cpp',
    'src/ViscoElasticTransformer.cpp']

if get_option('shared')
    libblacksmith_shared = shared_library('meshmonk',
        sources,
        dependencies: [c_dep, t_dep, eigen_dep],
        include_directories: vendor,
        install: true, version: '0.0.7')
else
    libblacksmith_static = static_library('meshmonk',
        sources,
        dependencies: [c_dep, t_dep, eigen_dep], 
        include_directories: vendor,
        install: true)
endif