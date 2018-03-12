cmake_minimum_required(VERSION 3.9)
project(interview)

set(CMAKE_CXX_STANDARD 11)

add_executable(interview main.cpp bitset/sort.cpp bitset/procdata.cpp duoluguibing/ExternSort.cpp duoluguibing/externSort.c Quick/selectQuick.cpp RedBlackTree/rb_tree.c string/strstr.c string/strcpy.c string/strncpy.c string/strchr.c string/strcmp.c string/strcat.c string/strlen.c string/strncat.c string/strncmp.c string/strpbrk.c string/strcspn.c string/strspn.c string/strnset.c string/memcmp.c string/memcpy.c string/memset.c string/memmove.c string/memchr.c hash/hash.c)