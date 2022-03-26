# Description

Implementing sorting algorithms, using c++20 standard (g++ 11.2.0)

# run test

```shell
$ g++ -std=c++20 -I./src ./src/test/*_family/*.test.cpp
```

# todo

-   support `input iterator` for `bubble sort`
-   support `input iterator` for `odd even sort`
-   improve `make_heap`
-   support `projection`
-   handle case `gap > 1` in `binary search` function
-   add `get gap sequence` option for `shell sort`
-   support `sentinel`
-   add `insertion function` option for `insertion sort` family (to optimize for `std::list` & `std::forward_list`)
-   optimize `comb sort`
-   implementing BST
