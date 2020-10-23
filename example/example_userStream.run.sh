

libcurl_dir=../lib/libcurl-7.69.1
libcurl_lib=${libcurl_dir}/lib

libwebsockets_dir=../lib/libwebsockets-3.2.2
libwebsockets_lib=${libwebsockets_dir}/lib

libbinacpp_dir=../lib/libbinacpp
libbinacpp_lib=${libbinacpp_dir}/lib

export SSL_CERT_FILE=`pwd`/cacert.pem
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$libcurl_lib:$libwebsockets_lib:$libbinacpp_lib

./example_userStream $@
