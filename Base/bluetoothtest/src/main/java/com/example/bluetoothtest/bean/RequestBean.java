package com.example.bluetoothtest.bean;

public class RequestBean {
    public static final int CHARGE_CONTROL = 0x100;//请求开启充电或停止充电
    public static final int DIS_CHARGE_CONTROL = 0x101;//请求允许开启放电或关闭放电配置
    public static final int WIFI_PUSH_DATA_CONFIG = 0x201;//1、配置网关是否主动推送设备实时状态数据，默认开启 2、设置推送周期，默认每隔5s推送
    public static final int WIFI_CONFIG = 0x200;//请求配置网关WiFi名称和密码
    public static final int QUERY_SOFTWARE_VERSION = 0x300;//请求查询是否有家庭网关服务软件和下位机固件更新
    public static final int UPDATE_SOFTWARE = 0x301;//控制家庭网关更新软件
    public static final int QUERY_CONTROL_PARGRAM = 0x400;//请求查询网关当前的控制参数设置
    public static final int QUERY_DEVICE_SATATUS = 0x500;//请求查询设备状态
    public static final int GET_DEVICE_SATATUS = 0x501;//家庭网关自动推送设备状态信息

    /**
     * requestCode : 0x00
     * requestParams : {}
     */

    private int requestCode;
    private Object requestParams ;

    public int getRequestCode() {
        return requestCode;
    }

    public void setRequestCode(int requestCode) {
        this.requestCode = requestCode;
    }

    public Object getRequestParams() {
        return requestParams;
    }

    public void setRequestParams(Object requestParams) {
        this.requestParams = requestParams;
    }
}
