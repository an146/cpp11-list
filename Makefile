test: test_list
	./test_list

test_list: test_list.cpp dummy.cpp list.hpp
	$(CXX) -O2 -std=c++11 -o $@ test_list.cpp dummy.cpp
