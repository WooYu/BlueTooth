package com.autel.core.libcom.hems.test

/**
 * @Author A16543
 * @Time 2022/8/29 0029 17:22
 * @Description
 */
data class EqualizerViewData(var resultTip:String,var tip1:String = "",var tip2:String = ""){
    var runBtnName:String="运行"
    var startBtnName:String="启动"
    var receive:String="接收命令数据"
}