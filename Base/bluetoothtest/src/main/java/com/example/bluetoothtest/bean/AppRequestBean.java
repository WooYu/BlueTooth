package com.example.bluetoothtest.bean;

public class AppRequestBean {
    public static class ChargeControlBean {

        /**
         * chargeContrl : 0
         */

        private int chargeContrl = 0;// 0停止充电，1开启充电

        public int getChargeContrl() {
            return chargeContrl;
        }

        public void setChargeContrl(int chargeContrl) {
            this.chargeContrl = chargeContrl;
        }
    }

    public static class DisChargeControlBean {

        /**
         * disChargeContrl : 0
         */

        private int disChargeContrl = 0;// 0关闭放电，1开启放电

        public int getDisChargeContrl() {
            return disChargeContrl;
        }

        public void setDisChargeContrl(int disChargeContrl) {
            this.disChargeContrl = disChargeContrl;
        }
    }

    public static class WifiPushDataBean {

        /**
         * isOpenPush : 0
         * pushCycle : 1000
         */

        private int isOpenPush = 0;//是否开启推送，0关闭，1开启
        private int pushCycle = 5000;//推送周期单位毫秒，默认5s

        public int getIsOpenPush() {
            return isOpenPush;
        }

        public void setIsOpenPush(int isOpenPush) {
            this.isOpenPush = isOpenPush;
        }

        public int getPushCycle() {
            return pushCycle;
        }

        public void setPushCycle(int pushCycle) {
            this.pushCycle = pushCycle;
        }
    }

    public static class WifiConfigBean {

        /**
         * SSID :
         * password :
         */

        private String SSID;//WiFi名称
        private String password;//密码

        public String getSSID() {
            return SSID;
        }

        public void setSSID(String SSID) {
            this.SSID = SSID;
        }

        public String getPassword() {
            return password;
        }

        public void setPassword(String password) {
            this.password = password;
        }
    }

    public static class QuerySoftwareBean {

    }

    public static class UpdateSoftwareBean {

        /**
         * Server : 0
         * Firmware : 0，
         */

        private int Server = 0;//是否升级，0不升级，1执行升级
        private int Firmware = 0;//是否升级，0不升级，1执行升级

        public int getServer() {
            return Server;
        }

        public void setServer(int Server) {
            this.Server = Server;
        }

        public int getFirmware() {
            return Firmware;
        }

        public void setFirmware(int Firmware) {
            this.Firmware = Firmware;
        }
    }

    public static class QueryControlBean {

    }

    public static class QueryDeviceBean {

    }

    public static class GetDeciceStatusBean {

    }

}
