#include "includes.h"
#pragma comment(lib,"wininet.lib")
int String2Char(string s, char a[])
{

	int n = s.size();
	int i = 0;
	while(a[i]=s[i])
		i++;
	return 1;
}

FbStatus GetFBStatuses(string paramId, string paramField,string paramToken)
{
		
	HINTERNET hopen, hconnect, hrequest;
	string accesstoken = paramToken;
	int n = accesstoken.size();
	string version = "/v2.1";
	string id = paramId;
	string edge ="/statuses";
	string field = paramField;
	char chUrlRequset [400];
	FbStatus t;
	string urlRequest = version+id+edge+field+"&"+accesstoken;
	String2Char(urlRequest,chUrlRequset);



	hopen = InternetOpen("HTTPGET",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	hconnect = InternetConnect(hopen,GRAPH_FB,INTERNET_DEFAULT_HTTPS_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);
	//hrequest= HttpOpenRequestA(hconnect,"GET","/v2.1/me/statuses?fields=message&limit=2&access_token=CAAVUMKQz7ZB0BANtlRFjMPvzH2PQ2We0Xy6tyd8iAAnSMMHZCduQHQMGZAln4PWOQO6CPFnYT4LVpQJ2TBay7vIR268fuq3jVONE5Hteq05GQA8QlBapz3ZAWmQdmu43giQytttLwpCAphqZCcztAwrlLX3kpc2hm4tBCYmTn7xkRHPoEazE1Nb2XSXQAnYDRZCK6sNixcj7nDni2QN4am" ,"HTTP/1.1",NULL, NULL,INTERNET_FLAG_SECURE , 0);
	hrequest= HttpOpenRequest(hconnect,"GET",chUrlRequset,"HTTP/1.1",NULL, NULL,INTERNET_FLAG_SECURE , 0);
	printf("FB Sending\n");
	if(HttpSendRequest(hrequest,NULL,NULL,NULL,0)){
		printf("FB Success\n");
		CHAR szBuffer[2048];
		DWORD dwRead=0;
		printf("FB Reading status\n");
		while(InternetReadFile(hrequest, szBuffer, sizeof(szBuffer)-1, &dwRead) && dwRead) 
		{
			szBuffer[dwRead] = 0;
			//printf(szBuffer);
			dwRead=0;
		}
		printf("FB Finish Reading\n");

		cJSON *root = cJSON_Parse(szBuffer);
		cJSON* arr = cJSON_GetObjectItem(root,"data");

		//printf("\n\n");
			if(cJSON_GetArraySize(arr)>0)
		{

			cJSON *subitem = cJSON_GetArrayItem(arr,0);
			//printf("%s\n",cJSON_GetObjectItem(subitem,"message")->valuestring);
			
			t.message = cJSON_GetObjectItem(subitem,"message")->valuestring;
			t.Id = cJSON_GetObjectItem(subitem,"id")->valuestring;
			printf("FB returning message\n");
			return t;


		}




	}
	else
	{
		printf("Failed\n");
		return t;
	}
	


	//InternetCloseHandle(hrequest);
	//InternetCloseHandle(hconnect);
	//InternetCloseHandle(hopen);
}

int UpStatusFb(string paramId, string paramMessage, string paramToken)
{
	HINTERNET hopen, hconnect, hrequest;
	string accesstoken = paramToken;
	int n = accesstoken.size();
	string version = "/v2.1";
	string id = paramId;
	string edge ="/comments";
	char chUrlRequset [400];
	string urlRequest = version+"/"+id+edge+"?"+accesstoken;
	String2Char(urlRequest,chUrlRequset);

	char headers[]="Content-Type: application/x-www-form-urlencoded";
	char formdata[300];
	String2Char("message="+paramMessage,formdata);
	

	hopen = InternetOpenA("HTTPGET",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	hconnect = InternetConnectA(hopen,GRAPH_FB,INTERNET_DEFAULT_HTTPS_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);
	hrequest= HttpOpenRequestA(hconnect,"POST",chUrlRequset,"HTTP/1.1",NULL, NULL,INTERNET_FLAG_SECURE , 0);
	if(HttpSendRequestA(hrequest,headers,strlen(headers),formdata,strlen(formdata))) {
		//printf("Success\n");
	}
	InternetCloseHandle(hrequest);
	InternetCloseHandle(hconnect);
	InternetCloseHandle(hopen);
	return 1;
	

}