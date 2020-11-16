cmake_minimum_required(VERSION 3.17)
project(DataStructure)

set(CMAKE_CXX_STANDARD 11)

add_executable(Bitree Bitree/main.cpp Bitree/Implementation.h Bitree/BiNode_macro.h Bitree/std.h Bitree/BiTree.h)

add_executable(List List_d/ListNode.h List_d/ListNode_implementation.h List_d/List.h List_d/List_implementation.h List_d/main.cpp)

add_executable(hafman Tree/HuffmanTree.cpp)

