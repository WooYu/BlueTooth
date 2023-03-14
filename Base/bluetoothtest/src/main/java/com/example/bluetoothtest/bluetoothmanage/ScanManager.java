package com.example.bluetoothtest.bluetoothmanage;

import android.content.Context;
import android.util.Log;

import com.example.bluetoothtest.bean.DeviceModule;
import com.example.bluetoothtest.callback.IDataCallback;
import com.example.bluetoothtest.callback.IScanCallback;
import com.example.bluetoothtest.utli.Analysis;
import com.example.bluetoothtest.utli.ToolClass;
import com.example.bluetoothtest.viewmodel.MessageViewModel;

import java.util.ArrayList;
import java.util.List;


public class ScanManager {
    private enum State {refresh, leisure}//是否处于扫描状态

    private State mState = State.leisure;
    private List<DeviceModule> deviceModules = new ArrayList<>();
    public Context mContext;
    private List<DeviceModule> mClassicBluetoothArray = new ArrayList<>();
    private ClassicBluetoothManage mClassicManage;//2.0蓝牙
    private BleBluetoothManage mBleManage;//ble蓝牙
    private DeviceModule mDeviceModule;
    private MessageViewModel messageViewModel;

    public ScanManager(Context context, MessageViewModel messageViewModel) {
        this.messageViewModel = messageViewModel;
        mClassicManage = new ClassicBluetoothManage(context);
        mBleManage = new BleBluetoothManage(context);
    }

    public void sendStr(String request) {
        if (mDeviceModule != null) {
            sendData(mDeviceModule, Analysis.getBytes(request, false));
        }
    }

    //综合扫描（扫描完成时会检查是否有BLE模块名字乱码，若有则启动BLE扫描，通过解析BLE的广播包来获取名字）
    public boolean mixScan() {
        if (mState == State.refresh) {
            return false;
        }
        mState = State.refresh;
        mClassicBluetoothArray.clear();
        mClassicManage.scanBluetooth(new IScanCallback() {
            @Override
            public void stopScan() {
                //扫描结束
                Log.i("JWW", "classic扫描结束" + mClassicBluetoothArray.size());

//                //检验是否有乱码
                testMessyCode();

                boolean hasConnect = false;
                Log.i("JWW", "stopScan: " + mDeviceModule);
                if (mClassicBluetoothArray.size() > 0) {
                    for (DeviceModule deviceModule : mClassicBluetoothArray) {
                        if (deviceModule.getName().equals("AutelGateway")) {
                            Log.i("JWW", "mixScan: " + deviceModule.isBeenConnected());
                            if (!deviceModule.isBeenConnected()) {
//                        if (deviceModule.getName().equals("HC-08")) {
                                hasConnect = true;
                                connect(deviceModule, new IDataCallback() {
                                    @Override
                                    public void readData(byte[] data, String mac) {
                                        Log.i("JWW", "readData: " + data);
                                        String dataStr = Analysis.getByteToString(data, false/*是否是十六进制*/);
                                        messageViewModel.getReadData().setValue(dataStr);
                                    }

                                    @Override
                                    public void connectionFail(String mac, String cause) {
                                        Log.i("JWW", "connectionFail: " + mac + "  &&：" + cause);
                                    }

                                    @Override
                                    public void connectionSucceed(String mac) {
                                        Log.i("JWW", "connectionSucceed: " + mac);
                                    }

                                    @Override
                                    public void reading(boolean isStart) {
                                        Log.i("JWW", "reading: " + isStart);
                                    }

                                    @Override
                                    public void errorDisconnect(String mac) {
                                        Log.i("JWW", "errorDisconnect: " + mac);
                                    }

                                    @Override
                                    public void readNumber(int number) {
                                        Log.i("JWW", "readNumber: " + number);
                                    }

                                    @Override
                                    public void readLog(String className, String data, String lv) {
                                        Log.i("JWW", "readLog: " + className + "  &&:" + data + " &&：" + lv);
                                    }
                                });
                            }
                            mDeviceModule = deviceModule;
                            break;
                        }
                    }

                    messageViewModel.getConnectStatus().setValue(hasConnect);
                }
            }

            @Override
            public void updateRecycler(DeviceModule deviceModule) {
                //更新Recycler的数据
                mClassicBluetoothArray.add(deviceModule);
//                callbackActivity(deviceModule);
            }
        });
        return true;
    }

    /**
     * 蓝牙扫描
     *
     * @return
     */
    public boolean bleScan() {
        if (mState == State.refresh) {
            return false;
        }
        mState = State.refresh;
        mBleManage.scanBluetooth(new IScanCallback() {
            @Override
            public void stopScan() {
                Log.i("JWW", "ble扫描结束");

                mState = State.leisure;
            }

            @Override
            public void updateRecycler(DeviceModule deviceModule) {
                deviceModules.add(deviceModule);
//                callbackActivity(deviceModule);
                Log.i("JWW", "名字:" + (deviceModule.getName() != null ? deviceModule.getName() : "没有名字") + " Mac: " + deviceModule.getMac() + " isBLE: " + deviceModule.isBLE());
            }
        });

        return true;
    }


    //测试是否蓝牙名称有乱码
    private void testMessyCode() {
        final List<DeviceModule> list = getMessyCodeArray();
        mBleManage.scanBluetooth(list, true, new IScanCallback() {
            @Override
            public void stopScan() {
                Log.i("JWW", "=====解码=====");
                for (DeviceModule deviceModule : list) {
                    Log.i("JWW", "name: " + deviceModule.getName());
                }
                mState = State.leisure;
            }

            @Override
            public void updateRecycler(DeviceModule deviceModule) {

            }
        });
    }

    private List<DeviceModule> getMessyCodeArray() {
        List<DeviceModule> list = new ArrayList<>();
        for (DeviceModule deviceModule : mClassicBluetoothArray) {
            if (deviceModule.isBLE() && ToolClass.pattern(deviceModule.getName())) {
                list.add(deviceModule);
            }
        }
        return list;
    }

    //发送数据
    public void sendData(DeviceModule deviceModule, byte[] data) {
        if (deviceModule.isBLE()) {
            mBleManage.sendData(data);
        } else {
            mClassicManage.sendData(data);
        }
    }

    //连接蓝牙
    public void connect(final DeviceModule deviceModule, IDataCallback mIDataCallback) {

        if (deviceModule.isBLE()) {
            Log.i("JWW", "进入ble的连接方式");
            if (mBleManage.getMac() == null) {
                mBleManage.connectBluetooth(deviceModule, mIDataCallback);
            }
        } else {
            if (mClassicManage.getMac() == null)
                mClassicManage.connectBluetooth(deviceModule.getMac(), mIDataCallback);
        }
    }

    //断开蓝牙
    public void disconnect() {
        if (mDeviceModule != null) {
            if (mDeviceModule.isBLE()) {
                mBleManage.disConnectBluetooth();
            } else {
                mClassicManage.disconnectBluetooth();
            }
        }
    }
}
