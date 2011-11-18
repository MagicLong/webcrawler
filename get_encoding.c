#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "curl/curl.h"
#include "curl/types.h"
#include "curl/easy.h"

#include "utils.h"

static void err_exit(const char * info_str)
{
    fprintf(stderr, "%s\n", info_str);
    exit(-1);
}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) //这个函数是为了符合CURLOPT_WRITEFUNCTION, 而构造的
{
    FILE *fp = NULL;
    int write_size = 0;

    if( access(stream, R_OK) == -1 ){
        fp = fopen(stream, "wb");
    }
    else{
        fp = fopen(stream, "ab");
    }
    if(fp){
        write_size = fwrite(ptr, size, nmemb, fp);
        fclose(fp);
    }
    return write_size;
}

int main(int argc, char* argv[])
{
    int ret;
    char buffer[BUFF_MAX] = {0};
    char* page;
    int count, f;

    if( argc < 2 ){
        err_exit("No input");
    }
    char *tmp_file = "./tmp_for_curl";

    CURL *curl;

    curl_global_init(CURL_GLOBAL_ALL); 
    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, tmp_file);

    ret = curl_easy_perform(curl);

    if (ret){
        err_exit("get page error");
    }

    if( (f = open(tmp_file, 0)) == -1 ){
        err_exit("open file error");
    }

    page = (char*)malloc(1);
    memset(page, 0, 1);

    while(count = read(f, buffer, BUFF_MAX)){
        page = realloc(page, strlen(page) + count + 1);
        strncat(page, buffer, count);
    }
    printf("the page:\n %s", page);

    html_parser(page);

    if(page){
        free(page);
    }

    close(f);
    //remove(tmp_file);
    return 0;
}
