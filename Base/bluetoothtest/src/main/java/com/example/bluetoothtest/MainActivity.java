package com.example.bluetoothtest;


import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import com.example.bluetoothtest.bean.AppRequestBean;
import com.example.bluetoothtest.bean.RequestBean;
import com.example.bluetoothtest.bluetoothmanage.ScanManager;
import com.example.bluetoothtest.viewmodel.MessageViewModel;
import com.google.gson.Gson;

public class MainActivity extends AppCompatActivity {
    private ScanManager scanManager;
    private MessageViewModel messageViewModel;
    private boolean hasConnect = false;
    private RelativeLayout progress_bar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        messageViewModel = ViewModelProviders.of(this).get(MessageViewModel.class);
        scanManager = new ScanManager(MainActivity.this, messageViewModel);
        EditText wifi_name = (EditText) findViewById(R.id.wifi_name);
        EditText wifi_password = (EditText) findViewById(R.id.wifi_password);
        EditText push_tx = (EditText) findViewById(R.id.push_tx);
        TextView response_text = (TextView) findViewById(R.id.response_text);
        progress_bar = (RelativeLayout) findViewById(R.id.progress_bar);

        scanManager.mixScan();
        RequestBean requestBean = new RequestBean();
        Gson gson = new Gson();

        Button charge = (Button) findViewById(R.id.charge);
        AppRequestBean.ChargeControlBean chargeControlBean = new AppRequestBean.ChargeControlBean();
        charge.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!hasConnect){
                    Toast.makeText(MainActivity.this,"蓝牙未连接",Toast.LENGTH_SHORT).show();
                    return;
                }
                chargeControlBean.setChargeContrl(chargeControlBean.getChargeContrl() == 0 ? 1:0);
                requestBean.setRequestCode(RequestBean.CHARGE_CONTROL);
                requestBean.setRequestParams((chargeControlBean));
                scanManager.sendStr(gson.toJson(requestBean));
                charge.setText(chargeControlBean.getChargeContrl() == 0 ? "开始充电":"停止充电");
            }
        });

        Button discharge = (Button) findViewById(R.id.discharge);
        AppRequestBean.DisChargeControlBean disChargeControlBean = new AppRequestBean.DisChargeControlBean();
        discharge.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!hasConnect){
                    Toast.makeText(MainActivity.this,"蓝牙未连接",Toast.LENGTH_SHORT).show();
                    return;
                }
                disChargeControlBean.setDisChargeContrl(disChargeControlBean.getDisChargeContrl() == 0 ? 1:0);
                requestBean.setRequestCode(RequestBean.DIS_CHARGE_CONTROL);
                requestBean.setRequestParams((disChargeControlBean));
                scanManager.sendStr(gson.toJson(requestBean));
                discharge.setText(disChargeControlBean.getDisChargeContrl() == 0 ? "开始放电":"关闭放电");
            }
        });

        Button setwifi = (Button) findViewById(R.id.setwifi);
        AppRequestBean.WifiConfigBean wifiConfigBean = new AppRequestBean.WifiConfigBean();
        setwifi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!hasConnect){
                    Toast.makeText(MainActivity.this,"蓝牙未连接",Toast.LENGTH_SHORT).show();
                    return;
                }
                if(TextUtils.isEmpty(wifi_password.getText().toString())){
                    wifi_password.requestFocus();
                }else{
                    wifiConfigBean.setPassword(wifi_password.getText().toString());
                }

                if(TextUtils.isEmpty(wifi_name.getText().toString())){
                    wifi_name.requestFocus();
                }else{
                    wifiConfigBean.setSSID(wifi_name.getText().toString());
                }
                requestBean.setRequestCode(RequestBean.WIFI_CONFIG);
                requestBean.setRequestParams((wifiConfigBean));
                scanManager.sendStr(gson.toJson(requestBean));
            }
        });

        Button setpush = (Button) findViewById(R.id.setpush);
        AppRequestBean.WifiPushDataBean pushDataBean = new AppRequestBean.WifiPushDataBean();
        setpush.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!hasConnect){
                    Toast.makeText(MainActivity.this,"蓝牙未连接",Toast.LENGTH_SHORT).show();
                    return;
                }
                pushDataBean.setIsOpenPush(pushDataBean.getIsOpenPush() == 0 ? 1:0);
                pushDataBean.setPushCycle(Integer.valueOf(push_tx.getText().toString()));
                requestBean.setRequestCode(RequestBean.WIFI_PUSH_DATA_CONFIG);
                requestBean.setRequestParams((pushDataBean));
                scanManager.sendStr(gson.toJson(requestBean));
                setpush.setText(pushDataBean.getIsOpenPush() == 0 ? "开启推送":"关闭推送");
            }
        });

        Button software_version = (Button) findViewById(R.id.software_version);
        software_version.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!hasConnect){
                    Toast.makeText(MainActivity.this,"蓝牙未连接",Toast.LENGTH_SHORT).show();
                    return;
                }
                requestBean.setRequestCode(RequestBean.QUERY_SOFTWARE_VERSION);
                requestBean.setRequestParams("");
                scanManager.sendStr(gson.toJson(requestBean));
            }
        });

        Button software_setting = (Button) findViewById(R.id.software_setting);
        AppRequestBean.UpdateSoftwareBean updateSoftwareBean = new AppRequestBean.UpdateSoftwareBean();
        Button server_update = (Button) findViewById(R.id.server_update);
        server_update.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updateSoftwareBean.setServer(updateSoftwareBean.getServer() == 0 ? 1:0);
                server_update.setText(updateSoftwareBean.getServer() == 0 ? "执行服务升级":"不执行服务升级");
            }
        });
        Button firmware_update = (Button) findViewById(R.id.firmware_update);
        firmware_update.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                updateSoftwareBean.setFirmware(updateSoftwareBean.getFirmware() == 0 ? 1:0);
                firmware_update.setText(updateSoftwareBean.getFirmware() == 0 ? "执行固件升级":"不执行固件升级");
            }
        });
        software_setting.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!hasConnect){
                    Toast.makeText(MainActivity.this,"蓝牙未连接",Toast.LENGTH_SHORT).show();
                    return;
                }
                requestBean.setRequestCode(RequestBean.UPDATE_SOFTWARE);
                requestBean.setRequestParams((updateSoftwareBean));
                scanManager.sendStr(gson.toJson(requestBean));
            }
        });

        Button query_wifi = (Button) findViewById(R.id.query_wifi);
        query_wifi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!hasConnect){
                    Toast.makeText(MainActivity.this,"蓝牙未连接",Toast.LENGTH_SHORT).show();
                    return;
                }
                requestBean.setRequestCode(RequestBean.QUERY_CONTROL_PARGRAM);
                requestBean.setRequestParams("");
                scanManager.sendStr(gson.toJson(requestBean));
            }
        });
        Button query_device = (Button) findViewById(R.id.query_device);
        query_device.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!hasConnect){
                    Toast.makeText(MainActivity.this,"蓝牙未连接",Toast.LENGTH_SHORT).show();
                    return;
                }
                requestBean.setRequestCode(RequestBean.QUERY_DEVICE_SATATUS);
                requestBean.setRequestParams("");
                scanManager.sendStr(gson.toJson(requestBean));
            }
        });


        messageViewModel.getConnectStatus().observe(this, new Observer<Boolean>() {
            @Override
            public void onChanged(Boolean aBoolean) {
                hasConnect = aBoolean;
                progress_bar.setVisibility(View.GONE);
                Toast.makeText(MainActivity.this, aBoolean ? "连接成功" : "连接失败", Toast.LENGTH_SHORT).show();
            }
        });

        messageViewModel.getReadData().observe(this, new Observer<String>() {
            @Override
            public void onChanged(String s) {
                response_text.setText(s);
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.i("JWW", "onStop: ");
        if(scanManager!=null){
            scanManager.disconnect();
        }
    }
}