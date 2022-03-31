# Description

Implementing sorting algorithms, using c++20 standard (g++ 11.2.0)

# run test

```shell
$ g++ -std=c++20 -I./src ./src/test/*_family/index.cpp
```

# Supported types

| Container Types          | Raw Types | View Types                     | Iterator Adaptor Types |
|--------------------------|-----------|--------------------------------|------------------------|
| std::array               | array     | std::views::all_t *            | std::reverse_iterator  |
| std::deque               | pointer   | std::views::counted *          | std::counted_iterator  |
| std::forward_list        |           | std::ranges::common_view *     |                        |
| std::list                |           | std::ranges::drop_view *       |                        |
| std::vector              |           | std::ranges::drop_while_view * |                        |
| std::span                |           | std::ranges::elements_view *   |                        |
| std::basic_string        |           | std::ranges::empty_view *      |                        |
| std::valarray            |           | std::ranges::keys_view *       |                        |
| std::pmr::deque *        |           | std::ranges::ref_view *        |                        |
| std::pmr::forward_list * |           | std::ranges::reverse_view *    |                        |
| std::pmr::list *         |           | std::ranges::single_view *     |                        |
| std::pmr::vector *       |           | std::ranges::take_view *       |                        |
| std::pmr::basic_string * |           | std::ranges::take_while_view * |                        |
|                          |           | std::ranges::values_view *     |                        |
|                          |           | std::ranges::subrange *        |                        |

`*`: not working for now

# Unsupported types

| Types                           | Reason          | Note                                  |
|---------------------------------|-----------------|---------------------------------------|
| std::ranges::iota               | ???             | compiler error with std::ranges::sort |
| std::ranges::filter_view        | ???             | compiler error with std::ranges::sort |
| std::views::transform_view      | ???             | compiler error with std::ranges::sort |
| std::views::join_view           | ???             | compiler error with std::ranges::sort |
| std::views::split_view          | ???             | compiler error with std::ranges::sort |
| std::basic_string_view          | const           |                                       |
| std::initializer_list           | const           |                                       |
| std::back_insert_iterator       | output iterator |                                       |
| std::front_insert_iterator      | output iterator |                                       |
| std::insert_iterator            | output iterator |                                       |
| std::ranges::basic_istream_view | input iterator  |                                       |
| std::move_iterator              | ???             | compiler error with std::ranges::sort |
| std::common_iterator            | ???             | compiler error with std::ranges::sort |

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

- 	change `comparator` concept
-   support `projection`
-   optimize `comb sort`
-   improve `make_heap`
-   support `sentinel`
-	support `dangling`
- 	support `view`
-   implementing BST
-   handle case `gap > 1` in `binary search` function
