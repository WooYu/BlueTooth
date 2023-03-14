package com.autel.core.libcom.hems.protocol

/**
 * @Author A16543
 * @Time 2022/8/14 0014 16:53
 * @Description
 */
abstract class MsgBody<D> {

    var msgCode: Int = 0x00
    var msgId: String? = null
    var deviceId: String = "0000"
    var deviceStatus:Int=0
    var data: ByteArray? = null


    abstract fun parseMsgData(): D?

}