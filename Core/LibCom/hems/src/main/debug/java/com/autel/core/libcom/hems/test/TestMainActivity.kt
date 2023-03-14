package com.autel.core.libcom.hems.test


import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.ViewModelProvider
import com.autel.utils.ext.observeEvents
import com.autel.utils.ext.observeState
import com.autel.utils.log.logger
import com.autels.core.libcom.hems.databinding.ActivityTestMainBinding


class TestMainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityTestMainBinding
    lateinit var testViewModel:TestViewModel

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityTestMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        testViewModel = ViewModelProvider(this).get(TestViewModel::class.java)
        initViewListen()
        initViewStateObserve()
    }

    fun initViewListen(){
        binding.heartTest.setOnClickListener {
            testViewModel.startHeartBeat()
        }

        binding.deviceRunStatus.setOnClickListener {
            testViewModel.stopHeartBeat()
        }

        binding.moduleStatus.setOnClickListener {

        }

        binding.readConfig.setOnClickListener {
        }

        binding.runPauseTest.setOnClickListener {
        }
        binding.canConfig.setOnClickListener {
        }
        binding.selfCheckTest.setOnClickListener {
            testViewModel.querySelfCheckStatus()
        }
        binding.moduleConfig.setOnClickListener {
        }
        binding.targetVoltage.setOnClickListener {
        }
        binding.startConnect.setOnClickListener {
        }
        binding.setOnlyModule.setOnClickListener {
        }
    }

    fun initViewStateObserve(){
        testViewModel.container.viewData.let { state->
            state.observeState(this,EqualizerViewData::resultTip){
                binding.title.text = it
            }
            state.observeState(this,EqualizerViewData::tip1){
                binding.tip1.text = it
            }
            state.observeState(this,EqualizerViewData::tip2){
                binding.tip2.text = it
            }
            state.observeState(this,EqualizerViewData::runBtnName){
                binding.runPauseTest.text = it
            }
            state.observeState(this,EqualizerViewData::startBtnName){
                binding.startConnect.text = it
            }
            state.observeState(this,EqualizerViewData::receive){
                binding.receiveData.text = it
            }
        }
        testViewModel.container.viewEvents.observeEvents(this){
            when(it){
                is EqualizerViewEvent.ToastTip -> {
                    Toast.makeText(this,it.toastTip,Toast.LENGTH_LONG).show()
                }
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
    }

}