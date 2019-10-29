// Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rmw/topic_info_array.h"

#include "rcutils/logging_macros.h"
#include "rmw/error_handling.h"
#include "rmw/convert_rcutils_ret_to_rmw_ret.h"
#include "rmw/types.h"

rmw_topic_info_array_t
rmw_get_zero_initialized_topic_info_array(void)
{
  rmw_topic_info_array_t zero = {0};
  return zero;
}

rmw_ret_t
rmw_topic_info_array_check_zero(rmw_topic_info_array_t * topic_info_array)
{
  if (!topic_info_array) {
    RMW_SET_ERROR_MSG("topic_info_array is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (topic_info_array->count != 0 || topic_info_array->info_array != NULL) {
    RMW_SET_ERROR_MSG("topic_info_array is not zeroed");
    return RMW_RET_INVALID_ARGUMENT;
  }
  return RMW_RET_OK;
}

rmw_ret_t
rmw_topic_info_array_init_with_size(
  rcutils_allocator_t * allocator,
  size_t size,
  rmw_topic_info_array_t * topic_info_array)
{
  if (!allocator) {
    RMW_SET_ERROR_MSG("allocator is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!topic_info_array) {
    RMW_SET_ERROR_MSG("topic_info_array is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  topic_info_array->info_array = allocator->allocate(sizeof(*topic_info_array->info_array) * size,
      allocator->state);
  if (!topic_info_array->info_array) {
    RMW_SET_ERROR_MSG("failed to allocate memory for info_array");
    return RMW_RET_BAD_ALLOC;
  }
  return RMW_RET_OK;
}

rmw_ret_t
rmw_topic_info_array_fini(
  rcutils_allocator_t * allocator,
  rmw_topic_info_array_t * topic_info_array)
{
  if (!allocator) {
    RMW_SET_ERROR_MSG("allocator is null");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!topic_info_array) {
    RMW_SET_ERROR_MSG("topic_info_array is null");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (!topic_info_array->info_array) {
    RMW_SET_ERROR_MSG("invalid topic_info_array");
    return RMW_RET_INVALID_ARGUMENT;
  }
  allocator->deallocate(topic_info_array->info_array, allocator->state);
  topic_info_array->info_array = NULL;
  topic_info_array->count = 0;
  return RMW_RET_OK;
}