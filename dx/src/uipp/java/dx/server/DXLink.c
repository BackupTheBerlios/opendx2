/****************************************************************************/
/*                            DX  SOURCEFILE                                */
/****************************************************************************/


/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/java/dx/server/Attic/DXLink.c,v 1.1 1999/03/24 15:17:33 gda Exp $
 */

#include <string.h>
#include <stdlib.h>
#include <dx/dxl.h>
#include "DXServerThread.h"
#include "DXServer.h"

/*
 * The ibm6000 version of DXServer leaves defunct processes around.
 * using wait3 seems to take care of the problem.  I havent' tested
 * the other platforms.
 */
#if defined(ibm6000) || defined(sgi)
#if defined(ibm6000) || defined(hp700) || defined(alphax) || defined(sun4)
#define USE_WAIT3 1
#endif

#if USE_WAIT3
#if defined(alphax)
#include <sys/time.h>
#define _BSD
#include <sys/wait.h>
#else
#include <sys/wait.h>
#include <sys/time.h>
#endif
#else
#include <wait.h>
#endif
#endif


typedef struct _JavaEnv {
    void* java_env;
    void* java_obj;
} *JavaEnvironment;





/*
 * remove trailing whitespace from the message
 */
void DXLink_InfoMsgCB (DXLConnection * u1, const char *msg, const void *data)
{
int i,j;
jstring jstr;
jvalue jv[1];
char* dupmsg;

    JavaEnvironment je = (JavaEnvironment)data;
    JNIEnv* env = (JNIEnv*)je->java_env;
    jobject obj = (jobject)je->java_obj;
    jclass cls = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetMethodID(env, cls, "infoNotify", "(Ljava/lang/String;)V");
    if (mid == 0) {
	fprintf (stderr, "%s[%d] couldn't look up java method\n", __FILE__,__LINE__);
	return ;
    }

    i = 1+strlen(msg);
    dupmsg = (char*)malloc(i);
    strcpy (dupmsg, msg);
    for (j = i-1; j>=0; j--) {
	if ((dupmsg[j] == ' ') || (dupmsg[j] == '\t') || (dupmsg[j] == '\n'))
	    dupmsg[j] = '\0';
	else
	    break;
    }
    jstr = (*env)->NewStringUTF(env, dupmsg);
    jv[0].l = jstr;
    (*env)->CallVoidMethodA (env, obj, mid, jv);
    free(dupmsg);
}


JNIEXPORT jlong JNICALL Java_DXServer_DXLStartDX
    (JNIEnv *env, jclass u1, jstring jcmdstr, jstring jhost)
{
char cmdstr[256];
DXLConnection* dxl;

    const char *host = (*env)->GetStringUTFChars(env, jhost,0);
    const char *cmd = (*env)->GetStringUTFChars(env, jcmdstr,0);
    const char* dxargs = (const char*)getenv("DXARGS");

    if ((dxargs) && (dxargs[0]))
	sprintf (cmdstr, "dx %s", dxargs);
    else
	strcpy (cmdstr, cmd);
    dxl = DXLStartDX(cmdstr, host);
    /* if (dxl) DXLSetMessageDebugging(dxl, 1); */

    (*env)->ReleaseStringUTFChars(env, jcmdstr, cmd);
    (*env)->ReleaseStringUTFChars(env, jhost, host);

    return (long)dxl;
}

JNIEXPORT jint JNICALL Java_DXServerThread_DXLExecuteOnce
    (JNIEnv *env, jobject jobj, jlong jdxl, jstring jmacro)
{
jmethodID mid = 0;
int retval = 1;
DXLConnection* conn = (DXLConnection*)jdxl;
const char *macro = (*env)->GetStringUTFChars(env, jmacro,0);
char tmpbuf[128];
int size = sizeof(struct _JavaEnv);

    if (DXLGetSocket(conn) > 0) {

	JavaEnvironment je = (JavaEnvironment)malloc(size);
	je->java_env = (void*)env;
	je->java_obj = (void*)jobj;
	DXLSetMessageHandler (conn, PACK_INFO, NULL, 
	    (DXLMessageHandler)DXLink_InfoMsgCB, (const void*)je);
	DXLSetMessageHandler (conn, PACK_LINK, NULL, 
	    (DXLMessageHandler)DXLink_InfoMsgCB, (const void*)je);
	DXLSetMessageHandler (conn, PACK_ERROR, NULL,
	    (DXLMessageHandler)DXLink_InfoMsgCB, (const void*)je);

	strcpy (tmpbuf, macro);
	if (exDXLExecuteOnceNamed(conn, tmpbuf) == ERROR) {
	    retval = 0;
	} else {
	    const char* method_name = "hasEndMsg";
	    jclass cls = (*env)->GetObjectClass(env, jobj);
	    /* use the javap command to generate the signature. */
	    jmethodID mid = (*env)->GetMethodID(env, cls, "hasEndMsg", "()I");
	    int state = 1;
	    if (mid == 0) 
		fprintf (stderr, 
		    "%s[%d] couldn't look up java method\n", __FILE__,__LINE__);

	    while (state > 0) {
		/*
		 * Check for an end-execution message
		 */
		if (mid != 0) {
		    jint tmp = 0;
		    tmp = (*env)->CallIntMethod (env, jobj, mid);
		    if (tmp == 1) {
			DXLEndExecution (conn);
			break;
		    }
		}

		if (DXLWaitForEvent (conn) == ERROR) {
		    retval = 0;
		    break;
		}
		if (DXLHandlePendingMessages (conn) == ERROR) {
		    retval = 0;
		    break;
		}
		if (DXLGetExecutionStatus(conn, &state) == ERROR) {
		    retval = 0;
		    break;
		}
	    }
	}

	DXLRemoveMessageHandler (conn, PACK_INFO, NULL, 
	    (DXLMessageHandler)DXLink_InfoMsgCB);
	DXLRemoveMessageHandler (conn, PACK_LINK, NULL, 
	    (DXLMessageHandler)DXLink_InfoMsgCB);
	DXLRemoveMessageHandler (conn, PACK_ERROR, NULL,
	    (DXLMessageHandler)DXLink_InfoMsgCB);
    } else {
	retval = 0;
    }
    (*env)->ReleaseStringUTFChars(env, jmacro, macro);
    return retval;
}



JNIEXPORT jint JNICALL Java_DXServer_DXLSend
    (JNIEnv *env, jclass u1, jlong jdxl, jstring jval)
{
    int retval = 1;
    DXLConnection* conn = (DXLConnection*)jdxl;
    if (DXLGetSocket(conn) > 0) {
	const char* value = (*env)->GetStringUTFChars(env, jval, 0);
	if (DXLSend (conn, value) == ERROR) {
	    retval = 0;
	} 
	(*env)->ReleaseStringUTFChars(env, jval, value);
    } else {
	retval = 0;
    }

    return retval;
}


JNIEXPORT jint JNICALL Java_DXServerThread_DXLLoadVisualProgram
  (JNIEnv *env, jobject jobj, jlong jdxl, jstring jnet)
{
int retval = 0;
DXLConnection* conn = (DXLConnection*)jdxl;

    if (DXLGetSocket(conn) > 0) {
	const char* net_file = (*env)->GetStringUTFChars(env, jnet, 0); 
	retval = DXLLoadVisualProgram (conn, net_file) != ERROR; 
	(*env)->ReleaseStringUTFChars(env, jnet, net_file);
    }

    return retval;
}

JNIEXPORT jint JNICALL Java_DXServer_DXLExitDX
  (JNIEnv* u1, jclass u2, jlong jdxl)
{
    int retval = 1;

    DXLConnection* conn = (DXLConnection*)jdxl;
    if (DXLGetSocket(conn) > 0) {
	DXLSend(conn, "Executive(\"quit\");");
	if (DXLExitDX(conn) == ERROR) {
	    retval = 0;
	}
    } else {
	DXLCloseConnection (conn);
	retval = 0;
    }
#if defined(ibm6000) || defined(sgi)
#if defined(USE_WAIT3)
    wait3 (NULL, WNOHANG, NULL);
#endif

#if !defined(USE_WAIT3) && !defined(DXD_OS_NON_UNIX)
    {
    siginfo_t winfo;
    waitid (P_ALL, 0, &winfo, WNOHANG|WEXITED);
    }
#endif
#endif
    return retval;
}

JNIEXPORT jint JNICALL Java_DXServerThread_DXLIsMessagePending
  (JNIEnv *u1, jobject u2, jlong jdxl)
{
    int retval = 1;
    DXLConnection* conn = (DXLConnection*)jdxl;
    if (DXLGetSocket(conn) > 0) {
	retval = DXLIsMessagePending(conn);
    } else {
	retval = 0;
    }

    return retval;
}

JNIEXPORT jint JNICALL Java_DXServerThread_DXLHandlePendingMessages
    (JNIEnv *env, jobject jobj, jlong jdxl)
{
    int retval = 1;
    DXLConnection* conn = (DXLConnection*)jdxl;
    if (DXLGetSocket(conn) > 0) {
	if (DXLHandlePendingMessages (conn) == ERROR) {
	    retval = 0;
	}
    } else {
	retval = 0;
    }
    return retval;
}

