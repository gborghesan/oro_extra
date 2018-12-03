how to make a orocos library
======

in the cmake whre the lib is

```
orocos_library(rtt_period_counter
    src/rtt_period_counter.cpp
    )
```
very last in place of catkin package
```
orocos_generate_package(
  INCLUDE_DIRS include
	LIBRARY rtt_period_counter
)
```

in the package where the lib is imported
```
find_package(oro_extra_lib)
...
target_link_libraries(oct_average
  name_of_the_component
  ${catkin_LIBRARIES}
  )
```
no need to explicitly link, is dumped inside the  ```${catkin_LIBRARIES}``` variable
