cmake_minimum_required(VERSION 3.4.2)
project(ita3e)

set(CMAKE_BUILD_TYPE Debug)
set(PROJECT_DESCRIPTION "Algorithm implmentations in C/C++ for self learning")
set(PTSS_DSE_VERSION_MAJOR 1)
set(PTSS_DSE_VERSION_MINOR 0)
set(EXEC1 basicDS)
set(EXEC2 boostGraphTut)

set(SRCS1 DataStructures/src/ita3e.c 
		 DataStructures/src/ita3e_queue.c 
		 DataStructures/src/ita3e_queue_test.c
		 DataStructures/src/ita3e_stack.c
		 DataStructures/src/ita3e_stack_test.c
		 DataStructures/src/ita3e_indexedseq.c
		 DataStructures/src/ita3e_indexedseq_test.c
		 DataStructures/src/ita3e_sort.c
		 DataStructures/src/ita3e_sort_test.c
		 DataStructures/src/ita3e_list.c
		 DataStructures/src/ita3e_list_test.c
		 DataStructures/src/ita3e_btree.c
		 DataStructures/src/ita3e_btree_test.c
		 DataStructures/src/ita3e_adjlist.c
		 DataStructures/src/main.c)

# Basic DS target
add_executable(${EXEC1} ${SRCS1})
target_include_directories(${EXEC1} PUBLIC ${PROJECT_SOURCE_DIR}/DataStructures/include ${PROJECT_BINARY_DIR})
target_compile_options(${EXEC1} PRIVATE --std=c11 -Wall -O0)
target_link_libraries(${EXEC1} PUBLIC -lm -lecotools -lboost_graph)

# Boost.Graph target + Also contains algorithm
add_executable(${EXEC2} BoostGraph/src/ATG.cpp BoostGraph/src/testATG.cpp)
target_include_directories(${EXEC2} PUBLIC ${PROJECT_SOURCE_DIR}/BoostGraph/include ${PROJECT_BINARY_DIR})
target_compile_options(${EXEC2} PRIVATE -std=c++11 -Wall)
target_link_libraries(${EXEC2} PUBLIC -lm -lecotools -lboost_graph)