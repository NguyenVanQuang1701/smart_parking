// Nhận IN/ OUT --> mqtt, cập nhật DB

const mqtt = require("mqtt");
const db = require("./database");

const client = mqtt.connect(
    "mqtt://10.12.175.1:1883"
);


client.on("connect", () => {        //client.on() dùng để lắng nghe một event

    console.log("MQTT CONNECTED");

    client.subscribe("parking/entry");      //đăng ký nhận message từ topic
    client.subscribe("parking/exit");

});


//MQTT MESSAGE

client.on("message", (topic, message) => {

    let event = message.toString(); //Chuyển message thành string

    console.log("MQTT:", topic, event); //MQTT: parking/entry IN


    //XE VÀO
    if (topic === "parking/entry" && event === "IN") {

        db.run(`
            UPDATE parking
            SET
                cars = CASE
                    WHEN cars < total THEN cars + 1
                    ELSE cars
                END,

                empty = CASE
                    WHEN empty > 0 THEN empty - 1
                    ELSE empty
                END
        `, function(err) {

            if (err) {
                console.log("DB ERROR:", err);
                return;
            }

            console.log("XE VAO -> UPDATE DB");

            updateStatus();

        });

    }


    //XE RA

    if (topic === "parking/exit" && event === "OUT") {

        db.run(`
            UPDATE parking
            SET
                cars = CASE
                    WHEN cars > 0 THEN cars - 1
                    ELSE 0
                END,

                empty = CASE
                    WHEN empty < total THEN empty + 1
                    ELSE empty
                END
        `, function(err) {

            if (err) {
                console.log("DB ERROR:", err);
                return;
            }

            console.log("XE RA -> UPDATE DB");

            updateStatus();

        });

    }


    //LƯU LỊCH SỬ

    if (event === "IN" || event === "OUT") {

        db.run(
            "INSERT INTO history(event, time) VALUES(?, datetime('now','localtime'))",
            [event],
            function(err) {

                if (err) {
                    console.log("HISTORY ERROR:", err);
                }

            }
        );

    }

});


//GỬI STATUS CHO ESP32

function updateStatus() {

    db.get(
        "SELECT * FROM parking",
        (err, row) => {

            if (err) {
                console.log("STATUS ERROR:", err);
                return;
            }

            if (!row) {
                return;
            }


            console.log(
                "STATUS:",
                row
            );


            client.publish(     //Publish trạng thái cho ESP32
                "parking/status",
                row.empty.toString()
            );

        }
    );

}