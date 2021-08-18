#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Thông tin về wifi
#define ssid "BuiVinhBac"
#define password "12081963"
#define mqtt_server "broker.hivemq.com" 
const uint16_t mqtt_port = 1883; //Port của CloudMQTT TCP
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() 
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

char a;
void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Co tin nhan moi tu topic:");
  Serial.println(topic);
  for (int i = 0; i < length; i++)
    a = payload[i];
  if (a == 48)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
    digitalWrite(LED_BUILTIN, LOW);
  Serial.println();
}

void setup(){
  Serial.begin(115200);
  //while (!Serial) continue;
  pinMode(LED_BUILTIN, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port); 
  client.setCallback(callback);
}

void reconnect() 
{
  while (!client.connected()) // Chờ tới khi kết nối
  {
    // Thực hiện kết nối với mqtt user và pass
    if (client.connect("ESP8266_id1","ESP_offline",0,0,"ESP8266_id1_offline"))  //kết nối vào broker
    {
      Serial.println("Đã kết nối:");
      client.subscribe("ESP8266_read_data");
    }
    else 
    {
      Serial.print("Lỗi:, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Đợi 5s
      delay(5000);
    }
  }
}
String data;
String data1,data2,data3,data4;
int sta,dem = 0;

void Tach(String data){
  for( int i = 0 ; i < data.length();i++){
    if(data[i] == ','){
      if( dem == 0)
        data1 = data.substring(sta,i);
      if( dem == 1)
        data2 = data.substring(sta,i);
      if( dem == 2)
        data3 = data.substring(sta,i);

      sta = i + 1;
      dem ++;
    }
    if(dem == 3){
      data4 = data.substring(sta,data.length());
      sta = 0;
      dem = 0;
    }
  }
}

float Tach_data(String data){
  float data_sau;
  for(int i  = 0 ; i < data.length(); i++)
  {
    if ( data[i] == ':'){
      //data_truoc = data.substring(0,i);
      data_sau = data.substring(i+1,data.length()).toFloat();
      break;
    }
  }
  return data_sau;
}

void loop(){
  if (!client.connected())// Kiểm tra kết nối
      reconnect();
  if(Serial.available())
  {
    data = Serial.readString();
  }
  if (data != ""){
    Tach(data);
    Serial.println(data1);
    Serial.println(data2);
    Serial.println(data3);
    Serial.println(data4);
    StaticJsonDocument<200> doc;
    doc["Temp"] = Tach_data(data1);
    doc["Humi"] = Tach_data(data2);
    doc["Voltage"] = Tach_data(data3);
    doc["Dust"] = Tach_data(data4);
    char buffer[256];
    size_t n = serializeJson(doc, buffer);
    serializeJsonPretty(doc, Serial);
    client.publish("Toan123456", buffer, n);
    data = "";
    data1= "";
    data2= "";
    data3= "";
    data4= "";
  }
  
  //delay(100);
}
