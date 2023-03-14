package com.autel.busiservices.hems

import com.autel.core.libcom.hems.jni.HemsSystemJni
import com.autel.core.libcom.hems.jni.HemsSystemJni.startHemsNativeSystem
import com.autel.core.libcom.hems.jni.HemsSystemJni.stopHemsNativeSystem
import com.autel.utils.queue.IErrorStrategy
import com.autel.utils.queue.TaskErrorContext
import kotlinx.coroutines.*
import kotlin.coroutines.CoroutineContext


object HemsSystemService{

    private var taskErrorContext = TaskErrorContext(object: IErrorStrategy{
        override fun handleError(e: Throwable) {

        }
    })

    private val coroutineScope =
        CoroutineScope(SupervisorJob() + Dispatchers.IO + CoroutineExceptionHandler { _, e ->
            taskErrorContext.handleError(e)//SupervisorJob 防止子协程抛异常，影响其他协程
        })

    fun startHemsSystemService(){
        coroutineScope.launch(CoroutineName("HemsSystemServer")) {
            //开启Hems系统服务线程
            startBluetoothServer()
            //启动Hems中间层系统业务
            startHemsNativeSystem()

        }
    }

    fun stopHemsSystemService(){
        coroutineScope.launch{
            stopBluetootheServer()
            stopHemsNativeSystem()
        }
    }



    private fun startBluetoothServer(){
        coroutineScope.launch(CoroutineName("BluetoothServer")) {
            //开启蓝牙服务线程
        }
    }

    private fun stopBluetootheServer(){

    }
}