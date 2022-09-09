export PKG_CONFIG_PATH=PKG_CONFIG_PATH:/usr/local/lib/pkgconfig/
export LD_LIBRARY_PATH=LD_LIBRARY_PATH:/usr/local/lib

LDFLAGS = -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl

CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11

GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

all: dist_mem_mtx_impl dir_node

dist_mem_mtx_impl: communicate.pb.o communicate.grpc.pb.o dist_mem_mtx_impl.o
	$(CXX) $^ $(LDFLAGS) -o $@

dir_node: communicate.pb.o communicate.grpc.pb.o dir_node.o
	$(CXX) $^ $(LDFLAGS) -o $@

%.grpc.pb.cc: %.proto
	protoc --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto
	protoc --cpp_out=. $<

clean:
	rm -f *.o *.pb.cc *.pb.h dist_mem_mtx_impl dir_node
