include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../../include ../../layers ../../include/helpers ../../include/memory ../../include/loops ../../include/graph ../../include/ops ../../include/types ../../include/cnpy ../../blas)
if(LINUX)
    link_directories(/usr/local/lib)
    link_directories(/usr/lib)
    link_directories(/lib)
endif()

if(APPLE)
    message("Using apple")
    link_directories(/usr/local/lib)
    link_directories(/usr/lib)
    link_directories(/lib)
endif()
if(WIN32)
    get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    foreach(dir ${dirs})
        message(STATUS "dir='${dir}'")
    endforeach()
endif()

# -fsanitize=address
#  -fsanitize=leak
set(CMAKE_CXX_FLAGS  " -fPIC -std=c++11 -fassociative-math -funsafe-math-optimizations -fmax-errors=2")


if (APPLE)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        if ("${CMAKE_C_COMPILER_VERSION}" VERSION_GREATER 6.0 OR "${CMAKE_C_COMPILER_VERSION}" VERSION_EQUAL 6.0)
            SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wa,-mavx512f -fmax-errors=1")
        endif()
    endif()
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
    SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ARCH_TUNE}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
    SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ARCH_TUNE} -O3 -fp-model fast")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ARCH_TUNE}")
endif()


IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    include_directories("/usr/include")
    include_directories("/usr/local/include")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


message("CPU BLAS")
add_definitions(-D__CPUBLAS__=true)
add_library(nd4jcpu STATIC ../../blas/cpu/NativeOps.cpp ../../blas/cpu/GraphExecutioner.cpp
        ../../blas/cpu/NativeOpExcutioner.cpp ../../blas/cpu/NDArray.cpp ../../blas/cpu/NDArrayFactory.cpp  ../../include/memory/cpu/Workspace.cpp
        ../../include/cnpy/cnpy.cpp  ../../include/nd4jmemset.h ../../include/nd4jmalloc.h ../../include/ops/declarable/generic/parity_ops.cpp
        ../../include/ops/declarable/generic/third_party.cpp ../../include/memory/cpu/Workspace.cpp ../../include/ops/declarable/generic/helpers/impl/convolutions.cpp
        ../../include/ops/declarable/generic/convo/conv2d_ops.cpp ../../blas/Environment.cpp ../../include/graph/impl/Stash.cpp ../../include/indexing/impl/NDIndex.cpp
        ../../include/indexing/impl/IndicesList.cpp ../../include/graph/impl/Variable.cpp ../../include/graph/impl/VariableSpace.cpp
        ../../include/graph/impl/ShapeList.cpp ../../include/graph/impl/SessionLocalStorage.cpp ../../include/graph/impl/Node.cpp ../../include/graph/impl/Graph.cpp
        ../../include/graph/Block.h ../../include/graph/impl/Block.cpp ../../include/graph/impl/ArrayList.cpp ../../include/helpers/impl/ArrayUtils.cpp ../../include/helpers/impl/helper_hash.cpp
        ../../include/helpers/impl/TAD.cpp ../../include/ops/impl/specials_sparse.cpp ../../include/helpers/impl/shape.cpp ../../include/ops/declarable/impl/DeclarableOp.cpp ../../include/ops/declarable/DeclarableOp.h
        ../../include/ops/declarable/impl/OpRegistrator.cpp ../../include/ops/declarable/impl/DeclarableReductionOp.cpp ../../include/ops/declarable/impl/DeclarableCustomOp.cpp
        ../../include/ops/impl/specials.cpp ../../include/memory/cpu/MemoryRegistrator.cpp ../../include/ops/impl/gemm.cpp ../../include/ops/declarable/generic/convo/conv3d_ops.cpp
        ../../include/ops/declarable/generic/convo/fullconv3d.cpp ../../include/ops/declarable/generic/convo/pooling2d_ops.cpp ../../include/ops/declarable/generic/convo/pooling3d_ops.cpp
        ../../include/loops/cpu/scalar.cpp ../../include/memory/cpu/MemoryReport.cpp ../../include/memory/MemoryReport.h ../../include/memory/cpu/MemoryUtils.cpp ../../include/memory/MemoryUtils.h
        ../../include/ops/declarable/impl/OpTuple.cpp ../../include/ops/declarable/OpTuple.h ../../include/ops/declarable/generic/parity_ops/strided_slice.cpp ../../include/ops/declarable/generic/parity_ops/zeros_as.cpp
        ../../include/ops/declarable/generic/parity_ops/maximum.cpp ../../include/ops/declarable/generic/parity_ops/minimum.cpp ../../include/ops/declarable/generic/parity_ops/tear.cpp ../../include/ops/declarable/impl/BooleanOp.cpp
        ../../include/ops/declarable/BooleanOp.h ../../include/ops/declarable/generic/boolean/lt_scalar.cpp ../../include/ops/declarable/generic/boolean/gt_scalar.cpp
        ../../include/ops/declarable/impl/OpDescriptor.cpp ../../include/ops/declarable/generic/boolean/eq_scalar.cpp ../../include/ops/declarable/generic/boolean/neq_scalar.cpp
        ../../include/ops/declarable/generic/boolean/gte_scalar.cpp ../../include/ops/declarable/generic/boolean/lte_scalar.cpp
        ../../include/ops/declarable/generic/flow/flow_control_ops.cpp ../../include/graph/impl/Scope.cpp ../../include/graph/Scope.h
        ../../include/graph/Node.h ../../include/graph/Graph.h ../../include/ops/declarable/impl/LogicOp.cpp ../../include/ops/declarable/LogicOp.h
        ../../include/ops/declarable/impl/LegacyOp.cpp ../../include/ops/declarable/LegacyOp.h ../../include/ops/declarable/impl/LegacyTransformOp.cpp
        ../../include/ops/declarable/LegacyTransformOp.h ../../include/ops/declarable/impl/LegacyPairwiseTransformOp.cpp ../../include/ops/declarable/LegacyPairwiseTransformOp.h
        ../../include/ops/declarable/impl/LegacyScalarOp.cpp ../../include/ops/declarable/LegacyScalarOp.h ../../include/ops/declarable/impl/LegacyReduceOp.cpp
        ../../include/ops/declarable/LegacyReduceOp.h ../../include/ops/declarable/impl/LegacyIndexReduceOp.cpp ../../include/ops/declarable/LegacyIndexReduceOp.h
        ../../include/ops/declarable/impl/LegacyReduce3Op.cpp ../../include/ops/declarable/LegacyReduce3Op.h ../../include/ops/declarable/impl/LegacyStatsOp.cpp
        ../../include/ops/declarable/LegacyStatsOp.h ../../include/ops/declarable/impl/LegacyBroadcastOp.cpp ../../include/ops/declarable/LegacyBroadcastOp.h
        ../../include/ops/declarable/generic/convo/im2col.cpp ../../include/ops/declarable/generic/convo/col2im.cpp ../../include/graph/execution/impl/LogicExecutor.cpp
        ../../include/graph/execution/LogicExecutor.h ../../include/graph/execution/impl/LogicScope.cpp ../../include/graph/execution/LogicScope.h
        ../../include/graph/execution/impl/LogicWhile.cpp ../../include/graph/execution/LogicWhile.h ../../include/graph/execution/impl/LogicConditional.cpp
        ../../include/graph/execution/LogicConditional.h ../../include/graph/execution/impl/LogicSwitch.cpp ../../include/graph/execution/LogicSwitch.h ../../include/graph/Intervals.h ../../include/graph/impl/Intervals.cpp
        ../../include/ops/declarable/generic/recurrent_ops.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND "${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 4.9)
    message(FATAL_ERROR "You need at least GCC 4.9")
endif()

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
else()
    message("OPENMP NOT FOUND")
endif()


if(APPLE)
    SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    #SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -static")
elseif(MSYS)
    SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -static")
endif()


#
add_executable(runtests StashTests.cpp SessionLocalTests.cpp FlatBuffersTests.cpp ConvolutionTests.cpp DeclarableOpsTests.cpp DenseLayerTests.cpp  GraphTests.cpp HashUtilsTests.cpp NDArrayTests.cpp TadTests.cpp VariableSpaceTests.cpp VariableTests.cpp WorkspaceTests.cpp JavaInteropTests.cpp MemoryUtilsTests.cpp OpsArena.cpp OpTupleTests.cpp ParityOpsTests.cpp BooleanOpsTests.cpp SwitchTests.cpp ScopeTests.cpp ConditionalTests.cpp LegacyOpsTests.cpp)
target_link_libraries(runtests nd4jcpu gtest gtest_main)