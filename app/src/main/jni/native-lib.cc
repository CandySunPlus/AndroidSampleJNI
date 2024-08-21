#include "native-lib.h"

#ifdef __cplusplus
extern "C" {
#endif  // !__cplusplus

JNIEXPORT jstring JNICALL getPackageName(JNIEnv *env, jobject obj) {
    jclass clazz = env->GetObjectClass(obj);
    jmethodID mid = env->GetMethodID(clazz, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject packageManager = env->CallObjectMethod(obj, mid);

    mid = env->GetMethodID(clazz, "getPackageName", "()Ljava/lang/String;");
    jstring packageName = (jstring)env->CallObjectMethod(obj, mid);
    return packageName;
}

static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);

    if (clazz == NULL) {
        return JNI_FALSE;
    }

    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

static int registerNatives(JNIEnv *env) {
    static const char *className = "com/example/hani/MainActivity";

    static JNINativeMethod jniNativeMethods[] = {"getPName", "()Ljava/lang/String;", (void *)getPackageName};

    if (registerNativeMethods(env, className, jniNativeMethods, sizeof(jniNativeMethods) / sizeof(JNINativeMethod)) !=
        JNI_TRUE) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;

    ALOGI("JNI_ONLOAD");

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK) {
        ALOGE("GetEnv failed");
        return -1;
    }

    if (registerNatives(env) != JNI_TRUE) {
        ALOGE("RegisterNatives failed");
        return -1;
    }

    return JNI_VERSION_1_6;
}

#ifdef __cplusplus
}
#endif  // !__cplusplus
