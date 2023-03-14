package com.autel.core.libcom.hems.protocol

import com.autel.core.libcom.hems.protocol.MsgCode.SUCCEED


/**
 * @Author A16543
 * @Time 2022/8/15 0015 10:57
 * @Description
 */
class StatusMsgBody:MsgBody<Boolean>() {
    override fun parseMsgData(): Boolean {
        if(msgCode == SUCCEED){
            return true
        }
        return false
    }
}