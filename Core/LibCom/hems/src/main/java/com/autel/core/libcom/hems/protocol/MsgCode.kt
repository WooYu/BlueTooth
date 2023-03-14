package com.autel.core.libcom.hems.protocol

import com.autels.core.libcom.hems.R


/**
 * @Author A16543
 * @Time 2022/8/15 0015 20:07
 * @Description 消息结果码
 */
object MsgCode {
    const val SUCCEED = 0x00
    const val CHECK_FAILED = 0x01
    const val NOT_SUPPORT = 0x02
    const val LENGTH_ERROR = 0x03
    const val FRAME_ERROR = 0x04
    /**读取设备数据失败*/
    const val READ_FAILED = 0x10
    /**接收设备数据错误*/
    const val DEVICE_MSG_ERROR = 0x11
    /**接收设备数据CRC校验错误*/
    const val DEVICE_CRC_ERROR = 0x12
    /**发送数据错误*/
    const val SEND_DATA_ERROR = 0x13
    /**设备未连接*/
    const val DEVICE_NOT_CONNECTED = 0x14
    /**发送数据后，下位机未响应*/
    const val DEVICE_NOT_RESPOND = 0x15




    fun parseMsgCode(code:Int):Int{
        return when(code){
            READ_FAILED -> R.string.read_data_error
            DEVICE_MSG_ERROR -> R.string.data_lenth_error
            DEVICE_CRC_ERROR -> R.string.data_crc_error
            SEND_DATA_ERROR -> R.string.send_data_error
            DEVICE_NOT_CONNECTED -> R.string.device_not_connect
            DEVICE_NOT_RESPOND -> R.string.device_not_respond
            else->-1
        }
    }

}