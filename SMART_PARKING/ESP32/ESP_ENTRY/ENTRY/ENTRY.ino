#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include <TM1637Display.h>


const char* ssid = "NVQ";
const char* password = "17012004";

const char* mqtt_server = "10.12.175.1";

#define TRIG_PIN 5
#define ECHO_PIN 18

#define LED_GREEN 4
#define LED_RED 16

#define SERVO_ENTRY_PIN 19

Servo servoEntry;


#define TM_CLK 21
#define TM_DIO 22

TM1637Display display(TM_CLK, TM_DIO);


WiFiClient espClient;
PubSubClient client(espClient);


int emptySlot = 20;

bool carIn = false;

// ĐO KHOẢNG CÁCH
float distanceRead()
{
  digitalWrite(TRIG_PIN, LOW);

  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);

  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);


  long time = pulseIn(
    ECHO_PIN,
    HIGH,
    30000
  );


  if (time == 0)
  {
    return 999;
  }


  return time * 0.034 / 2;
}


void setupWifi()
{
  Serial.print("Connecting WIFI");

  WiFi.begin(
    ssid,
    password
  );


  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);

    Serial.print(".");
  }


  Serial.println();

  Serial.println("WIFI OK");


  Serial.print("ESP IP: ");

  Serial.println(
    WiFi.localIP()
  );
}

void callback(
  char* topic,
  byte* payload,
  unsigned int length
)
{
  String msg = "";


  for (int i = 0; i < length; i++)
  {
    msg += (char)payload[i];
  }


  Serial.print("MQTT DATA: ");

  Serial.println(msg);


  // Nhận số chỗ trống
  if (String(topic) == "parking/status")
  {
    emptySlot = msg.toInt();


    // Không cho vượt giới hạn
    if (emptySlot < 0)
    {
      emptySlot = 0;
    }

    if (emptySlot > 20)
    {
      emptySlot = 20;
    }


    Serial.print("EMPTY SLOT = ");

    Serial.println(emptySlot);
  }
}

// MQTT CONNECT

void reconnect()
{
  if (!client.connected())
  {
    Serial.print("Connecting MQTT...");


    if (client.connect("ESP32_ENTRY"))
    {
      Serial.println("OK");


      client.subscribe(
        "parking/status"
      );
    }
    else
    {
      Serial.print("FAILED state=");

      Serial.println(
        client.state()
      );
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(
    TRIG_PIN,
    OUTPUT
  );

  pinMode(
    ECHO_PIN,
    INPUT
  );
  pinMode(
    LED_GREEN,
    OUTPUT
  );

  pinMode(
    LED_RED,
    OUTPUT
  );

  servoEntry.setPeriodHertz(50);


  servoEntry.attach(
    SERVO_ENTRY_PIN,
    500,
    2400
  );


  // Đóng barrier lúc khởi động

  servoEntry.write(0);
  display.setBrightness(7);


  // Hiển thị ban đầu 20 chỗ
  display.showNumberDec(
    emptySlot,
    true
  );

  digitalWrite(
    LED_GREEN,
    HIGH
  );

  digitalWrite(
    LED_RED,
    LOW
  );
  setupWifi();

  client.setServer(
    mqtt_server,
    1883
  );

  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();
  display.showNumberDec(
    emptySlot,
    true
  );

  if (emptySlot > 0)
  {
    digitalWrite(
      LED_GREEN,
      HIGH
    );

    digitalWrite(
      LED_RED,
      LOW
    );
  }
  else
  {
    digitalWrite(
      LED_GREEN,
      LOW
    );

    digitalWrite(
      LED_RED,
      HIGH
    );
  }


  float d = distanceRead();


  Serial.print("Distance: ");

  Serial.println(d);

  // XE VÀO
  if (
    d < 15 &&
    carIn == false
  )
  {
    carIn = true;


    // Chỉ cho xe vào khi còn chỗ

    if (emptySlot > 0)
    {
      Serial.println("XE VAO");

      servoEntry.write(90);

      if (client.connected())
      {
        client.publish(
          "parking/entry",
          "IN"
        );

        Serial.println(
          "MQTT: IN"
        );
      }
      else
      {
        Serial.println(
          "MQTT KHONG KET NOI"
        );
      }

      delay(3000);
      servoEntry.write(0);

      Serial.println(
        "DONG THANH CHAN"
      );
    }
    else
    {
      Serial.println(
        "BAI DA DAY"
      );
    }
  }
  if (d > 30)
  {
    carIn = false;
  }
}
