#include <jni.h>
#include <string>
#include "LogPrint.h"

#include "HemsConfig.h"
#include "../System/HemsLib.h"

using namespace std;

void CallStaticFunction(JNIEnv *env){
    jclass  javaClass = env->FindClass("com/autel/core/libcom/hems/jni/HemsSystemJni");
    jmethodID uploadMethod = env->GetStaticMethodID(javaClass,"uploadCollectData",
                                                    "(Ljava/lang/String;)Z");
    jstring  data = env->NewStringUTF("Hems Devices Data");
    env->CallStaticBooleanMethod(javaClass,uploadMethod,data);
    env->DeleteLocalRef(javaClass);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_autel_core_libcom_hems_jni_HemsSystemJni_startSystem(JNIEnv *env, jobject thiz) {
    LOGE("----startSystem------- Message:%s", "1");
    CHemsLib::GetInst().Start();
    return JNI_TRUE;
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_autel_core_libcom_hems_jni_HemsSystemJni_stopSystem(JNIEnv *env, jobject thiz) {
    LOGE("----stopSystem------- Message:%s", "2");
    CHemsLib::GetInst().Stop();
    CHemsLib::ReleaseInst();
    return JNI_FALSE;
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_autel_core_libcom_hems_jni_HemsSystemJni_startV2XCharge(JNIEnv *env, jobject thiz) {
    LOGE("----startV2XCharge------- Message:%s", "3");
    return CHemsLib::GetInst().StartV2xCharge();
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_autel_core_libcom_hems_jni_HemsSystemJni_stopV2XCharge(JNIEnv *env, jobject thiz) {
    LOGE("----stopV2XCharge------- Message:%s", "4");
    return CHemsLib::GetInst().StopV2xCharge();
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_autel_core_libcom_hems_jni_HemsSystemJni_startV2XDisCharge(JNIEnv *env, jobject thiz) {
    LOGE("----startV2XDisCharge------- Message:%s", "5");
    return CHemsLib::GetInst().StartV2xDisCharge();
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_autel_core_libcom_hems_jni_HemsSystemJni_stopV2XDisCharge(JNIEnv *env, jobject thiz) {
    LOGE("----stopV2XDisCharge------- Message:%s", "6");
    return CHemsLib::GetInst().StopV2xDisCharge();
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_autel_core_libcom_hems_jni_HemsSystemJni_getLibHemsVersion(JNIEnv *env, jobject thiz) {
    string v =  to_string(Hems_VERSION_MAJOR)+"."+to_string(Hems_VERSION_MINOR);
    v += "."+ to_string(Hems_VERSION_PATCH);

    LOGE("----getLibHemsVersion------- Message:%s", v.c_str());
    jstring  version = env->NewStringUTF(v.c_str());
    return version;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_autel_core_libcom_hems_jni_HemsSystemJni_startOnPowerGrid(JNIEnv *env, jobject thiz) {
    LOGE("----startOnPowerGrid------- Message:%s", "7");
    return JNI_FALSE;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_autel_core_libcom_hems_jni_HemsSystemJni_startOffPowerGrid(JNIEnv *env, jobject thiz) {
    LOGE("----startOffPowerGrid------- Message:%s", "8");
    return JNI_FALSE;
}




