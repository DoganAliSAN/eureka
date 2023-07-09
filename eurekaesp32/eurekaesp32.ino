#include <FS.h>
#include <SD_MMC.h>
#include <WiFi.h>

String readFile(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return "";
  }

  String content = "";
  while (file.available()) {
    char c = file.read();
    if (c == '\n') {
      content += "|||";
    } else {
      content += c;
    }
  }

  return content;
}

void splitString(const String& input, const char* delimiter, String* output, int outputSize) {
  char str[input.length() + 1];
  strcpy(str, input.c_str());

  char* token = strtok(str, delimiter);
  int index = 0;
  while (token != nullptr && index < outputSize) {
    output[index] = String(token);
    token = strtok(nullptr, delimiter);
    index++;
  }
}

const int serverPort = 5394;
WiFiServer server(serverPort);

void setup() {
  Serial.begin(115200);

  String content = readFile(SD_MMC, "/wifi.txt");
  String tokens[2];
  splitString(content, "|||", tokens, 2);
  const char* ssid = tokens[0].c_str();
  const char* password = tokens[1].c_str();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\n');
        Serial.println(request);
        client.println("OK");
        client.stop();
      }
    }
  }
}
