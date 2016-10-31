#objects1 = main.o goods.o menu_print.o \
		  #login.o customer.o shop.o storage.o log.o
#
# vpath <pattern> <directories>
# vpath %.h ../c++11  # 到该目录搜索文件
# vpath %.h ../c++14  # 可以指定多个目录
# vpath %.c ../c++14  # 可以指定多个pattern
# all : one two three # 利用伪目标特性，可以一次生成多个文件
# .PHONY all  #.PHONY all al ll #也可以同时指定多个伪目标

#login.o : login.cpp login.h
	#g++ -std=c++11  -c -o login.o login.cpp 

#customer.o : customer.cpp customer.h 
	#g++ -std=c++11  -c -o customer.o customer.cpp

objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
jd : $(objects) ; @echo 最后的一点工作... 
	@g++ -o jd $(objects) -std=c++11 -g

cxx11_obj := $(objects) 
$(cxx11_obj) : %.o: %.cpp
	g++ -c -g -std=c++11 $< -o $@

%.d: %.cpp
	@set -e; rm -f $@; \
		g++ -M -std=c++11 $< >; $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ >; $@; \
		rm -f $@.$$$$
#sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g'
.PHONY : clean
# 清除文件 
clean :
	-rm -f *.o jd 
