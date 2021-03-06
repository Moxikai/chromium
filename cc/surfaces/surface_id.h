// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_SURFACES_SURFACE_ID_H_
#define CC_SURFACES_SURFACE_ID_H_

#include <stddef.h>
#include <stdint.h>

#include <functional>

#include "base/format_macros.h"
#include "base/hash.h"
#include "base/strings/stringprintf.h"

namespace cc {

class SurfaceId {
 public:
  SurfaceId() : id_namespace_(0), local_id_(0), nonce_(0) {}

  SurfaceId(const SurfaceId& other)
      : id_namespace_(other.id_namespace_),
        local_id_(other.local_id_),
        nonce_(other.nonce_) {}

  // A SurfaceId consists of three components: namespace, local Id, and nonce.
  // An |id_namespace| is a display compositor service allocated ID that
  // uniquely identifies a client.
  // A |local_id| is a sequentially allocated ID generated by the display
  // compositor client.
  // A |nonce| is a cryptographically secure random int that makes a SurfaceId
  // unguessable by other clients.
  SurfaceId(uint32_t id_namespace, uint32_t local_id, uint64_t nonce)
      : id_namespace_(id_namespace), local_id_(local_id), nonce_(nonce) {}

  bool is_null() const {
    return id_namespace_ == 0 && nonce_ == 0 && local_id_ == 0;
  }

  size_t hash() const {
    size_t interim = base::HashInts(id_namespace_, local_id_);
    return base::HashInts(static_cast<uint64_t>(interim), nonce_);
  }

  uint32_t id_namespace() const { return id_namespace_; }

  uint32_t local_id() const { return local_id_; }

  uint64_t nonce() const { return nonce_; }

  std::string ToString() const {
    return base::StringPrintf("%d:%d:%" PRIu64, id_namespace_, local_id_,
                              nonce_);
  }

  bool operator==(const SurfaceId& other) const {
    return id_namespace_ == other.id_namespace_ &&
           local_id_ == other.local_id_ && nonce_ == other.nonce_;
  }

  bool operator!=(const SurfaceId& other) const { return !(*this == other); }

  bool operator<(const SurfaceId& other) const {
    return std::tie(id_namespace_, local_id_, nonce_) <
           std::tie(other.id_namespace_, other.local_id_, other.nonce_);
  }

 private:
  // See SurfaceIdAllocator::GenerateId.
  uint32_t id_namespace_;
  uint32_t local_id_;
  uint64_t nonce_;
};

struct SurfaceIdHash {
  size_t operator()(const SurfaceId& key) const { return key.hash(); }
};

}  // namespace cc

#endif  // CC_SURFACES_SURFACE_ID_H_
