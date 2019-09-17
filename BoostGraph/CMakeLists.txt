cmake_minimum_required(VERSION 3.4.2)
project(ptss-dse)

set(CMAKE_BUILD_TYPE Debug)
set(PROJECT_DESCRIPTION "Malleable DAG scheduling with deadline for peak power minimization")
set(PTSS_DSE_VERSION_MAJOR 1)
set(PTSS_DSE_VERSION_MINOR 0)
set(EXEC1 mDagPkpISLPED2019Ext)
set(EXEC2 mDagPkpJansenBinSearch)

 
## Targets (Convex Optimization+DGGD aka ISLPED extension)
add_executable(${EXEC1} src/ATG.cpp src/testATG.cpp)
target_include_directories(${EXEC1} PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR})
target_compile_options(${EXEC1} PRIVATE -std=c++11 -Wall)
target_link_libraries(${EXEC1} PUBLIC -lm -lecotools -lboost_graph)

## Targets (Tulika's suggestion dated 02/07/2019 aka Malleable-DAG scheduling + Binary search apprach)
# add_executable(${EXEC2} src/Stats.cpp src/ATG.cpp src/KlausHuangLP.cpp src/KlausHuangListM.cpp src/testKlausHuangLP.cpp src/KHMBinSearch.cpp)
# target_include_directories(${EXEC2} PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR} $ENV{GUROBI_HOME}/include)
# target_compile_options(${EXEC2} PRIVATE -std=c++11 -Wall)
# target_link_libraries(${EXEC2} PUBLIC -lm -lecotools -lgurobi_c++ -lgurobi81)
