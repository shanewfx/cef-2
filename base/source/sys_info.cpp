// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "sys_info.h"

#include "base_switches.h"
#include "command_line.h"
#include "lazy_instance.h"
#include "string_number_conversions.h"
#include "sys_info_internal.h"
#include "time_cef.h"

namespace base {

#if !defined(OS_ANDROID)

	static const int kLowMemoryDeviceThresholdMB = 512;

	bool DetectLowEndDevice() {
		CommandLine* command_line = CommandLine::ForCurrentProcess();
		int int_value = 0;
		if (command_line->HasSwitch(switches::kLowEndDeviceMode)) {
			std::string string_value =
				command_line->GetSwitchValueASCII(switches::kLowEndDeviceMode);
			StringToInt(string_value, &int_value);
		}
		if (int_value == 1)
			return true;
		if (int_value != 2)
			return false;

		int ram_size_mb = SysInfo::AmountOfPhysicalMemoryMB();
		return (ram_size_mb > 0 && ram_size_mb < kLowMemoryDeviceThresholdMB);
	}

	static LazyInstance<
		internal::LazySysInfoValue<bool, DetectLowEndDevice> >::Leaky
		g_lazy_low_end_device = LAZY_INSTANCE_INITIALIZER;

	// static
	bool SysInfo::IsLowEndDevice() {
		return g_lazy_low_end_device.Get().value();
	}
#endif

	// static
	int64 SysInfo::Uptime() {
		// This code relies on an implementation detail of TimeTicks::Now() - that
		// its return value happens to coincide with the system uptime value in
		// microseconds, on Win/Mac/iOS/Linux/ChromeOS and Android.
		int64 uptime_in_microseconds = TimeTicks::Now().ToInternalValue();
		return uptime_in_microseconds / 1000;
	}

}  // namespace base
