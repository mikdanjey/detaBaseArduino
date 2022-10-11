#ifndef DETABASE_LIBRARY_H
#define DETABASE_LIBRARY_H

#include <Arduino.h>
#include <WiFiClientSecure.h>

#define HTTPS_PORT 443
#define DETA_BASE_HOST "database.deta.sh"
#define TIMEOUT_THRESH 5000

typedef struct {
  int statusCode;
  String reply;
} result;


void printResult(result resultObject);
class DetaBaseObject {
  public:
    DetaBaseObject(WiFiClientSecure wifiObject, const char* detaID, const char* detaBaseName, const char* apiKey, bool debugOption);
    DetaBaseObject(WiFiClientSecure wifiObject, const char* detaID, const char* detaBaseName, const char* apiKey);
    ~DetaBaseObject();

    result putObject(const char* jsonObject);
    result getObject(const char* key);
    result deleteObject(const char* key);
    result insertObject(const char* jsonObject);
    result updateObject(const char* jsonObject, const char* key);
    result query(const char* queryObject);
    const char* getDetaID();
    const char* getBaseURI();

  private:
    const char* _apiKey;
    const char* _detaID;
    const char* _detaBaseName;
    char* _baseURI;
    const char* _host;
    WiFiClientSecure _wifiObject;
    bool _debugOn;
    bool checkTimeout();
    void parseReply(result* returnObject);
    void writeNonPayloadHeaders();
    void writePayloadHeaders(const char* object);
    void initResult(result* resultObject);
};

#endif
