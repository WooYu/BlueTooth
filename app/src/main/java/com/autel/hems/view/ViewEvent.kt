package com.autel.hems.view

sealed class ViewEvent
class StartSystemBtnEvent():ViewEvent()
class StopSystemBtnEvent():ViewEvent()
class StartChargeBtnEvent():ViewEvent()
class StopChargeBtnEvent():ViewEvent()
class StartDisChargeBtnEvent():ViewEvent()
class StopDisChargeBtnEvent():ViewEvent()
class QueryLibVersion():ViewEvent()
class StartOnPowerGrid():ViewEvent()
class StartOffPowerGrid():ViewEvent()