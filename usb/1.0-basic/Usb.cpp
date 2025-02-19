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
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <android-base/logging.h>
#include <utils/Errors.h>
#include <utils/StrongPointer.h>

#include "Usb.h"

namespace android {
namespace hardware {
namespace usb {
namespace V1_0 {
namespace implementation {

Return<void> Usb::switchRole(const hidl_string &portName __unused,
                             const PortRole &newRole __unused) {
    LOG(ERROR) << __func__ << ": Not supported";
    return Void();
}

Return<void> Usb::queryPortStatus() {
    hidl_vec<PortStatus> currentPortStatus;
    currentPortStatus.resize(1);

    currentPortStatus[0].portName = "otg_default";
    currentPortStatus[0].currentDataRole = PortDataRole::DEVICE;
    currentPortStatus[0].currentPowerRole = PortPowerRole::SINK;
    currentPortStatus[0].currentMode = PortMode::UFP;
    currentPortStatus[0].canChangeMode = false;
    currentPortStatus[0].canChangeDataRole = false;
    currentPortStatus[0].canChangePowerRole = false;
    currentPortStatus[0].supportedModes = PortMode::UFP;

    pthread_mutex_lock(&mLock);
    if (mCallback != NULL) {
        Return<void> ret =
                mCallback->notifyPortStatusChange(currentPortStatus, Status::SUCCESS);
        if (!ret.isOk()) {
            LOG(ERROR) << "queryPortStatus error " << ret.description();
        }
    } else {
        LOG(INFO) << "Notifying userspace skipped. Callback is NULL";
    }
    pthread_mutex_unlock(&mLock);

    return Void();
}

Return<void> Usb::setCallback(const sp<IUsbCallback> &callback) {
    pthread_mutex_lock(&mLock);

    mCallback = callback;
    LOG(INFO) << "registering callback";

    pthread_mutex_unlock(&mLock);
    return Void();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace usb
}  // namespace hardware
}  // namespace android
