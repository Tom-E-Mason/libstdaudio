// libstdaudio
// Copyright (c) 2018 - Timur Doumler

#pragma once
#include <vector>
#include "config.h"
#include "buffer.h"

LIBSTDAUDIO_NAMESPACE_BEGIN

/** A container holding a number of audio buffers for input and output, respectively. */
class buffer_list {
public:
  using size_type = size_t;

  /** Constructs an empty buffer list. */
  buffer_list();

  /** Constructs a buffer list with the specified number of buffers.
   *
   *  \param num_input_buffers The number of input buffers to hold.
   *  \param num_output_buffers The number of output buffers to hold.
   */
  buffer_list(size_type num_input_buffers, size_type num_output_buffers);

  /** Resizes the buffer list to contain the specified number of buffers.
   *
   *  \param num_input_buffers The number of input buffers to hold.
   *  \param num_output_buffers The number of output buffers to hold.
   */
  void resize(size_type num_input_buffers, size_type num_output_buffers);

  /** Returns a view of the input buffers.
   *  Note: this function is guaranteed to not allocate memory.
   */
  span<buffer> input_buffers();

  /** Returns a view of the output buffers.
   *  Note: this function is guaranteed to not allocate memory.
   */
  span<buffer> output_buffers();

  /** Returns the current number of input buffers the buffer list can hold without
   *  having to allocate memory.
   *  Note: this function is guaranteed to not allocate memory.
   */
  size_t input_buffer_capacity() const noexcept;

  /** Returns the current number of output buffers the buffer list can hold without
   *  having to allocate memory.
   *  Note: this function is guaranteed to not allocate memory.
   */
  size_t output_buffer_capacity() const noexcept;

  // TODO: it looks like we would have to duplicate the whole interface of vector here,
  // as buffer_list is essentially just two std::vectors ... Change the design!

private:
  vector<buffer> _input_buffers;
  vector<buffer> _output_buffers;

  // Maximum number of input and output buffers, respectively, that the buffer_list
  // is always guaranteed to be able to hold without reallocating.
  static constexpr size_t _safe_num_buffers = 10;
  void _preallocate_safe_num_buffers();
};

LIBSTDAUDIO_NAMESPACE_END