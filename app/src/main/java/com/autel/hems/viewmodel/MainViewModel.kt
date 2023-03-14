package com.autel.hems.viewmodel

import androidx.lifecycle.viewModelScope
import com.autel.busiservices.hems.HemsSystemService
import com.autel.core.domain.base.viewmodel.BaseViewModel
import com.autel.core.libcom.hems.jni.HemsSystemJni
import com.autel.hems.model.MainModel
import com.autel.hems.view.*
import com.autel.utils.log.logger
import kotlinx.coroutines.launch

class MainViewModel: BaseViewModel<MainModel>() {

    init {
        logger.d("--MainViewModel init--")
        viewModelScope.launch {
            HemsSystemJni.dataReportFlow.collect{
                logger.d("--MainViewModel collect--data--${it}")
                if(it is String){
                    notifyStickUIState("收到中间层消息：$it")
                    return@collect
                }
            }
        }

    }

    override suspend fun dispatcherEvent(event: Any) {
        super.dispatcherEvent(event)
        when(event){
            is StartSystemBtnEvent-> HemsSystemService.startHemsSystemService()
            is StopSystemBtnEvent-> HemsSystemService.stopHemsSystemService()
            is StartChargeBtnEvent-> HemsSystemJni.startV2XCharging()
            is StartDisChargeBtnEvent -> HemsSystemJni.startV2XDisCharging()
            is StopChargeBtnEvent-> HemsSystemJni.stopV2xCharging()
            is StopDisChargeBtnEvent-> HemsSystemJni.stopV2xDisCharging()
            is QueryLibVersion -> {
                val version = HemsSystemJni.getHemsLibVersion()
                notifyStickUIState("Hems系统库版本号：$version")
            }
            is StartOnPowerGrid -> HemsSystemJni.startHemsOnPowerGrid()
            is StartOffPowerGrid -> HemsSystemJni.startHemsOffPowerGrid()
        }
    }


}