

#include <psp2/io/stat.h> 
#include <psp2/sysmodule.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/display.h>

#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/net/http.h>

#include <psp2/io/fcntl.h>
#include <math.h>

#include <vita2d.h>


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <string>

#include <curl/curl.h>
#include <jansson.h>

#include "messageBox.h"

#ifndef _UTILS_
#define _UTILS_

struct stringcurl {
  char *ptr;
  size_t len;
}; 

extern int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, 
                    double TotalToUpload, double NowUploaded);

extern void init_string(struct stringcurl *s);

extern size_t writefunc(void *ptr, size_t size, size_t nmemb, struct stringcurl *s);

extern size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data);

extern size_t write_data_to_disk(void *ptr, size_t size, size_t nmemb, void *stream);

extern std::string getCurlString();

extern void curlDownloadFile(std::string url , std::string file);

extern void netInit();

extern void netTerm();

extern void httpInit();

extern void httpTerm();

extern std::string getJoke();

extern std::string getVDBDownloadCount(std::string url, std::string request);

extern void checkForUpdate();

#endif