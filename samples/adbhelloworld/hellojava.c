#include <stdio.h>
#include "jni.h"

void start_java() {
    JavaVM *jvm;
    JNIEnv *env;
    JavaVMInitArgs vm_args;
    JavaVMOption options[1];
    options[0].optionString = "-Djava.class.path=/data/local/tmp/class";
    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 1;
    vm_args.options = options;
    jint res = JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);
    if (res != 0) {
        fprintf(stderr, "Could not created JVM, res = %d\n", res);
        return;
    }
    jclass cls = (*env)->FindClass(env, "HelloWorld");
    if (cls == NULL) {
        printf("Could not find HelloWorld class\n");
        return;
    }
    jmethodID mid = (*env)->GetStaticMethodID(env, cls, "main", "([Ljava/lang/String;)V");
    if (mid == NULL) {
        printf("Could not find main method\n");
        return;
    }
    (*env)->CallStaticVoidMethod(env, cls, mid, NULL);
    (*jvm)->DestroyJavaVM(jvm);
}

int main(void) {
    fprintf(stderr, "in main, starting java...\n");
    start_java();
    fprintf(stderr, "Done.\n");
    return 0;
}
