package com.autel.core.libcom.hems

import com.autel.base.deviceconnect.factory.DeviceConnFactory
import com.autel.base.deviceconnect.factory.type.ConnType
import com.autel.core.libcom.hems.data.DataResult
import com.autel.core.libcom.hems.data.SelfCheckStatus
import com.autel.core.libcom.hems.tasks.DeviceCommTask
import com.autel.core.libcom.hems.tasks.HeartBeatTask
import com.autel.core.libcom.hems.tasks.SelfCheckTask
import com.autel.utils.queue.ITask
import com.autel.utils.queue.TaskManagerImp
import com.autel.utils.queue.TaskQueue
import kotlinx.coroutines.flow.SharedFlow

/**
 * @Author A16543
 * @Time 2023/1/9 0009 11:11
 * @Description
 */
object DeviceComService {
    private val taskManager = TaskManagerImp<ITask<DataResult<*>>, DataResult<*>>()
    private val mQueue: TaskQueue<ITask<DataResult<*>>, DataResult<*>> = TaskQueue(true, taskManager)

    private suspend fun sendData(task:ITask<DataResult<*>>):Boolean{
        if(task is DeviceCommTask<*,*>) {
            task.initCommDevice(DeviceConnFactory.getDeviceConnFactory(ConnType.SERIAL_PORT_CONN_TYPE))
        }
        return mQueue.enqueue(task)
    }


    suspend fun startHeartBeat(): SharedFlow<DataResult<Boolean>> {
        return taskManager.getTask(HeartBeatTask::class.java.simpleName)?.let {
            (it as HeartBeatTask).resultFlow
        }?:HeartBeatTask(true).let {
            sendData(it)
            it.resultFlow
        }
    }

    fun stopHeartBeat(){
        taskManager.getTask(HeartBeatTask::class.java.simpleName)?.let {
            if(it is HeartBeatTask){
                it.isStartConnect = false
            }
        }
    }

    suspend fun querySelfCheckStatus():DataResult<SelfCheckStatus>{
        var task = SelfCheckTask()
        sendData(task)
        return task.await()
    }
}