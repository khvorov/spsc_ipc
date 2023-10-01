find_package(Boost REQUIRED)

add_executable(Producer Producer.cpp)
target_link_libraries(Producer Boost::boost)

add_executable(Consumer Consumer.cpp)
target_link_libraries(Consumer Boost::boost)
