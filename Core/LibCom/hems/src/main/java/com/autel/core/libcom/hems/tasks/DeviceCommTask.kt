package com.autel.core.libcom.hems.tasks

import com.autel.base.deviceconnect.DeviceConnInterface
import com.autel.core.libcom.hems.data.DataResult
import com.autel.core.libcom.hems.protocol.MsgBody
import com.autel.core.libcom.hems.protocol.MsgCode
import com.autel.core.libcom.hems.protocol.MsgProtocol
import com.autel.utils.log.logger
import com.autel.utils.queue.AbTimeTask
import com.autels.core.libcom.hems.BuildConfig
import kotlinx.coroutines.delay

/**
 * @Author A16543
 * @Time 2022/8/10 0010 11:19
 * @Description
 */
abstract class DeviceCommTask<T: MsgBody<D>,D>(val deviceId: String="0000",timeMills: Long = 0, isPeriod: Boolean = false) : AbTimeTask<DataResult<D>>(timeMills,isPeriod){

    companion object{
        //1秒
        val READ_TIME_OUT  = 1000
        //200毫秒
        val WRITE_TIME_OUT = 200
    }

    private lateinit var mDevice: DeviceConnInterface
    private lateinit var mMsgProtocol: MsgProtocol<T, D>

    override fun tag(): String {
        return this.javaClass.simpleName
    }

    fun initCommDevice(device:DeviceConnInterface){
        mDevice = device
        mMsgProtocol = MsgProtocol<T,D>(mDevice,getMsgProtocolBody())
    }

    suspend fun isDeviceConnect():Boolean{
        if(mDevice.isConnCanUse()){
            return true
        }
        var isSucceed = mDevice.openDeviceConn(true)
        if(isSucceed){
            delay(500)
            return mDevice.isConnCanUse()
        }
        return false
    }


    fun sendData(msgId:String, deviceId:String, data: String, timeout: Int): Int {
        return mMsgProtocol.writeDataSync(msgId,deviceId,data,timeout)
    }

    /**
     * @param timeout 单位微妙
     */
    suspend fun readData(timeout: Int): D? {
        return mMsgProtocol.readDataSync(timeout)
    }

    override suspend fun excuteTask(): DataResult<D> {
        if(BuildConfig.isDemo){
            return excuteDeviceDebugCommTask()
        }
        if(!isDeviceConnect() ){
            logger.d("----device--not--connected--")
            return DataResult(MsgCode.DEVICE_NOT_CONNECTED)
        }
        return excuteDeviceCommTask()
    }


    override suspend fun excuteTimerTask(): DataResult<D> {
        return excuteTask()
    }

    abstract suspend fun excuteDeviceCommTask():DataResult<D>

    abstract suspend fun excuteDeviceDebugCommTask():DataResult<D>

    abstract fun getMsgProtocolBody():T

}