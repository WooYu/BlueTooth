package com.example.bluetoothtest.callback;

import com.example.bluetoothtest.bean.DeviceModule;

public interface IScanCallback {
    void stopScan();
    void updateRecycler(DeviceModule deviceModule);
}
