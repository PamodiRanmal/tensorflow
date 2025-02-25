/* Copyright 2022 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include <cstdlib>
#include <memory>
#include <utility>

#include "tensorflow/lite/c/c_api_types.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/core/shims/c/experimental/acceleration/configuration/delegate_plugin.h"
#include "tensorflow/lite/delegates/utils/experimental/sample_stable_delegate/sample_stable_delegate.h"
#include "tensorflow/lite/delegates/utils/simple_opaque_delegate.h"
#include "tensorflow/lite/experimental/acceleration/configuration/c/stable_delegate.h"

namespace {

TfLiteDelegate* SampleStableDelegateCreateFunc(const void* tflite_settings) {
  auto delegate = std::make_unique<tflite::example::SampleStableDelegate>();
  return reinterpret_cast<TfLiteDelegate*>(
      tflite::TfLiteOpaqueDelegateFactory::CreateSimpleDelegate(
          std::move(delegate)));
}

void SampleStableDelegateDestroyFunc(TfLiteDelegate* sample_stable_delegate) {
  tflite::TfLiteOpaqueDelegateFactory::DeleteSimpleDelegate(
      reinterpret_cast<TfLiteOpaqueDelegateStruct*>(sample_stable_delegate));
}

int SampleStableDelegateErrnoFunc(TfLiteDelegate* sample_stable_delegate) {
  // no-op
  return 0;
}

const TfLiteOpaqueDelegatePlugin sample_stable_delegate_plugin = {
    SampleStableDelegateCreateFunc, SampleStableDelegateDestroyFunc,
    SampleStableDelegateErrnoFunc};

}  // namespace

/**
 * A super simple test delegate for testing.
 */
extern "C" const TfLiteStableDelegate TFL_TheStableDelegate = {
    TFL_STABLE_DELEGATE_ABI_VERSION, tflite::example::kSampleStableDelegateName,
    /*delegate_version=*/"1.0.0", &sample_stable_delegate_plugin};
