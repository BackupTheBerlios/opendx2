/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class server_DXServerThread */

#ifndef _Included_server_DXServerThread
#define _Included_server_DXServerThread
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     server_DXServerThread
 * Method:    DXLExecuteOnce
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_server_DXServerThread_DXLExecuteOnce
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     server_DXServerThread
 * Method:    DXLHandlePendingMessages
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_server_DXServerThread_DXLHandlePendingMessages
  (JNIEnv *, jobject, jlong);

/*
 * Class:     server_DXServerThread
 * Method:    DXLLoadVisualProgram
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_server_DXServerThread_DXLLoadVisualProgram
  (JNIEnv *, jobject, jlong, jstring);

#ifdef __cplusplus
}
#endif
#endif
