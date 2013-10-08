// Copyright (c) 2013 Google Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "media/mp4/decoding_time_iterator.h"

#include <algorithm>

#include "base/logging.h"

namespace media {
namespace mp4 {

DecodingTimeIterator::DecodingTimeIterator(
    const DecodingTimeToSample& decoding_time_to_sample)
    : sample_index_(0),
      decoding_time_table_(decoding_time_to_sample.decoding_time),
      iterator_(decoding_time_table_.begin()) {
}

bool DecodingTimeIterator::AdvanceSample() {
  ++sample_index_;
  if (sample_index_ >= iterator_->sample_count) {
    ++iterator_;
    if (iterator_ == decoding_time_table_.end())
      return false;
    sample_index_ = 0;
  }
  return true;
}

bool DecodingTimeIterator::IsValid() {
  return iterator_ != decoding_time_table_.end()
      && sample_index_ < iterator_->sample_count;
}

uint64 DecodingTimeIterator::Duration(uint32 start_sample, uint32 end_sample) {
  DCHECK(start_sample <= end_sample);
  uint32 current_sample = 0;
  uint32 prev_sample = 0;
  uint64 duration = 0;
  std::vector<DecodingTime>::const_iterator it = decoding_time_table_.begin();
  for (; it != decoding_time_table_.end(); ++it) {
    current_sample += it->sample_count;
    if (current_sample >= start_sample) {
      duration += (std::min(end_sample, current_sample)
          - std::max(start_sample, prev_sample + 1) + 1) * it->sample_delta;
      if (current_sample >= end_sample)
        break;
    }
    prev_sample = current_sample;
  }
  return duration;
}

uint32 DecodingTimeIterator::NumSamples() {
  uint32 num_samples = 0;
  std::vector<DecodingTime>::const_iterator it = decoding_time_table_.begin();
  for (; it != decoding_time_table_.end(); ++it) {
    num_samples += it->sample_count;
  }
  return num_samples;
}

}  // namespace mp4
}  // namespace media
