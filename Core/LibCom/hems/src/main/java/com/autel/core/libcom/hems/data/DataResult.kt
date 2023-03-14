package com.autel.core.libcom.hems.data

/**
 * @Author A16543
 * @Time 2022/8/10 0010 18:55
 * @Description
 */
data class DataResult<D>(val code:Int,val msg:String="",val data:D?){
    constructor(code:Int):this(code,"",null)
    constructor(code:Int,data:D?):this(code,"",data)
    constructor(code:Int,msg:String=""):this(code,msg,null)
    var msgData:String? = null
}

