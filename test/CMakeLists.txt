catkin_add_gtest(${PROJECT_NAME}_event_echo event_echo_main.cpp    )

#target_link_libraries( event_echo_main orocos-ocl-taskbrowser-${OROCOS_TARGET} )
target_link_libraries( ${PROJECT_NAME}_event_echo event_echo ${catkin_LIBRARIES})
