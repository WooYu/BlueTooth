package com.autel.core.libcom.hems.jni

import com.autel.utils.log.logger
import kotlinx.coroutines.channels.BufferOverflow
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.coroutines.flow.asSharedFlow

object HemsSystemJni {

    private val _dataReportFlow  = MutableSharedFlow<Any>(0,Int.MAX_VALUE, BufferOverflow.DROP_OLDEST)

    val dataReportFlow = _dataReportFlow.asSharedFlow()


    init {
        System.loadLibrary("Hems")
    }

    private external fun startSystem():Boolean

    private external fun stopSystem():Boolean

    /**开启V2X桩充电*/
    private external fun startV2XCharge():Boolean

    private external fun stopV2XCharge():Boolean

    private external fun startV2XDisCharge():Boolean

    private external fun stopV2XDisCharge():Boolean
    /**开始并网*/
    private external fun startOnPowerGrid():Boolean
    /**开始离网*/
    private external fun startOffPowerGrid():Boolean

    private external fun getLibHemsVersion():String

    suspend fun startHemsNativeSystem(){
        startSystem()
    }

    suspend fun stopHemsNativeSystem(){
        stopSystem()
    }

    suspend fun startV2XCharging(){
        startV2XCharge()
    }

    suspend fun stopV2xCharging(){
        stopV2XCharge()
    }

    suspend fun startV2XDisCharging(){
        startV2XDisCharge()
    }

    suspend fun stopV2xDisCharging(){
        stopV2XDisCharge()
    }

    suspend fun getHemsLibVersion():String{
        return getLibHemsVersion()
    }

    suspend fun startHemsOnPowerGrid():Boolean{
        return startOnPowerGrid()
    }

    suspend fun startHemsOffPowerGrid():Boolean{
        return startOffPowerGrid()
    }

    @JvmStatic
    fun uploadCollectData(data:String):Boolean{
        logger.d("----收到来自设备数据：$data")
        _dataReportFlow.tryEmit(data)
        return true
    }
}