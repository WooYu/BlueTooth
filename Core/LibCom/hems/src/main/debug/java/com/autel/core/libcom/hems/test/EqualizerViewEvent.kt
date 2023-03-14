package com.autel.core.libcom.hems.test

/**
 * @Author A16543
 * @Time 2022/8/29 0029 17:22
 * @Description
 */
sealed class EqualizerViewEvent {
    data class ToastTip(val  toastTip:String = ""):EqualizerViewEvent()
}