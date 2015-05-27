#define GRAPH_FB "graph.facebook.com"
typedef struct FbStatus{
	char* message;
	char* Id;
} FbStatus;

int String2Char(string s,char a[]);
FbStatus GetFBStatuses(string id, string field, string token);
int UpStatusFb(string paramId, string paramMessage, string paramToken);