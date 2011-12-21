all: \
	JSGenerator.h \
	JSGenerator.cpp \
	main.cpp
	g++ -Wall -lprotoc -lprotobuf -lpthread -o protoc-gen-js JSGenerator.cpp main.cpp

test:
	protoc --plugin=protoc-gen-js=protoc-gen-js --js_out=js_out person.proto
