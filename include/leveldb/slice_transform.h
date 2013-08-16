// Copyright (c) 2012 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// Class for specifying user-defined functions which perform a
// transformation on a slice.  It is not required that every slice
// belong to the domain and/or range of a function.  Subclasses should
// define InDomain and InRange to determine which slices are in either
// of these sets respectively.

#ifndef STORAGE_LEVELDB_INCLUDE_SLICE_TRANSFORM_H_
#define STORAGE_LEVELDB_INCLUDE_SLICE_TRANSFORM_H_

#include <string>

namespace leveldb {

class Slice;

class SliceTransform {
 public:
  virtual ~SliceTransform() {};

  // Return the name of this transformation.
  virtual const char* Name() const = 0;

  // transform a src in domain to a dst in the range
  virtual Slice Transform(const Slice& src) const = 0;

  // determine whether this is a valid src upon the function applies
  virtual bool InDomain(const Slice& src) const = 0;

  // determine whether dst=Transform(src) for some src
  virtual bool InRange(const Slice& dst) const = 0;
};

extern const SliceTransform* NewFixedPrefixTransform(size_t prefix_len);

}

#endif  // STORAGE_LEVELDB_INCLUDE_SLICE_TRANSFORM_H_