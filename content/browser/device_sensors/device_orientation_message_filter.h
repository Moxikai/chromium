// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DEVICE_SENSORS_DEVICE_ORIENTATION_MESSAGE_FILTER_H_
#define CONTENT_BROWSER_DEVICE_SENSORS_DEVICE_ORIENTATION_MESSAGE_FILTER_H_

#include "content/browser/device_sensors/device_sensor_message_filter.h"

namespace content {

class DeviceOrientationMessageFilter : public DeviceSensorMessageFilter {
 public:
  DeviceOrientationMessageFilter();

  // BrowserMessageFilter implementation.
  bool OnMessageReceived(const IPC::Message& message) override;

 private:
  ~DeviceOrientationMessageFilter() override;

  // DeviceSensorMessageFilter implementation.
  void DidStartPolling(base::SharedMemoryHandle handle) override;

  DISALLOW_COPY_AND_ASSIGN(DeviceOrientationMessageFilter);
};

}  // namespace content

#endif  // CONTENT_BROWSER_DEVICE_SENSORS_DEVICE_ORIENTATION_MESSAGE_FILTER_H_
