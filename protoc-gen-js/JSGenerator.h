#ifndef JSGENERATOR_H
#define JSGENERATOR_H

#include <string>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/printer.h>

namespace google {
	namespace protobuf {
		namespace compiler {
			namespace javascript {

				class JSGenerator : public CodeGenerator {
					public:
						JSGenerator();
						~JSGenerator();

						bool Generate(
								const FileDescriptor* file,
								const string& parameter,
								GeneratorContext* generator_context,
								string* error) const;


					private:
						mutable Mutex mutex_;
						mutable const FileDescriptor* file_;
						mutable io::Printer* printer_;
						void PrintMessages() const;
				};
			}
		}
	}
}

#endif /* end of include guard: JSGENERATOR_H */
