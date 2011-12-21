#include "JSGenerator.h"
#include <google/protobuf/descriptor.pb.h>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream.h>

namespace google {
	namespace protobuf {
		namespace compiler {
			namespace javascript {

				JSGenerator::JSGenerator() {}
				JSGenerator::~JSGenerator() {}

				bool JSGenerator::Generate(
						const FileDescriptor* file,
						const string& parameter,
						GeneratorContext* generator_context,
						string* error) const {

					MutexLock lock(&mutex_);
					file_ = file;

					string filename = file->name();
					filename += ".js";

					scoped_ptr<io::ZeroCopyOutputStream> output(generator_context->Open(filename));
					GOOGLE_CHECK(output.get());
					io::Printer printer(output.get(), '$');
					printer_ = &printer;

					map<string, string> m;
					m["name"] = file->name();
					m["package"] = file->package();

					printer.Print(m, "name = $name$\n\npackage = $package$\n\n");
					PrintMessages();
					return !printer.failed();
				}

				void JSGenerator::PrintMessages() const {
					for (int i = 0; i < file_->message_type_count(); i++) {
						string name = file_->message_type(i)->name();
						printer_->Print("message $name$\n", "name", name);
						printer_->Indent();
						for (int j = 0; j < file_->message_type(i)->field_count(); j++) {
							string field_name = file_->message_type(i)->field(j)->name();
							printer_->Print("field $field_name$\n", "field_name", field_name);
						}
						printer_->Outdent();
					}
				}
			}
		}
	}
}
