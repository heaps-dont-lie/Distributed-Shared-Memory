// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: communicate.proto

#ifndef PROTOBUF_INCLUDED_communicate_2eproto
#define PROTOBUF_INCLUDED_communicate_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_communicate_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_communicate_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[5]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_communicate_2eproto();
namespace communicate {
class Ack;
class AckDefaultTypeInternal;
extern AckDefaultTypeInternal _Ack_default_instance_;
class GetInfo;
class GetInfoDefaultTypeInternal;
extern GetInfoDefaultTypeInternal _GetInfo_default_instance_;
class Node_state_info;
class Node_state_infoDefaultTypeInternal;
extern Node_state_infoDefaultTypeInternal _Node_state_info_default_instance_;
class ReqLock;
class ReqLockDefaultTypeInternal;
extern ReqLockDefaultTypeInternal _ReqLock_default_instance_;
class Var_Ds_Info;
class Var_Ds_InfoDefaultTypeInternal;
extern Var_Ds_InfoDefaultTypeInternal _Var_Ds_Info_default_instance_;
}  // namespace communicate
namespace google {
namespace protobuf {
template<> ::communicate::Ack* Arena::CreateMaybeMessage<::communicate::Ack>(Arena*);
template<> ::communicate::GetInfo* Arena::CreateMaybeMessage<::communicate::GetInfo>(Arena*);
template<> ::communicate::Node_state_info* Arena::CreateMaybeMessage<::communicate::Node_state_info>(Arena*);
template<> ::communicate::ReqLock* Arena::CreateMaybeMessage<::communicate::ReqLock>(Arena*);
template<> ::communicate::Var_Ds_Info* Arena::CreateMaybeMessage<::communicate::Var_Ds_Info>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace communicate {

// ===================================================================

class ReqLock final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:communicate.ReqLock) */ {
 public:
  ReqLock();
  virtual ~ReqLock();

  ReqLock(const ReqLock& from);

  inline ReqLock& operator=(const ReqLock& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ReqLock(ReqLock&& from) noexcept
    : ReqLock() {
    *this = ::std::move(from);
  }

  inline ReqLock& operator=(ReqLock&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const ReqLock& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ReqLock* internal_default_instance() {
    return reinterpret_cast<const ReqLock*>(
               &_ReqLock_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(ReqLock* other);
  friend void swap(ReqLock& a, ReqLock& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ReqLock* New() const final {
    return CreateMaybeMessage<ReqLock>(nullptr);
  }

  ReqLock* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ReqLock>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ReqLock& from);
  void MergeFrom(const ReqLock& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ReqLock* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint32 seq_num = 1;
  void clear_seq_num();
  static const int kSeqNumFieldNumber = 1;
  ::google::protobuf::uint32 seq_num() const;
  void set_seq_num(::google::protobuf::uint32 value);

  // uint32 node_num = 2;
  void clear_node_num();
  static const int kNodeNumFieldNumber = 2;
  ::google::protobuf::uint32 node_num() const;
  void set_node_num(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:communicate.ReqLock)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 seq_num_;
  ::google::protobuf::uint32 node_num_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_communicate_2eproto;
};
// -------------------------------------------------------------------

class Ack final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:communicate.Ack) */ {
 public:
  Ack();
  virtual ~Ack();

  Ack(const Ack& from);

  inline Ack& operator=(const Ack& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Ack(Ack&& from) noexcept
    : Ack() {
    *this = ::std::move(from);
  }

  inline Ack& operator=(Ack&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Ack& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Ack* internal_default_instance() {
    return reinterpret_cast<const Ack*>(
               &_Ack_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Ack* other);
  friend void swap(Ack& a, Ack& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Ack* New() const final {
    return CreateMaybeMessage<Ack>(nullptr);
  }

  Ack* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Ack>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Ack& from);
  void MergeFrom(const Ack& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Ack* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint32 ack = 1;
  void clear_ack();
  static const int kAckFieldNumber = 1;
  ::google::protobuf::uint32 ack() const;
  void set_ack(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:communicate.Ack)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 ack_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_communicate_2eproto;
};
// -------------------------------------------------------------------

class Var_Ds_Info final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:communicate.Var_Ds_Info) */ {
 public:
  Var_Ds_Info();
  virtual ~Var_Ds_Info();

  Var_Ds_Info(const Var_Ds_Info& from);

  inline Var_Ds_Info& operator=(const Var_Ds_Info& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Var_Ds_Info(Var_Ds_Info&& from) noexcept
    : Var_Ds_Info() {
    *this = ::std::move(from);
  }

  inline Var_Ds_Info& operator=(Var_Ds_Info&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Var_Ds_Info& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Var_Ds_Info* internal_default_instance() {
    return reinterpret_cast<const Var_Ds_Info*>(
               &_Var_Ds_Info_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Var_Ds_Info* other);
  friend void swap(Var_Ds_Info& a, Var_Ds_Info& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Var_Ds_Info* New() const final {
    return CreateMaybeMessage<Var_Ds_Info>(nullptr);
  }

  Var_Ds_Info* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Var_Ds_Info>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Var_Ds_Info& from);
  void MergeFrom(const Var_Ds_Info& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Var_Ds_Info* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint64 psu_ds_start = 1;
  void clear_psu_ds_start();
  static const int kPsuDsStartFieldNumber = 1;
  ::google::protobuf::uint64 psu_ds_start() const;
  void set_psu_ds_start(::google::protobuf::uint64 value);

  // uint32 tag = 2;
  void clear_tag();
  static const int kTagFieldNumber = 2;
  ::google::protobuf::uint32 tag() const;
  void set_tag(::google::protobuf::uint32 value);

  // uint32 curr_page = 3;
  void clear_curr_page();
  static const int kCurrPageFieldNumber = 3;
  ::google::protobuf::uint32 curr_page() const;
  void set_curr_page(::google::protobuf::uint32 value);

  // uint32 tot_pages = 4;
  void clear_tot_pages();
  static const int kTotPagesFieldNumber = 4;
  ::google::protobuf::uint32 tot_pages() const;
  void set_tot_pages(::google::protobuf::uint32 value);

  // uint32 node_id = 5;
  void clear_node_id();
  static const int kNodeIdFieldNumber = 5;
  ::google::protobuf::uint32 node_id() const;
  void set_node_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:communicate.Var_Ds_Info)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint64 psu_ds_start_;
  ::google::protobuf::uint32 tag_;
  ::google::protobuf::uint32 curr_page_;
  ::google::protobuf::uint32 tot_pages_;
  ::google::protobuf::uint32 node_id_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_communicate_2eproto;
};
// -------------------------------------------------------------------

class Node_state_info final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:communicate.Node_state_info) */ {
 public:
  Node_state_info();
  virtual ~Node_state_info();

  Node_state_info(const Node_state_info& from);

  inline Node_state_info& operator=(const Node_state_info& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Node_state_info(Node_state_info&& from) noexcept
    : Node_state_info() {
    *this = ::std::move(from);
  }

  inline Node_state_info& operator=(Node_state_info&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Node_state_info& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Node_state_info* internal_default_instance() {
    return reinterpret_cast<const Node_state_info*>(
               &_Node_state_info_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(Node_state_info* other);
  friend void swap(Node_state_info& a, Node_state_info& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Node_state_info* New() const final {
    return CreateMaybeMessage<Node_state_info>(nullptr);
  }

  Node_state_info* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Node_state_info>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Node_state_info& from);
  void MergeFrom(const Node_state_info& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Node_state_info* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint32 tag = 1;
  void clear_tag();
  static const int kTagFieldNumber = 1;
  ::google::protobuf::uint32 tag() const;
  void set_tag(::google::protobuf::uint32 value);

  // uint32 effect = 2;
  void clear_effect();
  static const int kEffectFieldNumber = 2;
  ::google::protobuf::uint32 effect() const;
  void set_effect(::google::protobuf::uint32 value);

  // uint32 node_id = 3;
  void clear_node_id();
  static const int kNodeIdFieldNumber = 3;
  ::google::protobuf::uint32 node_id() const;
  void set_node_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:communicate.Node_state_info)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 tag_;
  ::google::protobuf::uint32 effect_;
  ::google::protobuf::uint32 node_id_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_communicate_2eproto;
};
// -------------------------------------------------------------------

class GetInfo final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:communicate.GetInfo) */ {
 public:
  GetInfo();
  virtual ~GetInfo();

  GetInfo(const GetInfo& from);

  inline GetInfo& operator=(const GetInfo& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetInfo(GetInfo&& from) noexcept
    : GetInfo() {
    *this = ::std::move(from);
  }

  inline GetInfo& operator=(GetInfo&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const GetInfo& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetInfo* internal_default_instance() {
    return reinterpret_cast<const GetInfo*>(
               &_GetInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  void Swap(GetInfo* other);
  friend void swap(GetInfo& a, GetInfo& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetInfo* New() const final {
    return CreateMaybeMessage<GetInfo>(nullptr);
  }

  GetInfo* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<GetInfo>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const GetInfo& from);
  void MergeFrom(const GetInfo& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(GetInfo* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated int32 pg_rq = 2;
  int pg_rq_size() const;
  void clear_pg_rq();
  static const int kPgRqFieldNumber = 2;
  ::google::protobuf::int32 pg_rq(int index) const;
  void set_pg_rq(int index, ::google::protobuf::int32 value);
  void add_pg_rq(::google::protobuf::int32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      pg_rq() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_pg_rq();

  // int32 page_req = 1;
  void clear_page_req();
  static const int kPageReqFieldNumber = 1;
  ::google::protobuf::int32 page_req() const;
  void set_page_req(::google::protobuf::int32 value);

  // uint32 ack = 3;
  void clear_ack();
  static const int kAckFieldNumber = 3;
  ::google::protobuf::uint32 ack() const;
  void set_ack(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:communicate.GetInfo)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > pg_rq_;
  mutable std::atomic<int> _pg_rq_cached_byte_size_;
  ::google::protobuf::int32 page_req_;
  ::google::protobuf::uint32 ack_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_communicate_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ReqLock

// uint32 seq_num = 1;
inline void ReqLock::clear_seq_num() {
  seq_num_ = 0u;
}
inline ::google::protobuf::uint32 ReqLock::seq_num() const {
  // @@protoc_insertion_point(field_get:communicate.ReqLock.seq_num)
  return seq_num_;
}
inline void ReqLock::set_seq_num(::google::protobuf::uint32 value) {
  
  seq_num_ = value;
  // @@protoc_insertion_point(field_set:communicate.ReqLock.seq_num)
}

// uint32 node_num = 2;
inline void ReqLock::clear_node_num() {
  node_num_ = 0u;
}
inline ::google::protobuf::uint32 ReqLock::node_num() const {
  // @@protoc_insertion_point(field_get:communicate.ReqLock.node_num)
  return node_num_;
}
inline void ReqLock::set_node_num(::google::protobuf::uint32 value) {
  
  node_num_ = value;
  // @@protoc_insertion_point(field_set:communicate.ReqLock.node_num)
}

// -------------------------------------------------------------------

// Ack

// uint32 ack = 1;
inline void Ack::clear_ack() {
  ack_ = 0u;
}
inline ::google::protobuf::uint32 Ack::ack() const {
  // @@protoc_insertion_point(field_get:communicate.Ack.ack)
  return ack_;
}
inline void Ack::set_ack(::google::protobuf::uint32 value) {
  
  ack_ = value;
  // @@protoc_insertion_point(field_set:communicate.Ack.ack)
}

// -------------------------------------------------------------------

// Var_Ds_Info

// uint64 psu_ds_start = 1;
inline void Var_Ds_Info::clear_psu_ds_start() {
  psu_ds_start_ = PROTOBUF_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Var_Ds_Info::psu_ds_start() const {
  // @@protoc_insertion_point(field_get:communicate.Var_Ds_Info.psu_ds_start)
  return psu_ds_start_;
}
inline void Var_Ds_Info::set_psu_ds_start(::google::protobuf::uint64 value) {
  
  psu_ds_start_ = value;
  // @@protoc_insertion_point(field_set:communicate.Var_Ds_Info.psu_ds_start)
}

// uint32 tag = 2;
inline void Var_Ds_Info::clear_tag() {
  tag_ = 0u;
}
inline ::google::protobuf::uint32 Var_Ds_Info::tag() const {
  // @@protoc_insertion_point(field_get:communicate.Var_Ds_Info.tag)
  return tag_;
}
inline void Var_Ds_Info::set_tag(::google::protobuf::uint32 value) {
  
  tag_ = value;
  // @@protoc_insertion_point(field_set:communicate.Var_Ds_Info.tag)
}

// uint32 curr_page = 3;
inline void Var_Ds_Info::clear_curr_page() {
  curr_page_ = 0u;
}
inline ::google::protobuf::uint32 Var_Ds_Info::curr_page() const {
  // @@protoc_insertion_point(field_get:communicate.Var_Ds_Info.curr_page)
  return curr_page_;
}
inline void Var_Ds_Info::set_curr_page(::google::protobuf::uint32 value) {
  
  curr_page_ = value;
  // @@protoc_insertion_point(field_set:communicate.Var_Ds_Info.curr_page)
}

// uint32 tot_pages = 4;
inline void Var_Ds_Info::clear_tot_pages() {
  tot_pages_ = 0u;
}
inline ::google::protobuf::uint32 Var_Ds_Info::tot_pages() const {
  // @@protoc_insertion_point(field_get:communicate.Var_Ds_Info.tot_pages)
  return tot_pages_;
}
inline void Var_Ds_Info::set_tot_pages(::google::protobuf::uint32 value) {
  
  tot_pages_ = value;
  // @@protoc_insertion_point(field_set:communicate.Var_Ds_Info.tot_pages)
}

// uint32 node_id = 5;
inline void Var_Ds_Info::clear_node_id() {
  node_id_ = 0u;
}
inline ::google::protobuf::uint32 Var_Ds_Info::node_id() const {
  // @@protoc_insertion_point(field_get:communicate.Var_Ds_Info.node_id)
  return node_id_;
}
inline void Var_Ds_Info::set_node_id(::google::protobuf::uint32 value) {
  
  node_id_ = value;
  // @@protoc_insertion_point(field_set:communicate.Var_Ds_Info.node_id)
}

// -------------------------------------------------------------------

// Node_state_info

// uint32 tag = 1;
inline void Node_state_info::clear_tag() {
  tag_ = 0u;
}
inline ::google::protobuf::uint32 Node_state_info::tag() const {
  // @@protoc_insertion_point(field_get:communicate.Node_state_info.tag)
  return tag_;
}
inline void Node_state_info::set_tag(::google::protobuf::uint32 value) {
  
  tag_ = value;
  // @@protoc_insertion_point(field_set:communicate.Node_state_info.tag)
}

// uint32 effect = 2;
inline void Node_state_info::clear_effect() {
  effect_ = 0u;
}
inline ::google::protobuf::uint32 Node_state_info::effect() const {
  // @@protoc_insertion_point(field_get:communicate.Node_state_info.effect)
  return effect_;
}
inline void Node_state_info::set_effect(::google::protobuf::uint32 value) {
  
  effect_ = value;
  // @@protoc_insertion_point(field_set:communicate.Node_state_info.effect)
}

// uint32 node_id = 3;
inline void Node_state_info::clear_node_id() {
  node_id_ = 0u;
}
inline ::google::protobuf::uint32 Node_state_info::node_id() const {
  // @@protoc_insertion_point(field_get:communicate.Node_state_info.node_id)
  return node_id_;
}
inline void Node_state_info::set_node_id(::google::protobuf::uint32 value) {
  
  node_id_ = value;
  // @@protoc_insertion_point(field_set:communicate.Node_state_info.node_id)
}

// -------------------------------------------------------------------

// GetInfo

// int32 page_req = 1;
inline void GetInfo::clear_page_req() {
  page_req_ = 0;
}
inline ::google::protobuf::int32 GetInfo::page_req() const {
  // @@protoc_insertion_point(field_get:communicate.GetInfo.page_req)
  return page_req_;
}
inline void GetInfo::set_page_req(::google::protobuf::int32 value) {
  
  page_req_ = value;
  // @@protoc_insertion_point(field_set:communicate.GetInfo.page_req)
}

// repeated int32 pg_rq = 2;
inline int GetInfo::pg_rq_size() const {
  return pg_rq_.size();
}
inline void GetInfo::clear_pg_rq() {
  pg_rq_.Clear();
}
inline ::google::protobuf::int32 GetInfo::pg_rq(int index) const {
  // @@protoc_insertion_point(field_get:communicate.GetInfo.pg_rq)
  return pg_rq_.Get(index);
}
inline void GetInfo::set_pg_rq(int index, ::google::protobuf::int32 value) {
  pg_rq_.Set(index, value);
  // @@protoc_insertion_point(field_set:communicate.GetInfo.pg_rq)
}
inline void GetInfo::add_pg_rq(::google::protobuf::int32 value) {
  pg_rq_.Add(value);
  // @@protoc_insertion_point(field_add:communicate.GetInfo.pg_rq)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
GetInfo::pg_rq() const {
  // @@protoc_insertion_point(field_list:communicate.GetInfo.pg_rq)
  return pg_rq_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
GetInfo::mutable_pg_rq() {
  // @@protoc_insertion_point(field_mutable_list:communicate.GetInfo.pg_rq)
  return &pg_rq_;
}

// uint32 ack = 3;
inline void GetInfo::clear_ack() {
  ack_ = 0u;
}
inline ::google::protobuf::uint32 GetInfo::ack() const {
  // @@protoc_insertion_point(field_get:communicate.GetInfo.ack)
  return ack_;
}
inline void GetInfo::set_ack(::google::protobuf::uint32 value) {
  
  ack_ = value;
  // @@protoc_insertion_point(field_set:communicate.GetInfo.ack)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace communicate

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_communicate_2eproto
