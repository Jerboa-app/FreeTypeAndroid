#include <jni.h>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <Text/textRenderer.cpp>

static TextRenderer * textRenderer = NULL;
static Type * type = NULL;
static AAssetManager * assets = NULL;

/*
 * Logging to logcat can be achieved with
 *
        __android_log_print(ANDROID_LOG_INFO, "", "This is an info message");

*/

std::string jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

extern "C" {

    // each function must be declared with names following the convention
    //
    //      Java_app_jerboa_freetypeandroid_FreeTypeWrapper_FUNCTONNAME
    //
    // or more generally
    //
    //      Java_com_domain_example_CLASS_FUNCTIONNAME

    void Java_app_jerboa_freetypeandroid_FreeTypeWrapper_assetManager(
            JNIEnv *env,
            jobject /* this */,
            jobject assetManager
            ){
        __android_log_print(ANDROID_LOG_INFO, "", "LOADING ASSETS");
            assets = AAssetManager_fromJava(env,assetManager);
        __android_log_print(ANDROID_LOG_INFO, "", "ASSEST LOADED");
    }

    void Java_app_jerboa_freetypeandroid_FreeTypeWrapper_TextRenderer(
            JNIEnv *env,
            jobject /* this */,
            jfloat resX,
            jfloat resY
            ){
          glm::mat4 textProj = glm::ortho(0.0,double(resX),0.0,double(resY));
          textRenderer = new TextRenderer(textProj);
          type = new Type("fonts/","OpenDyslexic-Regular.otf",48,assets);
    }

    void Java_app_jerboa_freetypeandroid_FreeTypeWrapper_free(
            JNIEnv *env,
            jobject /* this */
            ){
        delete type;
        delete textRenderer;
    }

    void Java_app_jerboa_freetypeandroid_FreeTypeWrapper_renderText(
            JNIEnv *env,
            jobject /* this */,
            jstring text,
            jfloat x,
            jfloat y,
            jfloat scale,
            jfloat r,
            jfloat g,
            jfloat b
            ){

        if (textRenderer == NULL){
            return;
        }

        textRenderer->renderText(
                *type,
                jstring2string(env,text),
                x,
                y,
                scale,
                glm::vec3(r,g,b)
                );
    }
}
