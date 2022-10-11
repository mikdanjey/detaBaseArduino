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
    const char *const _detaRootCa =
        "-----BEGIN CERTIFICATE-----\n" \
        "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\n" \
        "-----END CERTIFICATE-----\n";
};

#endif
