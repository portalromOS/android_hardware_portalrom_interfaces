/*
 * Copyright (C) 2022 The Portal Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <android-base/macros.h>
#include <vendor/qti/hardware/cryptfshw/1.0/ICryptfsHw.h>

#include <memory>

#include "ICryptfsHwController.h"

namespace vendor {
namespace qti {
namespace hardware {
namespace cryptfshw {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_string;
using ::android::hardware::Return;

class CryptfsHw : public ICryptfsHw {
  public:
    CryptfsHw(std::unique_ptr<ICryptfsHwController> controller);

    // Methods from ::vendor::qti::hardware::cryptfshw::V1_0::ICryptfsHw follow.
    Return<int32_t> setIceParam(uint32_t flag) override;
    Return<int32_t> setKey(const hidl_string& passwd, const hidl_string& enc_mode) override;
    Return<int32_t> updateKey(const hidl_string& oldpw, const hidl_string& newpw,
                              const hidl_string& enc_mode) override;
    Return<int32_t> clearKey() override;

  private:
    std::unique_ptr<ICryptfsHwController> controller_;
    int usage_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(CryptfsHw);
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace cryptfshw
}  // namespace hardware
}  // namespace qti
}  // namespace vendor
