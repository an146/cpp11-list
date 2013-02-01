test: test_list
	./test_list

test_list: test_list.cpp list.hpp
	$(CXX) -std=c++11 -o $@ $<
