package com.autel.core.libcom.hems.protocol

import com.autel.core.libcom.hems.data.SelfCheckStatus
import com.autel.utils.number.HexUtil

/**
 * @Author A16543
 * @Time 2022/8/24 0024 11:06
 * @Description
 */
class SelfCheckMsgBody:MsgBody<SelfCheckStatus>() {
    companion object{
        val MSG_ID_REQ_SELF_CHECK = "8003"
        val MSG_ID_GET_SELF_CHECK_STATUS = "8004"
    }
    var selfCheckStatus:SelfCheckStatus?=null

    override fun parseMsgData(): SelfCheckStatus? {
        if(msgId != MSG_ID_GET_SELF_CHECK_STATUS){
            return null
        }
        var errorCode = HexUtil.byteToInt(data?.copyOfRange(1,5),0,true)
        selfCheckStatus = SelfCheckStatus(data?.get(0)!!.toInt(),errorCode)
        return selfCheckStatus
    }
}