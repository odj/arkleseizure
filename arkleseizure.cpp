#include <cstdlib>
#include <sstream>
#include <node.h>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>

using namespace v8;
using namespace std;
using namespace node;
using namespace OpenBabel;

class Arkleseizure : public ObjectWrap {
    static Persistent<FunctionTemplate> converter_template;
    static Persistent<FunctionTemplate> mol_template;
    OBConversion conversion;


public:
    Arkleseizure() {
        conversion.SetInFormat("smi");
        conversion.SetOutFormat("smi");
    }


    static void Initialize(Handle<Object> target) {
        HandleScope scope;

        Local<FunctionTemplate> t = FunctionTemplate::New(New);
        converter_template = Persistent<FunctionTemplate>::New(t);
        converter_template->InstanceTemplate()->SetInternalFieldCount(1);
        converter_template->SetClassName(String::NewSymbol("OBConvert"));

        target->Set(String::New("version"), String::New("0.0.1"));
        NODE_SET_PROTOTYPE_METHOD(converter_template, "SetInFormat", SetInFormat);
        NODE_SET_PROTOTYPE_METHOD(converter_template, "SetOutFormat", SetOutFormat);
        NODE_SET_PROTOTYPE_METHOD(converter_template, "GetOutFormat", GetOutFormat);
        NODE_SET_PROTOTYPE_METHOD(converter_template, "GetInFormat", GetInFormat);
        NODE_SET_PROTOTYPE_METHOD(converter_template, "Convert", Convert);

        target->Set(String::NewSymbol("OBConvert"), converter_template->GetFunction());

        Local<FunctionTemplate> m = FunctionTemplate::New(New);
        mol_template = Persistent<FunctionTemplate>::New(m);
        mol_template->InstanceTemplate()->SetInternalFieldCount(1);
        mol_template->SetClassName(String::NewSymbol("OBMol"));
        target->Set(String::NewSymbol("OBMol"), mol_template->GetFunction());

    }

    static Handle<Value> New(const Arguments &args) {
        HandleScope scope;

        Arkleseizure *arkle = new Arkleseizure();
        arkle->Wrap(args.This());
        return args.This();
    }

    static Handle<Value> SetInFormat(const Arguments &args) {
        HandleScope scope;
        Arkleseizure *ark = ObjectWrap::Unwrap<Arkleseizure>(args.This());
        if (args.Length() == 0 ||
            !args[0]->IsString()) {
            return Undefined();
        }

        String::AsciiValue inputFormat(args[0]->ToString());
        return Boolean::New(ark->conversion.SetInFormat(*inputFormat));
    }

    static Handle<Value> SetOutFormat(const Arguments &args) {
        HandleScope scope;
        Arkleseizure *ark = ObjectWrap::Unwrap<Arkleseizure>(args.This());
        if (args.Length() == 0 ||
            !args[0]->IsString()) {
            return Undefined();
        }

        String::AsciiValue outputFormat(args[0]->ToString());
        return Boolean::New(ark->conversion.SetOutFormat(*outputFormat));
    }

     static Handle<Value> GetInFormat(const Arguments &args) {
        HandleScope scope;
        Arkleseizure *ark = ObjectWrap::Unwrap<Arkleseizure>(args.This());
        OBFormat* inFormat = ark->conversion.GetInFormat();
        return String::New(inFormat->GetID());
    }

     static Handle<Value> GetOutFormat(const Arguments &args) {
        HandleScope scope;
        Arkleseizure *ark = ObjectWrap::Unwrap<Arkleseizure>(args.This());
        OBFormat* outFormat = ark->conversion.GetOutFormat();
        return String::New(outFormat->GetID());
    }


       

    static Handle<Value> Convert(const Arguments &args) {
        HandleScope scope;
        Arkleseizure *ark = ObjectWrap::Unwrap<Arkleseizure>(args.This());

        if (args.Length() == 0 ||
            !args[0]->IsString()) {
            return Undefined();
        }

        OBMol mol;
        String::AsciiValue inputString(args[0]->ToString());
        ark->conversion.ReadString(&mol, *inputString);
        string outputString = ark->conversion.WriteString(&mol, true);
        return String::New(outputString.c_str());
    }

};

Persistent<FunctionTemplate> Arkleseizure::converter_template;
Persistent<FunctionTemplate> Arkleseizure::mol_template;

extern "C" void
init(Handle<Object> target)
{
    HandleScope scope;
    Arkleseizure::Initialize(target);
}

