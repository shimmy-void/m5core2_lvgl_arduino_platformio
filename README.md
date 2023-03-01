# Examples and Demos of LVGL for M5Stack Core2, Arduino framework, VSCode, Platform IO environment

## How to use

1. Clone this repository on a directory.

```shell
    git clone https://github.com/shimmy-void/m5core2_lvgl_arduino_platformio.git
```

2. Edit `/src/main.cpp` and `/lib/lv_conf.h` as follows.

### Examples

1. Uncomment to include "exampless/lv_examples.h" in `main.cpp`.

```cpp
#include "examples/lv_examples.h"   // only used for lvgl examples
// #include "demos/lv_demos.h"         // only used for lvgl demos
```
2. Uncomment one of the example functions, and comment out other example and demo functions in the `setup()` of `main.cpp`.

```cpp
// Uncomment only one of the following functions to run a example or demo
// Examples
// Examples in anim/lv_example_anim.h
lv_example_anim_1();
// lv_example_anim_2();
// lv_example_anim_3();
// lv_example_anim_timeline_1();
```

3. Make sure that `LV_BUILD_EXAMPLES` macro is defined as `1` in `lv_conf.h`.

```cpp
/*==================
* EXAMPLES
*==================*/

/*Enable the examples to be built with the library*/
#define LV_BUILD_EXAMPLES 1
```

### Demos

1. Uncomment to include "demos/lv_demos.h" in main.cpp.

```cpp
// #include "examples/lv_examples.h"   // only used for lvgl examples
#include "demos/lv_demos.h"         // only used for lvgl demos
```

2. Uncomment one of the demo functions, and comment out other example and demo functions in the `setup()` of `main.cpp`.

```cpp
// Demos
// Demos in benchmark/lv_demo_benchmark.h
// Define LV_USE_DEMO_BENCHMARK in lib/lv_conf.h to use these demos
lv_demo_benchmark(LV_DEMO_BENCHMARK_MODE_RENDER_AND_DRIVER);
// lv_demo_benchmark(LV_DEMO_BENCHMARK_MODE_REAL);
// lv_demo_benchmark(LV_DEMO_BENCHMARK_MODE_RENDER_ONLY);
// lv_demo_benchmark_run_scene(LV_DEMO_BENCHMARK_MODE_RENDER_AND_DRIVER, 0);
```

3. Assign one of the `LV_USE_DEMO_**` macros associated with the demo which you want to build to `1` in `lv_conf.h`.

```cpp
/*Benchmark your system*/
#define LV_USE_DEMO_BENCHMARK 1
#if LV_USE_DEMO_BENCHMARK
    /*Use RGB565A8 images with 16 bit color depth instead of ARGB8565*/
    #define LV_DEMO_BENCHMARK_RGB565A8 0
#endif
```

And then, build and download the program, Enjoy it!

## Dependency

- [LVGL](https://github.com/lvgl/lvgl)
