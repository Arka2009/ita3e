# ita3e : What is it ?
A collection of Agorithms in topics as diverse as computational geometry, 
scientific computing, quantitative finance, physics simulations, statistics, 
bioinformatics, DSP, EDA etc. 

## ita3e : Objectives ?
1. Learning Practical (sort of) implementation of algorithms and data structures in C/C++.
2. Complexity Analysis (cache, time and space) of algorithms.
3. Benchmarking, Energy and power analyses of applications.
4. Act as a testbed for the following
	4.1 Kernel/Application benchmarking.
	4.2 Inspect code generation and assembly code quality
	4.3 Use of tools like gdb/valgrind/PIN.
5. Not meant to be a production codebase. So dont expect rigorous 
   software development techniques to be applied consistently.
6. The level of abstraction is resticted to C/C++, any
   higher level programming abstraction are to be avoided. 
   The basic objective to understand how programs behave under the hood.
   process.

## Skill required/acquired
1. C/C++ programming in the UNIX environment.
2. C/C++ based parallel programming frameworks and libraries 
   (pthreads, openMP, Intel TBB and cilk)
3. Learn task and data parallelism and their implementation using thread and SIMD instructions.
   Try to understand the compiler optimizations (IR level and below) and
   code generation process.
4. Dynamic analyses like gdb/valgrind/PIN.
5. Build tools like GNUMake/CMake.
6. Computer System Security concepts

## Other cool/similar projects
1. Check C++ STL implementation from scratch [stl-from-scatch](https://github.com/topperc/stl-from-scratch)
2. Also check the implementation of Discrete Event Simulators in C++ (Book by James Nutaro). In particular
[gem5](https://www.gem5.org/) for computer systems. Also check [Sniper](http://snipersim.org/w/The_Sniper_Multi-Core_Simulator) simulator.
3. Use [GSL](https://www.gnu.org/software/gsl/) for mathematical functions.
4. Use [Boost.Graph](https://www.boost.org/doc/libs/1_72_0/libs/graph/doc/index.html) for graph algorithms in C/C++.
5. Use [srsLTE](https://github.com/srsLTE/srsLTE) for SDR for 3GPP based cellular communication.
6. Use [GNURadio](https://github.com/gnuradio/gnuradio) for implementation of DSP kernels and (simulink-like) interfaces for creating Radio Systems. [Volk](https://www.libvolk.org/) provides SIMD implementation for many of the core DSP functions.
7. Use [LLVM](https://github.com/llvm/llvm-project) for program analyses/compilation/code generation.