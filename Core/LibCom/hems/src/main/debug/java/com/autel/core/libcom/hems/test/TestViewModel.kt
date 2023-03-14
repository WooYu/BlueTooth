package com.autel.core.libcom.hems.test

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.autel.core.libcom.hems.DeviceComService
import com.autel.utils.ext.Container
import kotlinx.coroutines.launch


class TestViewModel:ViewModel() {
    val container = Container<EqualizerViewEvent, EqualizerViewData>(viewModelScope, EqualizerViewData(""))
    var beatCnts = 0

    fun startHeartBeat(){
        viewModelScope.launch {
            DeviceComService.startHeartBeat().collect{
                if(it.data == true){
                    container.uiState {
                        copy(resultTip="设备连接成功，心跳${beatCnts++}")
                    }
                }else{
                    container.uiState {
                        copy(resultTip="设备心跳断开！")
                    }
                }
            }
        }
    }

    fun stopHeartBeat(){
        DeviceComService.stopHeartBeat()
    }

    fun querySelfCheckStatus(){
        viewModelScope.launch {
            DeviceComService.querySelfCheckStatus().let {
                container.uiState {
                    copy(tip1 = "自检状态：${it.data.toString()}")
                }
            }
        }
    }
}