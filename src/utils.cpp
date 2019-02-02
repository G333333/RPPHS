#define VITASDK

#include "utils.h"


int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, 
                    double TotalToUpload, double NowUploaded)
{
    // ensure that the file to be downloaded is not empty
    // because that would cause a division by zero error later on
    if (TotalToDownload <= 0.0) {
        return 0;
    }

		// how wide you want the progress meter to be
    int total=105;
    double fractiondownloaded = NowDownloaded / TotalToDownload;
    // part of the progress meter that's already "full"
    int progress = round(fractiondownloaded * total);

		vita2d_start_drawing();
		vita2d_clear_screen();

		vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f,"Downloading File") / 2, 544 / 2 - 50, RGBA8(255,255,255,255), 20.0f, "Downloading File");
		vita2d_draw_rectangle(960 / 2 - 55, 544 / 2 - 25, 110, 35, RGBA8(255,255,255,255));
		vita2d_draw_rectangle(960 / 2 - 50, 544 / 2 - 20, progress, 25, RGBA8(0,255,0,255));
		

		vita2d_end_drawing();
		vita2d_swap_buffers();

    // if you don't return 0, the transfer will be aborted - see the documentation
    return 0; 
}

void init_string(struct stringcurl *s) {
  s->len = 0;
  s->ptr = (char*)malloc(s->len+1);
  if (s->ptr == NULL) {
    return;
    //exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct stringcurl *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = (char*)realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    return 0;
    //exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

size_t write_data_to_disk(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = sceIoWrite(   *(int*) stream , ptr , size*nmemb);
  return written;
}

std::string getCurlString(std::string url){
	
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) {
		struct stringcurl body;
		init_string(&body);
		struct stringcurl header;
		init_string(&header);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// Set useragant string
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
		// not sure how to use this when enabled
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		// not sure how to use this when enabled
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		// Set SSL VERSION to TLS 1.2
		curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
		// Set timeout for the connection to build
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
		// Follow redirects (?)
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		// The function that will be used to write the data 
		std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
		// Internal CURL progressmeter must be disabled if we provide our own callback
		// write function of response headers
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writefunc);
		// the response header data where to write to
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);
		// Request Header :
		struct curl_slist *headerchunk = NULL;
		headerchunk = curl_slist_append(headerchunk, "Accept: */*");
		headerchunk = curl_slist_append(headerchunk, "Content-Type: application/json");
		headerchunk = curl_slist_append(headerchunk, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
		//headerchunk = curl_slist_append(headerchunk, "Host: discordapp.com");  Setting this will lead to errors when trying to download. should be set depending on location : possible : cdn.discordapp.com or images.discordapp.com
		headerchunk = curl_slist_append(headerchunk, "Content-Length: 0");
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerchunk);
		
		
		// Perform the request
		res = curl_easy_perform(curl);
		int httpresponsecode = 0;
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &httpresponsecode);

		if(res != CURLE_OK){
		}

		return response_string;
	}
	return "Error";
}

void curlDownloadFile(std::string url , std::string file){
	int imageFD = sceIoOpen( file.c_str(), SCE_O_WRONLY | SCE_O_CREAT, 0777);
	if(!imageFD){
		return;
	}
	
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) {
		struct stringcurl body;
		init_string(&body);
		struct stringcurl header;
		init_string(&header);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		// Set useragant string
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
		// not sure how to use this when enabled
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		// not sure how to use this when enabled
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		// Set SSL VERSION to TLS 1.2
		curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
		// Set timeout for the connection to build
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
		// Follow redirects (?)
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		// The function that will be used to write the data 
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_to_disk);
		// The data filedescriptor which will be written to
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &imageFD);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
		// Install the callback function
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);
		// write function of response headers
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writefunc);
		// the response header data where to write to
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);
		// Request Header :
		struct curl_slist *headerchunk = NULL;
		headerchunk = curl_slist_append(headerchunk, "Accept: */*");
		headerchunk = curl_slist_append(headerchunk, "Content-Type: application/json");
		headerchunk = curl_slist_append(headerchunk, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
		//headerchunk = curl_slist_append(headerchunk, "Host: discordapp.com");  Setting this will lead to errors when trying to download. should be set depending on location : possible : cdn.discordapp.com or images.discordapp.com
		headerchunk = curl_slist_append(headerchunk, "Content-Length: 0");
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerchunk);
		
		
		// Perform the request
		res = curl_easy_perform(curl);
		int httpresponsecode = 0;
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &httpresponsecode);
		
		if(res != CURLE_OK){
			//do error checking	
		}
	}

	// close filedescriptor
	sceIoClose(imageFD);

	// cleanup
	curl_easy_cleanup(curl);
	
}

void netInit() {
	sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	
	SceNetInitParam netInitParam;
	int size = 4*1024*1024;
	netInitParam.memory = malloc(size);
	netInitParam.size = size;
	netInitParam.flags = 0;
	sceNetInit(&netInitParam);

	sceNetCtlInit();
}

void netTerm() {
	sceNetCtlTerm();

	sceNetTerm();

	sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);
}

void httpInit() {
	sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);

	sceHttpInit(4*1024*1024);
}

void httpTerm() {
	sceHttpTerm();

	sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
}

std::string getJoke(){
	json_t *root;
  json_error_t error;

	root = json_loads(getCurlString("https://api.chucknorris.io/jokes/random").c_str(), 0, &error);
	if(!root){
		return "Error";
	}

	if(!json_is_object(root)){
		json_decref(root);
		return "Error";
	}

	json_t *value;
  std::string message_text;

	value = json_object_get(root, "value");
	if(!json_is_string(value))
  {
      json_decref(root);
			return "Error";
  }

	message_text = json_string_value(value);

	json_decref(root);

	return message_text;
}

std::string getVDBDownloadCount(std::string url, std::string request){
	json_t *root;
  json_error_t error;

	root = json_loads(getCurlString(url.c_str()).c_str(), 0, &error);
	if(!root){
		return "Error";
	}

	if(!json_is_array(root)){
		json_decref(root);
		return "Error";
	}

	for(size_t i = 0; i < json_array_size(root); i++){
		json_t *data, *name, *dlCount;
	  std::string message_text;

		data = json_array_get(root, i);
    if(!json_is_object(data))
    {
        json_decref(root);
        return "Error";
    }

	name = json_object_get(data, "name");
	if(!json_is_string(name))
  {
      json_decref(root);
			return "Error";
  }

	std::string temp = json_string_value(name);
	if(temp.compare(request) == 0){

		dlCount = json_object_get(data, "downloads");
		if(!json_is_string(dlCount))
		{
			json_decref(root);
			return "Error";
		}
		message_text = json_string_value(dlCount);
		return message_text;
	}

	}

	json_decref(root);

	return "Error";
}

void checkForUpdate(){

	struct SceIoStat * dirStat = (SceIoStat*)malloc(sizeof(SceIoStat));
	if(sceIoGetstat("ux0:data/RPPHS" , dirStat) < 0){
		sceIoMkdir("ux0:data/RPPHS" , 0777);
	}

	json_t *root;
  json_error_t error;

	root = json_loads(getCurlString("https://api.github.com/repos/g333333/RPPHS/releases").c_str(), 0, &error);
	if(!root){
		return;
	}

	if(!json_is_array(root)){
		json_decref(root);
		return;
	}

	json_t *data, *tag, *assets, *assetRoot, *dlUrl;
	std::string url;

	for(size_t i = 0; i < json_array_size(root); i++){

		data = json_array_get(root, i);
    if(!json_is_object(data))
    {
      	json_decref(root);
    	  return;
    }

		tag = json_object_get(data, "tag_name");
		if(!json_is_string(tag))
  	{
      json_decref(root);
			return;
  	}

		assets = json_object_get(data, "assets");
		if(!json_is_array(assets))
		{
			json_decref(root);
			return;
		}

		assetRoot = json_array_get(assets, 0);
		if(!json_is_object(assetRoot))
		{
			json_decref(root);
			return;
		}

		dlUrl = json_object_get(assetRoot, "browser_download_url");
		if(!json_is_string(dlUrl))
		{
			json_decref(root);
			return;
		}
	
		std::string tagString = json_string_value(tag);
		double versionNumber = std::stod(tagString.substr(1,3));

		url = json_string_value(dlUrl);
		if(versionNumber == 1.2)
		{
			if(makeYesNoBox("A new version is available. Would you like to download it from:",url,"And store it at ux0:data/RPPHS ?"))
			{
				curlDownloadFile(url, "ux0:data/RPPHS/RPPHS.vpk");	
				json_decref(root);
				
				if(makeYesNoBox("Download can be installed with vitaShell", "Would you like to close RPPHS?",""))
				{
					quitGame = true;
				}

				return;
			}
			return;
		}
	}
	json_decref(root);

	return;
}