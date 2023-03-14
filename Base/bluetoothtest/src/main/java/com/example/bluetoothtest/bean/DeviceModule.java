package com.example.bluetoothtest.bean;


import android.bluetooth.BluetoothDevice;
import android.bluetooth.le.ScanResult;
import android.content.Context;
import android.os.Build;
import android.util.Log;

public class DeviceModule {

    private String mName;
    private BluetoothDevice mDevice;
    private boolean isBLE = false;
    private int mRssi = 10;
    private boolean mBeenConnected;
    private ScanResult result;
    private boolean isCollect = false;//是否被收藏

    private String mServiceUUID,mReadUUID,mSendUUID;



    public DeviceModule(BluetoothDevice device, int rssi, String name, Context context, ScanResult result){
        this(name,device,false,context);
        this.mRssi = rssi;
        this.result = result;
    }

    public DeviceModule(String name, BluetoothDevice device){
        this(name,device,false,null);
    }

    public DeviceModule(String name, BluetoothDevice device, boolean beenConnected, Context context){

        this.mName = name;
        this.mDevice = device;
        this.mBeenConnected = beenConnected;

        if (device == null)
            return;

        switch (device.getType()){
            case BluetoothDevice.DEVICE_TYPE_CLASSIC :
            case BluetoothDevice.DEVICE_TYPE_DUAL:
               isBLE = false;
                break;
            case BluetoothDevice.DEVICE_TYPE_LE:
                isBLE = true;
                break;
        }

    }

    public String getName(){
        if (mName != null) {
            return mName;
        }else if (mDevice.getName() != null) {
            mName = mDevice.getName();
        }else {
            mName = "N/A";
        }
        return mName;
    }

    public String getOriginalName(Context context){
        mName = getDevice().getName();
        if (mName == null)
            mName = "N/A";
        return mName;
    }

    public BluetoothDevice getDevice() {
        return mDevice;
    }

    public String getMac(){
        if (mDevice != null){
            return mDevice.getAddress();
        }
        return "出错了";
    }


    public void setUUID(String service,String read,String send){
        if (service != null)
            this.mServiceUUID = service;
        if (read != null)
            this.mReadUUID = read;
        if (send != null)
            this.mSendUUID = send;
    }




    public int getRssi() {
        return mRssi;
    }

    public boolean isBLE() {
        return isBLE;
    }

    public boolean isBeenConnected() {
        return mBeenConnected;
    }

    public boolean isCollect() {
        return isCollect;
    }

    public String getSendUUID() {
        if (mSendUUID != null)
            return mSendUUID;
        else
            return "没有发送特征";
    }

    public String getReadUUID() {
        if (mReadUUID != null)
            return mReadUUID;
        else
            return "没有读取特征";
    }

    public String getServiceUUID() {
        if(mServiceUUID != null)
            return mServiceUUID;
        else
            return "没有服务UUID";
    }
}
