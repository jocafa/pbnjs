#include <google/protobuf/compiler/plugin.h>
#include "JSGenerator.h"

int main (int argc, char* argv[]) {
	google::protobuf::compiler::javascript::JSGenerator generator;
	return google::protobuf::compiler::PluginMain(argc, argv, &generator);
}
