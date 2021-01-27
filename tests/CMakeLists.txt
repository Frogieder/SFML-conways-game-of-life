add_executable(t_neighbours test_neighbour_count.cpp ../src/game.cpp)
add_test(T_neighbours t_neighbours)

add_executable(t_make_grid test_grid_generator.cpp ../src/game.cpp)
add_test(T_make_gird t_make_grid)