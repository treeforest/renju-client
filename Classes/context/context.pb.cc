// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: context.proto

#include "context.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
class ContextDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Context> _instance;
} _Context_default_instance_;
static void InitDefaultsscc_info_Context_context_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_Context_default_instance_;
    new (ptr) ::Context();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Context::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Context_context_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_Context_context_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_context_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_context_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_context_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_context_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Context, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Context, result_),
  PROTOBUF_FIELD_OFFSET(::Context, session_),
  PROTOBUF_FIELD_OFFSET(::Context, serviceid_),
  PROTOBUF_FIELD_OFFSET(::Context, methodid_),
  PROTOBUF_FIELD_OFFSET(::Context, data_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Context)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_Context_default_instance_),
};

const char descriptor_table_protodef_context_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\rcontext.proto\"d\n\007Context\022\025\n\006result\030\001 \001"
  "(\0162\005.Code\022\017\n\007session\030\002 \001(\r\022\021\n\tserviceId\030"
  "\003 \001(\r\022\020\n\010methodId\030\004 \001(\r\022\014\n\004data\030\005 \001(\014*^\n"
  "\004Code\022\013\n\007SUCCESS\020\000\022\020\n\014ERR_CHECKSUM\020\001\022\020\n\014"
  "ERR_GET_HEAD\020\002\022\023\n\017ERR_UNPACK_HEAD\020\003\022\020\n\014E"
  "RR_GET_DATA\020\004B\013Z\t.;contextb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_context_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_context_2eproto_sccs[1] = {
  &scc_info_Context_context_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_context_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_context_2eproto = {
  false, false, descriptor_table_protodef_context_2eproto, "context.proto", 234,
  &descriptor_table_context_2eproto_once, descriptor_table_context_2eproto_sccs, descriptor_table_context_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_context_2eproto::offsets,
  file_level_metadata_context_2eproto, 1, file_level_enum_descriptors_context_2eproto, file_level_service_descriptors_context_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_context_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_context_2eproto)), true);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Code_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_context_2eproto);
  return file_level_enum_descriptors_context_2eproto[0];
}
bool Code_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}


// ===================================================================

void Context::InitAsDefaultInstance() {
}
class Context::_Internal {
 public:
};

Context::Context(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Context)
}
Context::Context(const Context& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_data().empty()) {
    data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_data(),
      GetArena());
  }
  ::memcpy(&result_, &from.result_,
    static_cast<size_t>(reinterpret_cast<char*>(&methodid_) -
    reinterpret_cast<char*>(&result_)) + sizeof(methodid_));
  // @@protoc_insertion_point(copy_constructor:Context)
}

void Context::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_Context_context_2eproto.base);
  data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(&result_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&methodid_) -
      reinterpret_cast<char*>(&result_)) + sizeof(methodid_));
}

Context::~Context() {
  // @@protoc_insertion_point(destructor:Context)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Context::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  data_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Context::ArenaDtor(void* object) {
  Context* _this = reinterpret_cast< Context* >(object);
  (void)_this;
}
void Context::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Context::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Context& Context::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Context_context_2eproto.base);
  return *internal_default_instance();
}


void Context::Clear() {
// @@protoc_insertion_point(message_clear_start:Context)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::memset(&result_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&methodid_) -
      reinterpret_cast<char*>(&result_)) + sizeof(methodid_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Context::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .Code result = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_result(static_cast<::Code>(val));
        } else goto handle_unusual;
        continue;
      // uint32 session = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          session_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 serviceId = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          serviceid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 methodId = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          methodid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bytes data = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          auto str = _internal_mutable_data();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Context::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Context)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .Code result = 1;
  if (this->result() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_result(), target);
  }

  // uint32 session = 2;
  if (this->session() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_session(), target);
  }

  // uint32 serviceId = 3;
  if (this->serviceid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_serviceid(), target);
  }

  // uint32 methodId = 4;
  if (this->methodid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(4, this->_internal_methodid(), target);
  }

  // bytes data = 5;
  if (this->data().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        5, this->_internal_data(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Context)
  return target;
}

size_t Context::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Context)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes data = 5;
  if (this->data().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_data());
  }

  // .Code result = 1;
  if (this->result() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_result());
  }

  // uint32 session = 2;
  if (this->session() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_session());
  }

  // uint32 serviceId = 3;
  if (this->serviceid() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_serviceid());
  }

  // uint32 methodId = 4;
  if (this->methodid() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_methodid());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Context::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Context)
  GOOGLE_DCHECK_NE(&from, this);
  const Context* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Context>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Context)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Context)
    MergeFrom(*source);
  }
}

void Context::MergeFrom(const Context& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Context)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.data().size() > 0) {
    _internal_set_data(from._internal_data());
  }
  if (from.result() != 0) {
    _internal_set_result(from._internal_result());
  }
  if (from.session() != 0) {
    _internal_set_session(from._internal_session());
  }
  if (from.serviceid() != 0) {
    _internal_set_serviceid(from._internal_serviceid());
  }
  if (from.methodid() != 0) {
    _internal_set_methodid(from._internal_methodid());
  }
}

void Context::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Context)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Context::CopyFrom(const Context& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Context)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Context::IsInitialized() const {
  return true;
}

void Context::InternalSwap(Context* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  data_.Swap(&other->data_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Context, methodid_)
      + sizeof(Context::methodid_)
      - PROTOBUF_FIELD_OFFSET(Context, result_)>(
          reinterpret_cast<char*>(&result_),
          reinterpret_cast<char*>(&other->result_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Context::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Context* Arena::CreateMaybeMessage< ::Context >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Context >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
