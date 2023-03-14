package com.autel.core.libcom.hems.tasks

import com.autel.core.libcom.hems.data.DataResult
import com.autel.core.libcom.hems.protocol.MsgCode
import com.autel.core.libcom.hems.protocol.StatusMsgBody


/**
 * @Author A16543
 * @Time 2022/8/10 0010 18:23
 * @Description 心跳任务，开启连接或顿开连接
 */
class HeartBeatTask(var isStartConnect:Boolean): DeviceCommTask<StatusMsgBody,Boolean>( timeMills= 1000,isPeriod = true) {
    private val MSG_ID_CONNECT = "0101"
    private val MSG_ID_DISCONNECT = "0102"
    var msgBody=StatusMsgBody()


    override suspend fun excuteDeviceCommTask(): DataResult<Boolean> {
        var msgId = if(isStartConnect) MSG_ID_CONNECT else MSG_ID_DISCONNECT
        var sedRet = sendData(msgId,deviceId,"", WRITE_TIME_OUT)
        if(!isStartConnect){
            stopTimeTask()
        }
        if(sedRet <0){
            return DataResult(MsgCode.SEND_DATA_ERROR)
        }
        var readRet = readData(READ_TIME_OUT) ?: return DataResult(MsgCode.READ_FAILED)
        var result = DataResult(MsgCode.SUCCEED,readRet)

        return result
    }

    override fun getMsgProtocolBody(): StatusMsgBody {
        return msgBody
    }

    override suspend fun excuteDeviceDebugCommTask(): DataResult<Boolean> {
        return DataResult(MsgCode.SUCCEED,true)
    }


}