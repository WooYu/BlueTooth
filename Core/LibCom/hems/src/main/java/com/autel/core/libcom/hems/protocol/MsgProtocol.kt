package com.autel.core.libcom.hems.protocol

import com.autel.base.deviceconnect.DeviceConnInterface
import com.autel.utils.log.logger
import com.autel.utils.number.HexUtil
import kotlinx.coroutines.delay

/**
 * @Author A16543
 * @Time 2022/8/14 0014 16:20
 * @Description
 */
class MsgProtocol<T:MsgBody<D>,D>(private val mDevice: DeviceConnInterface,val msgBody:T){
    private val MSG_WRITE_HEAD:String = "A5"
    private val MSG_WRITE_TAIL:String = "0D"
    private val MSG_READ_HEAD:String = "5A"
    private val MSG_READ_TAIL:String = "D0"


    /**同步发送数据
     * @param msgId：协议ID
     */
    fun writeDataSync(msgId:String,deviceId:String,data: String,timeout:Int):Int{
        var sendData = data
        var buffer=StringBuffer()
        var strLen = sendData.length/2
        var temp = ByteArray(4)
        HexUtil.intToByte(temp,strLen,0,true)
        var crc = HexUtil.getCrcValue(HexUtil.decodeHex(sendData),strLen,HexUtil.decodeHex(msgId),HexUtil.decodeHex(deviceId)).toUByte()
        var crcString = crc.toString(16).uppercase()
        if(crcString.length<=1){
            crcString="0${crcString}"
        }
        var hexLenStr = HexUtil.encodeHexStr(temp.copyOfRange(2,4),false)
        var msg = buffer.append(MSG_WRITE_HEAD).append(msgId).append(deviceId).append(hexLenStr).append(sendData).append(crcString).append(MSG_WRITE_TAIL).toString()
        msgBody.msgId = msgId
        msgBody.deviceId = deviceId
        var hexStr = HexUtil.decodeHex(msg)
        //logger.d("--write-before--msgId=${msgId}")
        var ret = mDevice.writeDataSync(hexStr,timeout)
        logger.d("-write-msgId=${msgId}--writeDataSync--msg=${msg}--end-ret=${ret}--hexStr.size=${hexStr.size}--crc=${crcString}--dataLen=${strLen}")
        return ret
    }

    fun getCrcValue(data:ByteArray,lenth:UInt,id:ByteArray):UByte{
        var crcByte:UInt=0u
        for(byte in id){
            crcByte += byte.toUByte().toUInt()
        }
        crcByte += lenth
        for(byte in data){
            crcByte += byte.toUByte().toUInt()
        }
        return crcByte.toUByte()
    }

    /**
     * @param timeout 单位微妙
     */
    suspend fun readDataSync(timeout:Int):D?{
        var buffer=ByteArray(1024)
        var receiveData=StringBuffer()
        msgBody.msgCode = MsgCode.READ_FAILED;
        //logger.d("--read-before--msgId=${msgBody.msgId}")
        var tempTimeOut = timeout;
        while(true){
            var len = mDevice.readDataSync(buffer,tempTimeOut)
            if(len<=0){
                break
            }
            //读到数据后超时降低至20ms
            tempTimeOut =20
            receiveData.append(HexUtil.encodeHexStr(buffer.copyOfRange(0,len),false))
        }
        if(receiveData.isEmpty()){
            msgBody.msgCode = MsgCode.READ_FAILED
            logger.d("----readDataSync-data is Empty len = -1")
            return null
        }
        logger.d("-read-msgId=${msgBody.msgId}------readDataSync-data=${receiveData}")


        //消息解包
        var msg = HexUtil.decodeHex(receiveData.toString())
        if(msg.size<= 9){
            msgBody.msgCode = MsgCode.DEVICE_MSG_ERROR
            return null
        }
        var headByte = msg[0]
        var tailByte = msg[msg.size-1]
        var msgId = msg.copyOfRange(1,3)
        var deviceId = msg.copyOfRange(3,5)
        var crcByte = msg[msg.size-2]
        var dataStatus = msg[msg.size-3]
        msgBody.msgId = HexUtil.encodeHexStr(msgId)
        msgBody.msgCode = dataStatus.toUByte().toInt()
        msgBody.deviceId = HexUtil.encodeHexStr(deviceId)
        if (msgBody.msgCode != MsgCode.SUCCEED){
            msgBody.msgCode = MsgCode.DEVICE_MSG_ERROR
            logger.d("----readDataSync---MSG_CODE_DEVICE_MSG_ERROR-msgCode-")
            return null
        }
        if (headByte.toUByte().toInt() != 0x5A){
            msgBody.msgCode = MsgCode.DEVICE_MSG_ERROR
            logger.d("----readDataSync---MSG_CODE_DEVICE_MSG_ERROR-5A-")

            return null
        }
        if (tailByte.toUByte().toInt() != 0xD0){
            msgBody.msgCode = MsgCode.DEVICE_MSG_ERROR
            logger.d("----readDataSync---MSG_CODE_DEVICE_MSG_ERROR-D0-")
            return null
        }
        var msgData = msg.copyOfRange(7, msg.size - 2)
        var crcCheck = HexUtil.getCrcValue(msgData, msgData.size, msgId,deviceId)
        if (crcByte != crcCheck) {
            msgBody.msgCode = MsgCode.DEVICE_CRC_ERROR
            logger.d("----readDataSync---MSG_CODE_DEVICE_CRC_ERROR-crcCheck=${crcCheck}---crcByte=${crcByte}")
            return null
        }

        msgBody.data = msgData.copyOfRange(0, msgData.size-1)
        return msgBody.parseMsgData()
    }
}