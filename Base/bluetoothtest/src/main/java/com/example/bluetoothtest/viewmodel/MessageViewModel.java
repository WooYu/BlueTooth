package com.example.bluetoothtest.viewmodel;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class MessageViewModel extends ViewModel {
   private MutableLiveData<Boolean> isConncet = new MutableLiveData<>();
   private MutableLiveData<String> readData = new MutableLiveData<>();

   public MutableLiveData<Boolean> getConnectStatus(){
       return  isConncet;
   }

    public MutableLiveData<String> getReadData(){
        return  readData;
    }
}
