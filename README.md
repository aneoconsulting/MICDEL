# elmic

Stands for **e**mbedded **l**anguage for **m**ulti **i**ndex **c**ontainer

__THIS IS PROOF OF CONCEPT AND WORK IS IN PROGRESS__

When you impelement algorithms, you transform mathematics to language (C++) and libraires. This means you have to adapt to the features and limits of these.
For instance, when you set values inside a multi-dimensional container, if you define your container as boost::multi_array, you get :
```cpp
constexpr auto category_count = 10;
constexpr auto month_count = 12;
boost::multi_array<int, 2> sales{boost::extents[category_count][month_count]};
//…
for (auto i = 0; i < category_count; i++) {
  for (auto j = 0; j < month_count; j++) {
    sales[i][j] = 2 * data[i][j] + 1;
  }
}
```

If you define your container as std::map of std::map, you get :
```cpp
std::map<int, std::map<int, int>> sales{};
//…
for (auto i = 0; i < category_count; i++) {
  for (auto j = 0; j < month_count; j++) {
    sales.at(i).at(j) = 2 * data[i][j] + 1;
  }
}

```

How could you adapt your code, to use both with the same syntax, for instance :
```cpp
constexpr auto category_count = 10;
constexpr auto month_count = 12;
container<category_count, month_count> sales{};
//…
for (auto i = 0; i < category_count; i++) {
  for (auto j = 0; j < month_count; j++) {
    sales.at(i, j) = 2 * data[i][j] + 1;
   }
}
```

Meta-containers allows you do by wrapping the underling structure AND its function members.

To view sample, go to src/Implem and explore our examples :
- map tree (std::map of std::map of ...)
- boost multiarray
- tuple map (tuple as index)
- eigen matrix
- graph


