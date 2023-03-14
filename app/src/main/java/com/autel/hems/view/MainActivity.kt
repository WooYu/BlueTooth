package com.autel.hems.view

import android.Manifest
import android.content.pm.PackageManager
import android.text.TextUtils
import androidx.lifecycle.lifecycleScope
import com.autel.core.domain.base.view.BaseActivity
import com.autel.hems.R
import com.autel.hems.databinding.ActivityMainBinding
import com.autel.hems.model.MainModel
import com.autel.hems.viewmodel.MainViewModel
import com.autel.utils.screen.NavigationBarUtil
import kotlinx.coroutines.launch

class MainActivity : BaseActivity<ActivityMainBinding, MainModel, MainViewModel>() {
    var arouteState = false

    override fun getPageTag() = "HistoryTestFragment"

    override fun initStyleConfig() {
//        setTheme(com.autel.utils.theme.R.style.AppTheme)
    }

    override fun initStateObserver() {
        //showWhiteLoading(com.autel.utils.theme.R.string.logining_check)
//        showWhiteLoading(com.autel.utils.theme.R.string.safety_checking)
    }

    override fun initViewListener() {
        lifecycleScope.launch {
            checkPermissions(
                arrayOf(
                    Manifest.permission.READ_EXTERNAL_STORAGE,
                    Manifest.permission.WRITE_EXTERNAL_STORAGE,
                    Manifest.permission.INTERNET,
                    Manifest.permission.ACCESS_COARSE_LOCATION,
                    Manifest.permission.ACCESS_FINE_LOCATION
                ), 200
            )
        }

        mViewBinding.btnStartSys.setOnClickListener{
            dispatcherEvent(StartSystemBtnEvent())
        }
        mViewBinding.btnStopSys.setOnClickListener{
            dispatcherEvent(StopSystemBtnEvent())
        }
        mViewBinding.btnStartCharge.setOnClickListener{
            dispatcherEvent(StartChargeBtnEvent())
        }
        mViewBinding.btnStopCharge.setOnClickListener{
            dispatcherEvent(StopChargeBtnEvent())
        }
        mViewBinding.btnStartDisCharge.setOnClickListener{
            dispatcherEvent(StartDisChargeBtnEvent())
        }
        mViewBinding.btnStopDisCharge.setOnClickListener{
            dispatcherEvent(StopDisChargeBtnEvent())
        }
        mViewBinding.btnGetLibV.setOnClickListener{
            dispatcherEvent(QueryLibVersion())
        }

        mViewBinding.btnStartOnNet.setOnClickListener{
            dispatcherEvent(StartOnPowerGrid())
        }

        mViewBinding.btnStartOffNet.setOnClickListener{
            dispatcherEvent(StartOffPowerGrid())
        }
    }

    override fun handUiRefresh(state: Any) {}

    override fun handStickUiRefresh(state: Any) {
        if(state is String && !TextUtils.isEmpty(state)) {
            mViewBinding.tvSystemStatus.text = state
        }
    }


    override fun onPermissionRequestResult(requestCode: Int, permissionStatus: Int) {
        super.onPermissionRequestResult(requestCode, permissionStatus)
        if(PackageManager.PERMISSION_DENIED == permissionStatus){

        }else if(PackageManager.PERMISSION_GRANTED == permissionStatus){
            //FloatMessagerMainWindow.getFloatMessagerMainWindow(this)
        }
    }

    override fun IdleHandlerTask() {

    }

    override fun languageChange(languageTag: Any?){}


}