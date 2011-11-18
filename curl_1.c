#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "curl/curl.h"
#include "curl/types.h"
#include "curl/easy.h"

FILE *fp; //定义FILE类型指针

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) //这个函数是为了符合CURLOPT_WRITEFUNCTION, 而构造的
{
    int written = fwrite(ptr, size, nmemb, (FILE *)fp);
    return written;
}

int main(int argc, char *argv[])
{
    CURL *curl;
    char* fpath = './tmp

    curl_global_init(CURL_GLOBAL_ALL); 
    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); //CURLOPT_WRITEFUNCTION 将后继的动作交给write_data函数处理
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fpath);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    exit(0);
}
