#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

const char* ssid = "NVQ";
const char* password = "17012004";


const char* mqtt_server = "10.12.175.1";

#define TRIG_PIN 5
#define ECHO_PIN 18

#define SERVO_EXIT_PIN 12

Servo servoExit;

WiFiClient espClient;

PubSubClient client(espClient);

bool carOut = false;

float distanceRead()
{

  digitalWrite(
    TRIG_PIN,
    LOW
  );

  delayMicroseconds(2);


  digitalWrite(
    TRIG_PIN,
    HIGH
  );

  delayMicroseconds(10);


  digitalWrite(
    TRIG_PIN,
    LOW
  );


  long time =
    pulseIn(
      ECHO_PIN,
      HIGH,
      30000
    );


  if(time == 0)
    return 999;


  return time * 0.034 / 2;

}


void setupWifi()
{

  Serial.print(
    "Connecting WIFI"
  );


  WiFi.begin(
    ssid,
    password
  );


  while(
    WiFi.status() != WL_CONNECTED
  )
  {

    delay(500);

    Serial.print(".");

  }


  Serial.println();

  Serial.println(
    "WIFI OK"
  );


  Serial.print(
    "ESP IP: "
  );

  Serial.println(
    WiFi.localIP()
  );

}

void reconnect()
{

  if(
    !client.connected()
  )
  {

    Serial.print(
      "Connecting MQTT..."
    );


    if(
      client.connect(
        "ESP32_EXIT"
      )
    )
    {

      Serial.println(
        "OK"
      );

    }
    else
    {

      Serial.print(
        "FAILED state="
      );

      Serial.println(
        client.state()
      );

    }

  }

}

void setup()
{

  Serial.begin(
    115200
  );

  pinMode(
    TRIG_PIN,
    OUTPUT
  );

  pinMode(
    ECHO_PIN,
    INPUT
  );

  servoExit.setPeriodHertz(
    50
  );


  servoExit.attach(
    SERVO_EXIT_PIN,
    500,
    2400
  );

  servoExit.write(
    0
  );

  setupWifi();

  client.setServer(
    mqtt_server,
    1883
  );

}

void loop()
{
  if(
    !client.connected()
  )
  {
    reconnect();
  }


  client.loop();
  float d =
    distanceRead();


  Serial.print(
    "Distance: "
  );

  Serial.println(
    d
  );

  if(
    d < 15 &&
    carOut == false
  )
  {

    carOut = true;


    Serial.println(
      "XE RA"
    );

    servoExit.write(
      90
    );
    if(
      client.connected()
    )
    {

      client.publish(
        "parking/exit",
        "OUT"
      );


      Serial.println(
        "MQTT: OUT"
      );

    }

    delay(3000);

    servoExit.write(
      0
    );


    Serial.println(
      "DONG THANH CHAN"
    );

  }

  if(
    d > 30
  )
  {

    carOut = false;

  }

}
