package com.autel.core.libcom.hems.tasks

import com.autel.core.libcom.hems.data.DataResult
import com.autel.core.libcom.hems.data.SelfCheckStatus
import com.autel.core.libcom.hems.protocol.MsgCode
import com.autel.core.libcom.hems.protocol.SelfCheckMsgBody
import com.autel.core.libcom.hems.protocol.SelfCheckMsgBody.Companion.MSG_ID_REQ_SELF_CHECK
import kotlinx.coroutines.delay

/**
 * @Author A16543
 * @Time 2022/8/24 0024 11:10
 * @Description
 */
class SelfCheckTask():DeviceCommTask<SelfCheckMsgBody, SelfCheckStatus>() {
    val selfCheckMsgBody = SelfCheckMsgBody()
    override suspend fun excuteDeviceCommTask(): DataResult<SelfCheckStatus> {
        var ret = sendData(MSG_ID_REQ_SELF_CHECK,deviceId,"", WRITE_TIME_OUT);
        //logger.d("---MSG_ID_REQ_SELF_CHECK-ret=${ret}")
        return if(ret>0) {
           var result =  readData(READ_TIME_OUT)
            DataResult(MsgCode.SUCCEED,result)
        }else DataResult(MsgCode.SEND_DATA_ERROR,null)
    }

    override fun getMsgProtocolBody(): SelfCheckMsgBody {
        return selfCheckMsgBody
    }


    override suspend fun excuteDeviceDebugCommTask(): DataResult<SelfCheckStatus> {
        delay(500)
        return DataResult(MsgCode.SUCCEED, SelfCheckStatus(MsgCode.SUCCEED,0))
    }
}