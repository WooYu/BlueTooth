package com.autel.core.libcom.hems.data

/**
 * @Author A16543
 * @Time 2022/8/24 0024 10:41
 * @Description
 */
data class SelfCheckStatus(
    /**自检状态 0 表示自检测试通过过，1 正在检测*/
    val status:Int,
    /**
     * errorCode(int32)标志，各位定义如下：
     */
    val errorCode:Int,

){
    companion object{
        const val SELF_CHECK_PASSED = 0
        const val SELF_CHECKING = 1
        const val SELF_CHECK_NOT_PASSED = 2
    }
}


