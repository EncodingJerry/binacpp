



libcurl_dir=../lib/libcurl-7.69.1
libcurl_include=${libcurl_dir}/include
libcurl_lib=${libcurl_dir}/lib

jsoncpp_dir=../lib/jsoncpp-1.8.3
jsoncpp_include=${jsoncpp_dir}/include
jsoncpp_src=${jsoncpp_dir}/src


libwebsockets_dir=../lib/libwebsockets-3.2.2
libwebsockets_include=${libwebsockets_dir}/include
libwebsockets_lib=${libwebsockets_dir}/lib

libbinacpp_dir=../lib/libbinacpp
libbinacpp_include=${libbinacpp_dir}/include
libbinacpp_lib=${libbinacpp_dir}/lib

%.o: %.cpp
	@echo -n "\nMaking $@\n\n\n"
	g++ -I$(libcurl_include) -I$(libwebsockets_include) -I$(libbinacpp_include) -I$(jsoncpp_include) \
	-c $< 
	-g -o $@

TARGETS = example_aggTrades  example  example_depthCache  example_klines  example_template  example_userStream  example_wapi
all: $(TARGETS)

$(TARGETS): % : %.o jsoncpp.o
	g++ -I$(libcurl_include) -I$(libwebsockets_include) -I$(libbinacpp_include) \
	$@.o jsoncpp.o \
	-L$(libcurl_lib) \
	-L$(libwebsockets_lib) \
	-L$(libbinacpp_lib) \
	-lbinacpp -lcurl -lcrypto -lwebsockets  -g -o $@
	cat run.sh.template  | sed s/%executable%/$@/ > $@.run.sh
	chmod 755 $@.run.sh


jsoncpp.o: $(jsoncpp_src)/jsoncpp.cpp 
	g++ -I$(jsoncpp_include) -c $< -o $@

clean:
	rm $(TARGETS)
	rm *.o
	rm *.sh

.PHONY: clean