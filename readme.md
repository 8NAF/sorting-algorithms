# Description

Implementing sorting algorithms, using c++20 standard (g++ 11.2.0).

# run test

```shell
$ g++ -std=c++20 -I./src ./src/test/index.cpp
```

# Supported types

| Container Types          | View Types                     | Iterator Adaptor Types |
|--------------------------|--------------------------------|------------------------|
| std::array               | std::views::all_t              | std::reverse_iterator  |
| std::deque               | std::views::counted            | std::counted_iterator  |
| std::forward_list        | std::ranges::common_view       |                        |
| std::list                | std::ranges::drop_view         |                        |
| std::vector              | std::ranges::drop_while_view   |                        |
| std::span                | std::ranges::elements_view     |                        |
| std::basic_string        | std::ranges::empty_view        |                        |
| std::valarray            | std::ranges::keys_view         |                        |
| std::pmr::deque          | std::ranges::ref_view          |                        |
| std::pmr::forward_list   | std::ranges::reverse_view      |                        |
| std::pmr::list           | std::ranges::single_view       |                        |
| std::pmr::vector         | std::ranges::take_view         |                        |
| std::pmr::basic_string   | std::ranges::take_while_view * |                        |
| raw array                | std::ranges::values_view       |                        |
|                          | std::ranges::subrange          |                        |

`*`: compiler error because `decltype(std::ranges::begin(T)) != decltype(std::ranges::end(T))`.

# Unsupported types

| Types                           | Reason          | Note                                                              |
|---------------------------------|-----------------|-------------------------------------------------------------------|
| std::ranges::iota               | ???             | compiler error with std::ranges::sort                             |
| std::ranges::filter_view        | ???             | compiler error with std::ranges::sort                             |
| std::views::transform_view      | ???             | compiler error with std::ranges::sort                             |
| std::views::join_view           | ???             | compiler error with std::ranges::sort, std::ranges::range = false |
| std::views::split_view          | ???             | compiler error with std::ranges::sort                             |
| std::basic_string_view          | const           |                                                                   |
| std::initializer_list           | const           |                                                                   |
| std::back_insert_iterator       | output iterator |                                                                   |
| std::front_insert_iterator      | output iterator |                                                                   |
| std::insert_iterator            | output iterator |                                                                   |
| std::ranges::basic_istream_view | input iterator  |                                                                   |
| std::move_iterator              | ???             | compiler error with std::ranges::sort                             |
| std::common_iterator            | ???             | compiler error with std::ranges::sort                             |

# Hold-on

| Types                                | Reason |
|--------------------------------------|--------|
| std::ranges::owning_view             | gcc 12 |
| std::ranges::lazy_split_view         | gcc 12 |
| std::ranges::zip_view                | C++23  |
| std::ranges::zip_transform_view      | C++23  |
| std::ranges::adjacent_view           | C++23  |
| std::ranges::adjacent_transform_view | C++23  |
| std::ranges::join_with_view          | C++23  |

# Todo

-	fix `projection`
-	merge `sorting algorithm` abstract class and `family` abstract class into one
-	add `for_each_iter`
-   implementing BST
