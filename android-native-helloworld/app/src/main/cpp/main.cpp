// Native (NDK) entry point for the app. No Java/Kotlin source is needed:
// the framework's android.app.NativeActivity hosts this native code directly
// (see AndroidManifest.xml -> android.app.lib_name = "native-activity").

#include <android_native_app_glue.h>
#include <android/log.h>
#include <jni.h>

#define LOG_TAG "HelloNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Builds a TextView showing "Hello, World!" and sets it as the activity's
// content view, entirely from native code via JNI.
static void showHelloWorld(android_app* app) {
    JNIEnv* env = nullptr;
    app->activity->vm->AttachCurrentThread(&env, nullptr);

    jobject activity = app->activity->clazz;
    jclass activityClass = env->GetObjectClass(activity);

    jclass textViewClass = env->FindClass("android/widget/TextView");
    jmethodID textViewCtor = env->GetMethodID(textViewClass, "<init>", "(Landroid/content/Context;)V");
    jobject textView = env->NewObject(textViewClass, textViewCtor, activity);

    jstring helloText = env->NewStringUTF("Hello, World!");
    jmethodID setText = env->GetMethodID(textViewClass, "setText", "(Ljava/lang/CharSequence;)V");
    env->CallVoidMethod(textView, setText, helloText);

    jmethodID setTextSize = env->GetMethodID(textViewClass, "setTextSize", "(F)V");
    env->CallVoidMethod(textView, setTextSize, 32.0f);

    jmethodID setGravity = env->GetMethodID(textViewClass, "setGravity", "(I)V");
    const jint GRAVITY_CENTER = 0x11; // android.view.Gravity.CENTER
    env->CallVoidMethod(textView, setGravity, GRAVITY_CENTER);

    jmethodID setContentView = env->GetMethodID(activityClass, "setContentView", "(Landroid/view/View;)V");
    env->CallVoidMethod(activity, setContentView, textView);

    LOGI("Hello, World!");

    app->activity->vm->DetachCurrentThread();
}

static void onAppCmd(android_app* app, int32_t cmd) {
    if (cmd == APP_CMD_INIT_WINDOW && app->window != nullptr) {
        showHelloWorld(app);
    }
}

void android_main(android_app* app) {
    app->onAppCmd = onAppCmd;

    int events;
    android_poll_source* source;
    while (true) {
        while (ALooper_pollAll(-1, nullptr, &events, reinterpret_cast<void**>(&source)) >= 0) {
            if (source != nullptr) {
                source->process(app, source);
            }
            if (app->destroyRequested != 0) {
                return;
            }
        }
    }
}
